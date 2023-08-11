#!/usr/bin/python3

import os
from pathlib import Path
import shutil


def rmdir(directory):
    directory = Path(directory)
    for item in directory.iterdir():
        if item.is_dir():
            rmdir(item)
        else:
            item.unlink()
    directory.rmdir()


XOS_BUILD_TARGET = os.getenv("XOS_BUILD_TARGET")


print("======= print environments")
for key in os.environ:
    if "XOS" in key:
        print(key, "=", os.environ[key])


def print_and_exit(msg: str):
    print(msg)
    exit(1)


print("======= start environment check")

if XOS_BUILD_TARGET == "":
    print_and_exit("XOS_BUILD_TARGET is empty")


XOS_FULL_DIST_PATH = os.path.abspath("dist")
XOS_FULL_DIST_TARGET_PATH = os.path.abspath("dist/" + XOS_BUILD_TARGET)
XOS_FULL_DIST_TARGET_PATH_ROOT = os.path.abspath("dist/" + XOS_BUILD_TARGET + "/root")


try:
    rmdir(XOS_FULL_DIST_TARGET_PATH)
except Exception as e:
    print(e)

XOS_CROSSTOOL_DIR = os.path.abspath("crosstools")
XOS_CROSSTOOL_NAME = XOS_BUILD_TARGET + "-linux-musl-cross"

XOS_CROSSTOOL_TOOLCHAIN_LIBDIR = os.path.abspath(
    XOS_CROSSTOOL_DIR
    + "/"
    + XOS_CROSSTOOL_NAME
    + "/"
    + XOS_BUILD_TARGET
    + "-linux-musl/lib/"
)


_rootDirs = [
    "bin",
    "data",
    "etc",
    "lib32",
    "sbin",
    "tmp",
    "var",
    "boot",
    "dev",
    "lib",
    "mnt",
    "proc",
    "run",
    "sys",
    "usr",
]


def mkdirRoot():
    print("======= start prepare root directory")
    for k in _rootDirs:
        os.makedirs(XOS_FULL_DIST_TARGET_PATH_ROOT + "/" + k, exist_ok=True)
        print("prepare directories", (XOS_FULL_DIST_TARGET_PATH_ROOT + "/" + k))


_muslLibs = [
    "libc.so",
    "libstdc++.so.6.0.29",
    "libgcc_s.so.1",
]

_muslLibLinks = {
    "libstdc++.so": "libstdc++.so.6.0.29",
    "libstdc++.so.6": "libstdc++.so.6.0.29",
    "ld-musl-" + XOS_BUILD_TARGET + ".so.1": "libc.so",
}


def copyMusl():
    print("======= start prepare shared library")
    for source in _muslLibs:
        shutil.copy(
            XOS_CROSSTOOL_TOOLCHAIN_LIBDIR + "/" + source,
            XOS_FULL_DIST_TARGET_PATH_ROOT + "/lib/" + source,
        )
        print(
            "copy libs",
            XOS_CROSSTOOL_TOOLCHAIN_LIBDIR + "/" + source,
            "to",
            XOS_FULL_DIST_TARGET_PATH_ROOT + "/lib/" + source,
        )
    for source in _muslLibLinks:
        target = Path("./" + _muslLibLinks[source])
        symlink = Path(XOS_FULL_DIST_TARGET_PATH_ROOT + "/lib/" + source)
        symlink.symlink_to(target)
        print("make symlink to", symlink, "to", target)


if __name__ == "__main__":
    # shutil.copyfile()
    mkdirRoot()
    copyMusl()
