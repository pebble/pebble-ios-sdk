//
//  NSJSONSerialization+ObjectWithNString.m
//  Ejecta
//
//  Created by matth on 7/19/13.
//
//

#import "NSJSONSerialization+ObjectWithNString.h"

@implementation NSJSONSerialization (ObjectWithNString)

+ (id)JSONObjectWithString:(NSString *)jsonString options:(NSJSONReadingOptions)opt error:(NSError **)error
{
  NSData *jsonData = [jsonString dataUsingEncoding:NSUnicodeStringEncoding allowLossyConversion:YES];
  
  return [NSJSONSerialization JSONObjectWithData:jsonData options:kNilOptions error:error];
}

+ (NSString*)stringWithNSDictionary:(NSDictionary*)dictionary {
  NSError *error;
  
  NSData *jsonData = [NSJSONSerialization dataWithJSONObject:dictionary
                                                     options:0
                                                       error:&error];
  
  if (!jsonData) {
    return nil;
  }
  
  return [[NSString alloc]initWithBytes:[jsonData bytes] length:[jsonData length] encoding:NSUTF8StringEncoding];
}

@end
