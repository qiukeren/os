

rm -rf dist

#rm -rf CMakeCache.txt
#cmake ; make ; make test


export XOS_BUILD_TARGET=x86_64

set -ex
cmake --build . --target clean
cmake . -DXOS_BUILD_TARGET=${XOS_BUILD_TARGET}
make -j4
 make test

./dist.py

unset XOS_BUILD_TARGET

exit

export XOS_BUILD_TARGET=riscv64


cmake --build . --target clean
set -ex
cmake --debug-output . -DXOS_BUILD_TARGET=${XOS_BUILD_TARGET}
make SHELL="bash -x" VERBOSE=1
# make test
exit;

./dist.py

unset XOS_BUILD_TARGET
