set -ex
cmake --build . --target clean
cmake .
make
make test
