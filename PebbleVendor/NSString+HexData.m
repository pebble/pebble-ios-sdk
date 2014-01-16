//
//  NSString+HexData.m
//  PebblePrivateKit
//
//  Created by Martijn The on 11/19/12.
//  Copyright (c) 2012 Pebble Technology. All rights reserved.
//

#import "NSString+HexData.h"

@implementation NSString (HexData)

- (NSData*) hexData {
  const NSUInteger length = [self length];
  NSMutableData* data = [NSMutableData dataWithCapacity:length / 2];
  
  for (int idx = 0; idx + 2 <= length; idx += 2) {
    NSRange range = NSMakeRange(idx, 2);
    NSString *hexStr = [self substringWithRange:range];
    NSScanner *scanner = [NSScanner scannerWithString:hexStr];
    unsigned int intValue;
    [scanner scanHexInt:&intValue];
    [data appendBytes:&intValue length:1];
  }

  return data;
}

@end


@implementation NSData (HexString)

- (NSString*)hexString {
  NSUInteger length = [self length];
  NSMutableString *hashString = [NSMutableString stringWithCapacity:length * 2];
  // Not the most efficient way of doing it, but it works:
  uint8_t *bytes = (uint8_t *) [self bytes];
  for (int i = 0; i < length; i++) {
    [hashString appendFormat:@"%02x", bytes[i]];
  }
  return [NSString stringWithString:hashString];
}

@end