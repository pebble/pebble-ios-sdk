//
//  PBBitmap.h
//  PebbleKit
//
//  Created by Martijn The on 3/24/13.
//  Copyright (c) 2013 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBDefines.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>
#import <PebbleKit/gtypes.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  Helper class to convert a UIImage to Pebble bitmap pixel data and GBitmap metadata.
 *  Refer to the documentation of Pebble's native watch app SDK on the GBitmap format.
 */

PB_EXTERN_CLASS @interface PBBitmap : NSObject

/**
 *  The pixel data of the bitmap.
 *  This corresponds to the data as pointed to by GBitmap's `addr` field.
 */
@property (nonatomic, readonly, strong) NSData *pixelData;

/**
 *  The number of bytes per row.
 *  Always a multiple of 4 bytes.
 */
@property (nonatomic, readonly, assign) uint16_t rowSizeBytes;

/**
 *  Bitfield of metadata flags.
 *  This corresponds to GBitmap's `info_flags` field.
 */
@property (nonatomic, readonly, assign) uint16_t infoFlags;

/**
 *  The box of bits inside `pixelData`, that contains
 *  the actual image data to use.
 *  This corresponds to GBitmap's `bounds` field.
 */
@property (nonatomic, readonly, assign) GRect bounds;

/**
 *  Factory method to create a PBBitmap from a UIImage instance.
 *  @param image The UIImage from which to create the PBBitmap
 */
+ (PBBitmap*)pebbleBitmapWithUIImage:(UIImage*)image;

@end

NS_ASSUME_NONNULL_END
