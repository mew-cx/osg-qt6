#! /bin/bash -x

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
git checkout 2025.01.13

echo "set(osg_OPENGL_PROFILE GLCORE)" >> triplets/x64-windows.cmake
#git status
#git diff

./bootstrap-vcpkg.sh
