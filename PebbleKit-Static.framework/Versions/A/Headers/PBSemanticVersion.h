//
//  PBSemanticVersion.h
//  PebbleKit
//
//  Created by Mario Carranca on 2015-12-11.
//  Copyright © 2015 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A version number that follows the rules of semantic versioning.
 *
 * The version number is supposed to have three components and an optional
 * suffix.
 */
PB_EXTERN_CLASS @interface PBSemanticVersion : NSObject

/** The version major number */
@property (nonatomic, assign, readonly) NSUInteger majorVersion;

/** The version minor number */
@property (nonatomic, assign, readonly) NSUInteger minorVersion;

/** The version revision number */
@property (nonatomic, assign, readonly) NSUInteger revisionVersion;

/**
 * The version suffix string.
 *
 * @note If a version tag string does not contain a suffix, it will be set to
 *       an empty string.
 *
 * The release suffix is not used in the -compare: or -isEqual: methods.
 */
@property (nonatomic, copy, readonly) NSString *suffix;

/**
 * Returns a new instance by parsing the input.
 *
 * @param versionString  Expected format: `major.minor.revision-sffix`.
 *
 *                       Example: "2.0.1-rc2"
 *
 *                       If a parsing error occurs, `nil` will be returned.
 *
 * @return A version or `nil` if some error happen.
 */
- (nullable instancetype)initWithVersionString:(NSString *)versionString;

/**
 * Returns a new instance by using the given components.
 *
 * @param major The version major number.
 * @param minor The version minor number.
 * @param revision The version revision number.
 * @param suffix The version suffix. Can be nil.
 */
- (instancetype)initWithMajor:(NSUInteger)major
                        minor:(NSUInteger)minor
                     revision:(NSUInteger)revision
                       suffix:(nullable NSString *)suffix;

/**
 * Compares the receiver to another version object.
 *
 * @param aVersion The version to compare with the receiver.
 *
 * @return `NSOrderedAscending` if the value of aVersion is greater than the
 *         receiver’s, `NSOrderedSame` if they’re equal, and
 *         `NSOrderedDescending` if the value of `aVersion` is less than the
 *         receiver’s.
 */
- (NSComparisonResult)compare:(PBSemanticVersion *)aVersion;

/**
 * Returns if the the receiver is equal or newer than the given version.
 *
 * @param other Version number to compare against.
 *
 * @return `YES` if the receiver is equal or newer. `NO` otherwise.
 */
- (BOOL)isEqualOrNewer:(PBSemanticVersion *)other;

/**
 * Returns if the receiver is strictly newer than the given version.
 *
 * @param other Version number to compare against.
 *
 * @return `YES` if the receiver is stricly newer. `NO` otherwise.
 */
- (BOOL)isNewer:(PBSemanticVersion *)other;

@end


@interface PBSemanticVersion (Unavailable)

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
