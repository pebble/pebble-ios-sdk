//
//  EAAccessoryFramework+OCMock.m
//  PebbleKit
//
//  Created by Martijn The on 7/30/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import "EAAccessoryFramework+OCMock.h"
#import <OCMock/OCMock.h>

@interface EAAccessory (Private)
- (BOOL)isPebble; /* Defined in PBPebbleCentral.m */
@end

@implementation EAAccessory (OCMock)
static id MockDelegate = nil;

+ (EAAccessory*)pebbleMock {
  id accessory = [OCMockObject mockForClass:[EAAccessory class]];
  BOOL value = YES;
  [(EAAccessory*)[[accessory stub] andReturnValue:OCMOCK_VALUE(value)] isPebble];
  [[[accessory stub] andReturn:@[@"com.getpebble.private", @"com.getpebble.public"]] protocolStrings];
  [[[accessory stub] andReturn: @"Pebble Technology Corp."] manufacturer];
  [[[accessory stub] andReturn: @"Pebble"] name];
  [[[accessory stub] andReturn: @"Pebble One"] modelNumber];
  [[[accessory stub] andReturn: @"0123456789"] serialNumber];
  [[[accessory stub] andReturn: @"1.2.3"] firmwareRevision];
  [[[accessory stub] andReturn: @"3.2.1"] hardwareRevision];
  [[[accessory stub] andReturnValue:OCMOCK_VALUE(value)] isConnected];
  [[accessory stub] setDelegate:[OCMArg checkWithBlock:^(id value) {
    MockDelegate = value;
    return YES;
  }]];
  [[[accessory stub] andCall:@selector(pebbleDelegate) onObject:self] delegate];
  NSUInteger connectionID = 1;
  [[[accessory stub] andReturnValue:OCMOCK_VALUE(connectionID)] connectionID];
  return accessory;
}
- (id)pebbleDelegate {
  return MockDelegate;
}
@end

@implementation EAAccessoryManager (OCMock)
+ (EAAccessoryManager*)mockManager {
  id manager = [OCMockObject mockForClass:[EAAccessoryManager class]];
  id accessory = [EAAccessory pebbleMock];
  [[[manager stub] andReturn:@[accessory]] connectedAccessories];
  [[manager stub] registerForLocalNotifications];
  [[manager stub] unregisterForLocalNotifications];
  return manager;
}
@end

@implementation EASession (OCMock)

+ (EASession*)mockSessionWithAccessory:(EAAccessory*)mockAccessory protocolString:(NSString*)protocol inputStream:(NSInputStream*)inStream outputStream:(NSOutputStream*)outStream {
  id session = [OCMockObject mockForClass:[EASession class]];
  [[[session stub] andReturn:mockAccessory] accessory];
  [[[session stub] andReturn:protocol] protocolString];
  [[[session stub] andReturn:inStream] inputStream];
  [[[session stub] andReturn:outStream] outputStream];
  return session;
}

@end