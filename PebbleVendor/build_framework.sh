#!/bin/sh

set -e
set +u
# Avoid recursively calling this script.
if [[ $SF_MASTER_SCRIPT_RUNNING ]]
then
    exit 0
fi
set -u
export SF_MASTER_SCRIPT_RUNNING=1

BUILD_ROOT=/tmp/PebbleVendor_build/build
SF_TARGET_NAME=PebbleVendor
SF_EXECUTABLE_PATH=libPebbleVendor.a
SF_WRAPPER_NAME=PebbleVendor.framework
SF_IPHONE_BUILT_PRODUCTS_DIR="$BUILD_ROOT/$CONFIGURATION-iphoneos"
SF_SIMULATOR_BUILT_PRODUCTS_DIR="$BUILD_ROOT/$CONFIGURATION-iphonesimulator"
SF_FAT_BUILT_PRODUCTS_DIR="$BUILD_ROOT/$CONFIGURATION-iphoneos+iphonesimulator"
SF_IPHONE_SDK_NAME=iphoneos7.0
SF_SIMULATOR_SDK_NAME=iphonesimulator7.0

# Build for iphone platform armv6 + armv7
xcodebuild -project "${PROJECT_FILE_PATH}" -target "${SF_TARGET_NAME}" -configuration "Release" -sdk ${SF_IPHONE_SDK_NAME} BUILD_DIR="${BUILD_ROOT}" OBJROOT="${OBJROOT}" BUILD_ROOT="${BUILD_ROOT}" ARCHS="armv6 armv7 armv7s" SYMROOT="${SYMROOT}" $ACTION

# Build the simulator platform i386
xcodebuild -project "${PROJECT_FILE_PATH}" -target "${SF_TARGET_NAME}" -configuration "Release" -sdk ${SF_SIMULATOR_SDK_NAME} BUILD_DIR="${BUILD_ROOT}" OBJROOT="${OBJROOT}" BUILD_ROOT="${BUILD_ROOT}" ARCHS="i386" SYMROOT="${SYMROOT}" $ACTION

# Smash the two static libraries into one fat binary and store it in the .framework
lipo -create "${SF_IPHONE_BUILT_PRODUCTS_DIR}/${SF_EXECUTABLE_PATH}" "${SF_SIMULATOR_BUILT_PRODUCTS_DIR}/${SF_EXECUTABLE_PATH}" -output "${SF_FAT_BUILT_PRODUCTS_DIR}/${SF_WRAPPER_NAME}/Versions/A/${SF_TARGET_NAME}"
