#!/bin/sh

set -e

SF_FAT_BUILT_PRODUCTS_DIR="$BUILD_ROOT/$CONFIGURATION-iphoneos+iphonesimulator"
SF_IPHONE_BUILT_PRODUCTS_DIR="$BUILD_ROOT/$CONFIGURATION-iphoneos"
SF_SIMULATOR_BUILT_PRODUCTS_DIR="$BUILD_ROOT/$CONFIGURATION-iphonesimulator"

mkdir -p "${SF_FAT_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/A/Headers"
mkdir -p "${SF_IPHONE_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/A/Headers"
mkdir -p "${SF_SIMULATOR_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/A/Headers"

# Link the "Current" version to "A"
/bin/ln -sfh A "${SF_FAT_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/Current"
/bin/ln -sfh Versions/Current/Headers "${SF_FAT_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Headers"
/bin/ln -sfh "Versions/Current/${PRODUCT_NAME}" "${SF_FAT_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/${PRODUCT_NAME}"

/bin/ln -sfh A "${SF_IPHONE_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/Current"
/bin/ln -sfh Versions/Current/Headers "${SF_IPHONE_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Headers"
/bin/ln -sfh "Versions/Current/${PRODUCT_NAME}" "${SF_IPHONE_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/${PRODUCT_NAME}"

/bin/ln -sfh A "${SF_SIMULATOR_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/Current"
/bin/ln -sfh Versions/Current/Headers "${SF_SIMULATOR_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Headers"
/bin/ln -sfh "Versions/Current/${PRODUCT_NAME}" "${SF_SIMULATOR_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/${PRODUCT_NAME}"

# The -a ensures that the headers maintain the source modification date so that we don't constantly
# cause propagating rebuilds of files that import these headers.
/bin/cp -a "${TARGET_BUILD_DIR}/${PUBLIC_HEADERS_FOLDER_PATH}/" "${SF_FAT_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/A/Headers"
/bin/cp -a "${TARGET_BUILD_DIR}/${PUBLIC_HEADERS_FOLDER_PATH}/" "${SF_IPHONE_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/A/Headers"
/bin/cp -a "${TARGET_BUILD_DIR}/${PUBLIC_HEADERS_FOLDER_PATH}/" "${SF_SIMULATOR_BUILT_PRODUCTS_DIR}/${PRODUCT_NAME}.framework/Versions/A/Headers"
