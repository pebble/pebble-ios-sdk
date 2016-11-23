//
//  PBDataLoggingService.h
//  PebbleKit
//
//  Created by Martijn The on 7/19/13.
//  Copyright (c) 2013 Pebble Technology. All rights reserved.
//

#import "PBDefines.h"

NS_ASSUME_NONNULL_BEGIN

@class PBWatch;

/**
 * Data logging datatypes.
 */
typedef NS_ENUM(uint8_t, PBDataLoggingType) {
  //! Array of bytes
  PBDataLoggingTypeByteArray = 0,
  //! unsigned integer
  PBDataLoggingTypeUInt = 2,
  //! signed integer
  PBDataLoggingTypeInt = 3,
};

/**
 * The metadata of a data logging session. Used to identify a session.
 */
PB_EXTERN_CLASS @interface PBDataLoggingSessionMetadata : NSObject <NSSecureCoding, NSCopying>

/**
 * A tag associated with the session.
 */
@property (nonatomic, readonly) uint32_t tag;

/**
 * The timestamp of the moment the session was created by the watchapp.
 */
@property (nonatomic, readonly) uint32_t timestamp;

/**
 * The type of data stored in this session.
 */
@property (nonatomic, readonly) PBDataLoggingType type;

/**
 * The size of a data item.
 */
@property (nonatomic, readonly) uint16_t itemSize;

/**
 * The serial number of the watch that created the sessions.
 */
@property (nonatomic, copy, readonly) NSString *serialNumber;

/**
 * Creates a new data logging session metadata object, given all its property values.
 * This method is provided to create a metadata object that can be used to
 * compare it with a metadata object that is passed into one of the
 * PBDataLoggingServiceDelegate methods.
 * @param tag The tag associated with the session
 * @param timestamp The timestamp of the creation of the session
 * @param type The type of data stored in the session
 * @param itemSize The size of a data item
 * @param serialNumber The serial number of the watch that created the session
 * @return A session metadata object with the specified information
 */
+ (instancetype)metadataWithTag:(uint32_t)tag
                      timestamp:(uint32_t)timestamp
                           type:(PBDataLoggingType)type
                       itemSize:(uint16_t)itemSize
                   serialNumber:(NSString *)serialNumber;

/**
 * Tests the equality of the recipient and the given object.
 *
 * This method can be used to compare two sessions’ metadata objects to check
 * whether they are referring to the same session or not.
 *
 * @param object The object to check against.
 *
 * @return `YES` if all the property values of the receiver are equal to the
 *         property values of the other object.
 */
- (BOOL)isEqual:(nullable id)object;

/**
 * Tests the equality of two data logging sessions’ metadata objects.
 *
 * This method can be used to compare two sessions’ metadata objects to check
 * whether they are referring to the same session or not.
 *
 * @note Equivalent to -[PBDataLoggingSessionMetadata isEqual:]
 *
 * @param sessionMetadata The session metadata to compare against.
 *
 * @return `YES` if all the property values of the receiver are equal to the
 *         property values of the given session.
 */
- (BOOL)isEqualToDataLoggingSessionMetadata:(PBDataLoggingSessionMetadata *)sessionMetadata;

@end


@class PBDataLoggingService;

/**
 * Data logging delegate protocol. The object that implements this protocol
 * is responsible for handling incoming data.
 */
@protocol PBDataLoggingServiceDelegate <NSObject>
@optional

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param bytes Pointer to the array of bytes.
 * The array contains (numberOfItems * session.itemSize) bytes.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasByteArrays:(const uint8_t *const)bytes numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param data Pointer to the array of UInt8`s.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasUInt8s:(const uint8_t[])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param data Pointer to the array of UInt16`s.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasUInt16s:(const uint16_t[])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param data Pointer to the array of UInt32`s.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasUInt32s:(const uint32_t[])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param data Pointer to the array of SInt8`s.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasSInt8s:(const int8_t[])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param data Pointer to the array of SInt16`s.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasSInt16s:(const int16_t[])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time there is data available that has not been
 * consumed yet.
 * @param service The data logging service.
 * @param data Pointer to the array of SInt32`s.
 * @param numberOfItems The number of items that the array contains.
 * @param session The metadata of the session.
 * @return YES if the data was consumed and the service can discard the data.
 * Return NO if the data was not be consumed after the method returned.
 * If NO is returned, the next time this callback is invoked for the session, the
 * data argument will (also) contain the data of the items of the previous
 * invocation of the callback.
 */
- (BOOL)dataLoggingService:(PBDataLoggingService *)service hasSInt32s:(const int32_t[])data numberOfItems:(uint16_t)numberOfItems forDataLoggingSession:(PBDataLoggingSessionMetadata *)session;

/**
 * Called by the service every time a session is finished.
 * This is guaranteed to be called only after all data has been received and
 * consumed by the application.
 * @param service The data logging service.
 * @param session The metadata of the session.
 */
- (void)dataLoggingService:(PBDataLoggingService *)service sessionDidFinish:(PBDataLoggingSessionMetadata *)session;

@end


/**
 * The data logging service. Assign a delegate object in order to receive
 * data from your watchapp.
 */
PB_EXTERN_CLASS @interface PBDataLoggingService : NSObject

/**
 * The delegate that has the responsility of handling callbacks from the
 * data logging service.
 */
@property (atomic, readwrite, weak) id<PBDataLoggingServiceDelegate> delegate;

/**
 * Sets the queue on which delegate methods will be executed.
 * Callbacks are intended to be processed in the order as they come in, so it
 * you must use a serial queue. If set to nil (default) the main queue is used.
 * @param delegateQueue The queue on which the delegate methods will be executed.
 */
- (void)setDelegateQueue:(dispatch_queue_t)delegateQueue;

/**
 * Query the latestConnectedWatch for data logging data.
 *
 * @deprecated Use pollForDataFromWatch:
 */
- (void)pollForData __attribute__((deprecated("Method deprecated. Use `pollForDataFromWatch:`")));

/**
 * Query the watch for data logging data.
 * @param watch The watch to query data from.
 */
- (void)pollForDataFromWatch:(PBWatch *)watch;

@end


@interface PBDataLoggingSessionMetadata (Unavailable)

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
