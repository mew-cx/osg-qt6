#! /bin/bash -x

# 0_BOOTSTRAP_VCPKG.sh #######################################3

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
git checkout 2025.01.13
echo "set(osg_OPENGL_PROFILE GLCORE)" >> triplets/x64-windows.cmake
#git status
#git diff
./bootstrap-vcpkg.sh
export VCPKG_ROOT=$(pwd)
cd -

# 1_INSTALL_DEPS.sh ##########################################3

cd "${VCPKG_ROOT}"
time ./vcpkg install "osgearth[tools]:x64-windows" "qtbase:x64-windows" "qttools:x64-windows"
cd -

# 2_CMAKE.sh #################################################3

cmake -B _BUILD -S . -DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"

# 3_BUILD.sh #################################################3

cmake --build build

#EOF
