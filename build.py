#!/usr/bin/python3

import subprocess
from typing import List


def runException(cmd: List[str], cwd: str):
    print("run in", cwd, cmd)
    res = subprocess.run(cmd, stdin=subprocess.PIPE, stderr=subprocess.STDOUT)
    if res.returncode != 0:
        raise Exception("run error {}".format(res))


targetFiles = ["shell/shell", "editor/editor",
               "vinit/vinit", "init/init", "httpserver/httpserver"]

runException(["rm", "-rf", "target"], ".")
runException(["cmake", "--build", ".", "--target", "clean"], ".")
runException(["cmake", "."], ".")
runException(["make"], ".")
runException(["mkdir", "target"], ".")
runException(["mkdir", "target/bin"], ".")

for file in targetFiles:
    runException(["cp", file, "target/bin"], ".")
