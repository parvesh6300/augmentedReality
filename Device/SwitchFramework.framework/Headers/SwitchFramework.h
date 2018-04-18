//
//  SwitchFramework.h
//  SwitchFramework
//
//  Created by Tony Cheng on 11/15/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for SwitchFramework.
FOUNDATION_EXPORT double SwitchFrameworkVersionNumber;

//! Project version string for SwitchFramework.
FOUNDATION_EXPORT const unsigned char SwitchFrameworkVersionString[];

#import <SwitchFramework/SWFace.h>
#import <SwitchFramework/SWFeature.h>
#import <SwitchFramework/SWEyeFeature.h>
#import <SwitchFramework/SWAttachable.h>
#import <SwitchFramework/SWStickerAttachable.h>
#import <SwitchFramework/SWMaskAttachable.h>
#import <SwitchFramework/SWEnvironmentAttachable.h>
#import <SwitchFramework/SWFilterAttachable.h>
#import <SwitchFramework/SWTrackingEngine.h>
#import <SwitchFramework/SWRecordingEngine.h>
#import <SwitchFramework/SWAVSource.h>
#import <SwitchFramework/SWAlertHandler.h>
#import <SwitchFramework/SWCommon.h>
#import <SwitchFramework/SWModelManager.h>
#import <SwitchFramework/SWRenderer.h>

@interface SwitchFramework : NSObject

+ (BOOL)initializeWithClientID:(NSString *)clientID signature:(NSString *)signature;
+ (BOOL)clientVerified;
+ (NSString *)clientID;
+ (NSString *)sdkVersion;

@end
