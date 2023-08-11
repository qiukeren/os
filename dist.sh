

rm -rf dist


export XOS_BUILD_TARGET=riscv64

set -ex
cmake --build . --target clean
cmake . -DXOS_BUILD_TARGET=${XOS_BUILD_TARGET}
make -j4
# make test

./dist.py

unset XOS_BUILD_TARGET

export XOS_BUILD_TARGET=x86_64

set -ex
cmake --build . --target clean
cmake . -DXOS_BUILD_TARGET=${XOS_BUILD_TARGET}
make -j4
# make test

./dist.py

unset XOS_BUILD_TARGET