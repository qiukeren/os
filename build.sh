set -ex
#cmake --build . --target clean
cmake .
make
make test

cd goinit
CGO_ENABLED=0 go build .
cd ..

cd gogetty
CGO_ENABLED=0 go build .
cd ..

