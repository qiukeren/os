function(prepare_crosstool)

    file(MAKE_DIRECTORY crosstools)
    set(CROSSTOOL_NAME "${XOS_BUILD_TARGET}-linux-musl-cross")

    if(XOS_BUILD_TARGET MATCHES x86_64)
        message("x86_64 build.")
        file(
            DOWNLOAD "http://musl.cc/${CROSSTOOL_NAME}.tgz"
            "crosstools/${CROSSTOOL_NAME}.tgz"
            SHOW_PROGRESS
            EXPECTED_MD5 84ba29c79b6da7e069ecdd2692545546)
    elseif(XOS_BUILD_TARGET MATCHES riscv64)
        message("riscv64 build.")
        file(
            DOWNLOAD "http://musl.cc/${CROSSTOOL_NAME}.tgz"
            "crosstools/${CROSSTOOL_NAME}.tgz"
            SHOW_PROGRESS
            EXPECTED_MD5 9833ad1cc88396b0e6e7a40ee8cda63e)
    else()
        message("default x86_64 build.")
        set(XOS_BUILD_TARGET x86_64)
        set(CROSSTOOL_NAME "x86_64-linux-musl-cross")
        file(
            DOWNLOAD "http://musl.cc/${CROSSTOOL_NAME}.tgz"
            "crosstools/${CROSSTOOL_NAME}.tgz"
            SHOW_PROGRESS
            EXPECTED_MD5 84ba29c79b6da7e069ecdd2692545546)
    endif()

    file(REMOVE_RECURSE "crosstools/${CROSSTOOL_NAME}")
    file(ARCHIVE_EXTRACT INPUT "crosstools/${CROSSTOOL_NAME}.tgz" DESTINATION
         crosstools/)

    set(CROSSTOOL_NAME "${XOS_BUILD_TARGET}-linux-musl-cross")
    message("build crosstools/${CROSSTOOL_NAME}")
    message("build crosstools/${CROSSTOOL_NAME}.tgz")
    message(
        "build ${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
    )
    set(CMAKE_C_COMPILER
        "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
    )
    set(CMAKE_CXX_COMPILER
        "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-g++"
    )

endfunction()
