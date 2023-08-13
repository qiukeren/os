function(prepare_crosstool)
    # set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY  CACHE STRING "" FORCE)

    file(MAKE_DIRECTORY crosstools)

    if ("${XOS_BUILD_TARGET}" STREQUAL "")

    else ()
        set(CROSSTOOL_NAME
                "${XOS_BUILD_TARGET}-linux-musl-cross"
                CACHE STRING "" FORCE)
    endif ()


    if (XOS_BUILD_TARGET STREQUAL x86_64)
        message("x86_64 build.")
        file(
                DOWNLOAD "https://musl.cc/${CROSSTOOL_NAME}.tgz"
                "crosstools/${CROSSTOOL_NAME}.tgz"
                SHOW_PROGRESS
                EXPECTED_MD5 84ba29c79b6da7e069ecdd2692545546)
    elseif (XOS_BUILD_TARGET STREQUAL riscv64)
        message("riscv64 build.")
        file(
                DOWNLOAD "https://musl.cc/${CROSSTOOL_NAME}.tgz"
                "crosstools/${CROSSTOOL_NAME}.tgz"
                SHOW_PROGRESS
                EXPECTED_MD5 9833ad1cc88396b0e6e7a40ee8cda63e)
    else ()
        message("default x86_64 build.")
    endif ()

    message("${XOS_BUILD_TARGET}")

    if (NOT "${XOS_BUILD_TARGET}" STREQUAL "")

        set(CROSSTOOL_NAME
                "${XOS_BUILD_TARGET}-linux-musl-cross"
                CACHE STRING "" FORCE)
        file(REMOVE_RECURSE "crosstools/${CROSSTOOL_NAME}")
        file(ARCHIVE_EXTRACT INPUT "crosstools/${CROSSTOOL_NAME}.tgz" DESTINATION
                crosstools/)

        set(CROSSTOOL_NAME
                "${XOS_BUILD_TARGET}-linux-musl-cross"
                PARENT_SCOPE)
        message("build crosstools/${CROSSTOOL_NAME}")
        message("build crosstools/${CROSSTOOL_NAME}.tgz")
        message(
                "build ${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
        )
        set(CMAKE_C_COMPILER
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
                CACHE FILEPATH "" FORCE)
        set(CMAKE_CXX_COMPILER
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-g++"
                CACHE FILEPATH "" FORCE)

        set(CMAKE_AR
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-ar"
                CACHE FILEPATH "" FORCE)
        set(CMAKE_ASM_COMPILER
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-gcc"
                PARENT_SCOPE)
        #        set(CMAKE_CXX_LINK_EXECUTABLE
        #                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-ld"
        #                PARENT_SCOPE)
        set(CMAKE_LINKER
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-ld"
                CACHE FILEPATH "" FORCE)
        set(CMAKE_OBJCOPY
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-objcopy"
                CACHE FILEPATH "" FORCE)
        set(CMAKE_RANLIB
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-ranlib"
                CACHE FILEPATH "" FORCE)
        set(CMAKE_SIZE
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-size"
                CACHE FILEPATH "" FORCE)
        set(CMAKE_STRIP
                "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin/${XOS_BUILD_TARGET}-linux-musl-strip"
                CACHE FILEPATH "" FORCE)


        SET(CMAKE_SYSTEM_PROGRAM_PATH "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/bin")
        SET(CMAKE_FIND_ROOT_PATH "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}/x86_64-linux-musl")
        #    SET(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/crosstools/${CROSSTOOL_NAME}")

        set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM
                NEVER
                PARENT_SCOPE)
        set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY
                ONLY
                PARENT_SCOPE)
        set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE
                ONLY
                PARENT_SCOPE)
    endif ()


endfunction()
