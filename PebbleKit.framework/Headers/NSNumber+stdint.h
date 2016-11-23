//
//  NSNumber+stdint.h
//  PebbleKit
//
//  Created by Martijn The on 3/20/13.
//  Copyright (c) 2013 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

/**
 * This category exposes the capabilities the underlying CFNumber to explicitely
 * store the signedness and the width of the storage.
 */
@interface NSNumber (PBStandardIntegerExtensions)

/**
 * Interprets the receiver as a 32-bits wide, unsigned integer.
 */
@property (readonly) uint32_t pb_uint32Value;

/**
 * Interprets the receiver as a 16-bits wide, unsigned integer.
 */
@property (readonly) uint16_t pb_uint16Value;

/**
 * Interprets the receiver as a 8-bits wide, unsigned integer.
 */
@property (readonly) uint8_t pb_uint8Value;

/**
 * Interprets the receiver as a 32-bits wide, signed integer.
 */
@property (readonly) int32_t pb_int32Value;

/**
 * Interprets the receiver as a 16-bits wide, signed integer.
 */
@property (readonly) int16_t pb_int16Value;

/**
 * Interprets the receiver as a 8-bits wide, signed integer.
 */
@property (readonly) int8_t pb_int8Value;

/**
 * Gets whether the number that is stored by the receiver should be interpreted
 * as a floating pointer number or not.
 */
@property (readonly, getter=pb_isFloat) BOOL pb_float;

/**
 * Gets whether the number that is stored by the receiver should be interpreted
 * as a signed integer or not.
 */
@property (readonly, getter=pb_isSigned) BOOL pb_signed;

/**
 * Gets the width in bytes of the integer that is stored by the receiver.
 */
@property (readonly) uint8_t pb_byteWidth;

/**
 * Creates an NSNumber with a 32-bits wide, unsigned integer.
 *
 * @param value The value for the created number.
 */
+ (NSNumber *)pb_numberWithUint32:(uint32_t)value;

/**
 * Creates an NSNumber with a 16-bits wide, unsigned integer.
 *
 * @param value The value for the created number.
 */
+ (NSNumber *)pb_numberWithUint16:(uint16_t)value;

/**
 * Creates an NSNumber with a 8-bits wide, unsigned integer.
 *
 * @param value The value for the created number.
 */
+ (NSNumber *)pb_numberWithUint8:(uint8_t)value;

/**
 * Creates an NSNumber with a 32-bits wide, signed integer.
 *
 * @param value The value for the created number.
 */
+ (NSNumber *)pb_numberWithInt32:(int32_t)value;

/**
 * Creates an NSNumber with a 16-bits wide, signed integer.
 *
 * @param value The value for the created number.
 */
+ (NSNumber *)pb_numberWithInt16:(int16_t)value;

/**
 * Creates an NSNumber with a 8-bits wide, signed integer.
 *
 * @param value The value for the created number.
 */
+ (NSNumber *)pb_numberWithInt8:(int8_t)value;

@end


@interface NSNumber (PBStandardIntegerExtensionsDeprecated)

- (uint32_t)uint32Value DEPRECATED_MSG_ATTRIBUTE("Use pb_uint32Value");
- (uint16_t)uint16Value DEPRECATED_MSG_ATTRIBUTE("Use pb_uint16Value");
- (uint8_t)uint8Value DEPRECATED_MSG_ATTRIBUTE("Use pb_uint8Value");
- (int32_t)int32Value DEPRECATED_MSG_ATTRIBUTE("Use pb_int32Value");
- (int16_t)int16Value DEPRECATED_MSG_ATTRIBUTE("Use pb_int16Value");
- (int8_t)int8Value DEPRECATED_MSG_ATTRIBUTE("Use pb_int8Value");
+ (NSNumber *)numberWithUint32:(uint32_t)value DEPRECATED_MSG_ATTRIBUTE("Use pb_numberWithUint32:");
+ (NSNumber *)numberWithUint16:(uint16_t)value DEPRECATED_MSG_ATTRIBUTE("Use pb_numberWithUint16:");
+ (NSNumber *)numberWithUint8:(uint8_t)value DEPRECATED_MSG_ATTRIBUTE("Use pb_numberWithUint8:");
+ (NSNumber *)numberWithInt32:(int32_t)value DEPRECATED_MSG_ATTRIBUTE("Use pb_numberWithInt32:");
+ (NSNumber *)numberWithInt16:(int16_t)value DEPRECATED_MSG_ATTRIBUTE("Use pb_numberWithInt16:");
+ (NSNumber *)numberWithInt8:(int8_t)value DEPRECATED_MSG_ATTRIBUTE("Use pb_numberWithInt8:");
- (BOOL)isFloat DEPRECATED_MSG_ATTRIBUTE("Use pb_isFloat");
- (BOOL)isSigned DEPRECATED_MSG_ATTRIBUTE("Use pb_isSigned");
- (uint8_t)width DEPRECATED_MSG_ATTRIBUTE("Use pb_byteWidth");

@end

NS_ASSUME_NONNULL_END
