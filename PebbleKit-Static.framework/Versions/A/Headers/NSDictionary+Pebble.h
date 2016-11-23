//
//  NSDictionary+Pebble.h
//  PebbleKit
//
//  Created by Martijn The on 3/20/13.
//  Copyright (c) 2013 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NSDictionary (Pebble)

/**
 * Serializes the receiver into a Pebble dict.
 *
 * The receiver dictionary must comply to the following constraints:
 *
 * - The keys must be instances of `NSNumber`. Their `-unsignedLongValue`
 *   return value will be used as final key.
 * - The values must be instances of either `NSString`, `NSData` or
 *   `NSNumber`. Use the `NSNumber (stdint)` category to specify the
 *   signedness and width of `NSNumber`.
 *
 * @param error Pointer to an `NSError *` that will be set in case there was an
 *              error creating the dictionary. Possible error codes:
 *
 *              - PBErrorCodeDictionaryUnsupportedKeyClass
 *              - PBErrorCodeDictionaryUnsupportedValueClass
 *              - PBErrorCodeDictionaryUnsupportedValueClass
 *
 * @see [NSData(Pebble) pb_dictionaryFromPebbleDictionaryDataWithError:]
 */
- (nullable NSData *)pb_pebbleDictionaryData:(NSError * __autoreleasing *)error;

@end

@interface NSData (Pebble)

/**
 * Interprets the receiver as Pebble dict data and deserializes it into an NSDictionary.
 *
 * @param error Pointer to an `NSError *` that will be set after the method has
 *              returned in case there was an error. Possible error codes:
 *
 *              - PBErrorCodeDictionaryInternalConsistency
 *
 * @see [NSDictionary(Pebble) pb_pebbleDictionaryData:]
 */
- (nullable NSDictionary *)pb_dictionaryFromPebbleDictionaryDataWithError:(NSError * __autoreleasing *)error;

@end


@interface NSDictionary (PebbleDeprecated)

- (nullable NSData *)pebbleDictionaryData:(NSError * __autoreleasing *)error DEPRECATED_MSG_ATTRIBUTE("Use pb_pebbleDictionaryData:");

@end


@interface NSData (PebbleDeprecated)

- (nullable NSDictionary *)dictionaryFromPebbleDictionaryDataWithError:(NSError * __autoreleasing *)error DEPRECATED_MSG_ATTRIBUTE("Use pb_dictionaryFromPebbleDictionaryDataWithError:");

@end

NS_ASSUME_NONNULL_END
