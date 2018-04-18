//
//  SWAttachable.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 2/7/17.
//  Copyright © 2017 Tony Cheng. All rights reserved.
//

@class SWFaceTrackingEntry;

@interface SWAttachable : NSObject

/*! attachablesFromSCNFilePath:
 *
 * This will load an array of attachables (but not add them to the tracking engine).
 * For the engine to detect a valid child node, it has to be either a valid vertex, or named "environment" or "camera". The camera child node should be of camera type
 *
 * @param scnFilePath
 * @return
 */
+ (NSArray <SWAttachable *> *)attachablesFromSCNFilePath:(NSString *)scnFilePath;

+ (NSArray <SWAttachable *> *)attachablesFromSWFaceTrackingEntry:(SWFaceTrackingEntry *)entry;


@end
