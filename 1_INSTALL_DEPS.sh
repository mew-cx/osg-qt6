#! /bin/bash -x

cd vcpkg

./bootstrap-vcpkg.sh
time ./vcpkg install osgearth[tools]:x64-windows
time ./vcpkg install qtbase:x64-windows
time ./vcpkg install qttools:x64-windows
