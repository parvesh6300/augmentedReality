//
// Created by Tony Cheng on 1/10/17.
// Copyright (c) 2017 Tracks Media, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SWFaceTrackingModel : NSObject
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *type;
@property (nonatomic) int numOfFrames;
@property (nonatomic) int fps;
@property (nonatomic) float scale;
@property (nonatomic) int pinningPoint;

- (NSString *)localPath;
- (BOOL)isInstalled;

- (NSString *)objPath;
- (NSString *)textureFilePath;
- (NSString *)textureSequenceFirstFilePath;
- (NSString *)textureAtlasPath;
- (NSString *)scnPath;
- (NSString *)filterFilePath;

@end

@interface SWFaceTrackingEntry : NSObject
@property (nonatomic, copy) NSString *name;
@property (nonatomic, strong) NSArray <NSString *> *models;
- (BOOL)isInstalled;
- (NSURL *)thumbnailURL;
@end

@interface SWFaceTrackingPack : NSObject
- (NSString *)packName;
- (NSArray <SWFaceTrackingEntry *>*)items;
- (NSURL *)thumbnailURL;
@end

#define kSWModelManagerEntriesUpdatedNotification @"kSWModelManagerEntriesUpdatedNotification"
#define kSWModelManagerModelDownloadedNotification @"kSWModelManagerModelDownloadedNotification"

@interface SWModelManager : NSObject

@property (nonatomic, copy) NSString *remotePath;

+ (SWModelManager *)sharedInstance;

/*
 * Use these read methods to load bundled Model and Objects plists
 */
+ (void)readModelsPlistAtPath:(NSString *)path;
+ (void)readObjectsPlistAtPath:(NSString *)path;

/*
 * the read plist functions read the local cached plists
 */
+ (void)readModelsPlist;
+ (void)readEntriesPlist;

/*
 * these will actually fetch from the remote path and write to the local plists
 */
+ (void)fetchModelsPlist;
+ (void)fetchEntriesPlist;

+ (void)downloadModelsForEntry:(SWFaceTrackingEntry *)entry;

+ (NSArray <SWFaceTrackingPack *> *)stickers;
+ (NSArray <SWFaceTrackingPack *> *)masks;
+ (NSArray <SWFaceTrackingEntry *> *)filters;

+ (NSArray <SWFaceTrackingModel *> *)modelsForEntry:(SWFaceTrackingEntry *)entry;

@end
