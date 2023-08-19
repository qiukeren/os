```
# XPM FORMAT
# ---

fixed header
    # 0-4   : fixed header 0x075BCD15
    # 4-12   : len(data - 12) ===> The size of the package uint32

part type
    # 01 main content
    # 02 file content

part header
    # uint16   : part type
    # uint64   : part size

main content
    # part header
    # 10-26 : package name 16 bytes
    # 26-28 : major version 16 bytes
    # 28-30 : minor version 16 bytes
    # 30-36 : architecture
    # uint32 : description size
    # 50-50+size: xxxxx

file content
    # part header
    # uint32 stat
    # uint32 uid
    # uint32 gid
    # uint64 Atim Sec
    # uint64 Atim Nsec
    # uint64 Mtim Sec
    # uint64 Mtim Nsec
    # uint64 Ctim Sec
    # uint64 Ctim Nsec
    # uint64 size
    # [32]char md5
    # size content
```