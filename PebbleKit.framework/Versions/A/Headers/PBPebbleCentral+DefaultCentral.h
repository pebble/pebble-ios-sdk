//
//  PBPebbleCentral+DefaultCentral.h
//  PebbleKit
//
//  Created by Marcel Jackwerth on 07/09/15.
//  Copyright (c) 2015 Pebble Technology. All rights reserved.
//

#import <PebbleKit/PBPebbleCentral.h>

NS_ASSUME_NONNULL_BEGIN

@interface PBPebbleCentral (DefaultCentral)

/**
 @returns The default central singleton instance.
 */
+ (instancetype)defaultCentral;

@end

NS_ASSUME_NONNULL_END
