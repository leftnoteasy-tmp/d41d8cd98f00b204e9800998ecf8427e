autoreconf -fiv && autoscan && automake
mkdir build
rm -rf build/*
cd build
make clean
../configure
make
cd ..
