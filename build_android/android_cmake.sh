#!/bin/bash

#export ANDROID_NDK=path/to/NDK
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../android.toolchain.cmake \
-DANDROID_TOOLCHAIN_NAME=aarch64-linux-android-4.9 \
-DANDROID_ABI=arm64-v8a \
-DANDROID_NATIVE_API_LEVEL=android-24 \
-DCMAKE_BUILD_TYPE=Release ../..
