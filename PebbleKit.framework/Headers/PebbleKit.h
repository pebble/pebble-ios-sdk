//
//  PebbleKit.h
//  PebbleKit
//
//  Created by Martijn Thé on 4/24/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import <Foundation/Foundation.h>

//! Project version number for PebbleKit.
FOUNDATION_EXPORT double PebbleKitVersionNumber;

//! Project version string for PebbleKit.
FOUNDATION_EXPORT const unsigned char PebbleKitVersionString[];

#import "PBFirmwareVersion.h"

#import "PBWatch.h"
#import "PBWatch+AppMessages.h"
#import "PBWatch+Golf.h"
#import "PBWatch+Legacy.h"
#import "PBWatch+Ping.h"
#import "PBWatch+Sports.h"
#import "PBWatch+Version.h"

#import "PBPebbleCentral.h"
#import "PBPebbleCentral+DefaultCentral.h"

#import "PBBitmap.h"
#import "PBDataLoggingService.h"
#import "PBErrors.h"

#import "NSNumber+stdint.h"
#import "NSDictionary+Pebble.h"

#pragma mark - Legacy behavior
#import "PBFirmwareVersion+Legacy.h"
#import "PBPebbleCentral+Legacy.h"
