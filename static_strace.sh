./bootstrap  ; ./configure --enable-mpers=no
make LDFLAGS+='-static -pthread'
