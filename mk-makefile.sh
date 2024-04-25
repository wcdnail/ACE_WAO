#!/bin/bash

#
# pacman -Syu --noconfirm
# pacman -S --noconfirm mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-clang \
#                       autoconf autoconf-archive automake mingw-w64-ucrt-x86_64-make \
#                       mingw-w64-ucrt-x86_64-libtool mingw-w64-ucrt-x86_64-pkg-config \
#                       mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja \
#                       mingw-w64-ucrt-x86_64-make
#

SOURCE_DIR=`pwd`
SOURCE_DIR_NAME=`basename $SOURCE_DIR`
COMPUTER_NAME=`hostname`
BUILD_OS=`uname -o`

if [ "$BUILD_OS" == "Msys" ]; then
    #ACE_C_COMPILER=C:/msys64/usr/bin/gcc.exe
    #ACE_CXX_COMPILER=C:/msys64/usr/bin/g++.exe
    ACE_C_COMPILER=/ucrt64/bin/clang.exe
    ACE_CXX_COMPILER=/ucrt64/bin/clang++.exe
else
    ACE_C_COMPILER=/usr/bin/clang
    ACE_CXX_COMPILER=/usr/bin/clang++
    #ACE_C_COMPILER=/usr/bin/gcc
    #ACE_CXX_COMPILER=/usr/bin/g++
fi

echo -ne "      VCPKG_ROOT : $VCPKG_ROOT\n"
echo -ne "      SOURCE_DIR : $SOURCE_DIR\n"
echo -ne " SOURCE_DIR_NAME : $SOURCE_DIR_NAME\n"
echo -ne "  ACE_C_COMPILER : $ACE_C_COMPILER\n"
echo -ne "ACE_CXX_COMPILER : $ACE_CXX_COMPILER\n"
echo -ne "   COMPUTER_NAME : $COMPUTER_NAME\n"
echo -ne "        BUILD_OS : $BUILD_OS\n"

mkdir -p ../${SOURCE_DIR_NAME}-build
pushd ../${SOURCE_DIR_NAME}-build

# -G "Unix Makefiles"

cmake -G "Ninja" \
-DCMAKE_BUILD_TYPE:STRING="Debug" \
-DCMAKE_CONFIGURATION_TYPES:STRING="Debug" \
-DCMAKE_C_COMPILER:FILEPATH=$ACE_C_COMPILER \
-DCMAKE_CXX_COMPILER:FILEPATH=$ACE_CXX_COMPILER \
-DBLD_COMPUTER_NAME="$COMPUTER_NAME" \
-DCMAKE_INSTALL_PREFIX="INSTALLED" \
$SOURCE_DIR

popd
