cmake_minimum_required(VERSION 3.20)

add_executable(init runit-init.c strerr_die.c buffer.c buffer_2.c buffer_1.c error_str.c open_append.c open_read.c open_trunc.c open_write.c error.c
        sig.c strerr_sys.c buffer_put.c byte_copy.c buffer_write.c str_len.c)




