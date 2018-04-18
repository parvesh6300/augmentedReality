//
// Created by Tony Cheng on 5/23/17.
// Copyright (c) 2017 Tony Cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SceneKit/SceneKit.h>
#import <AVFoundation/AVFoundation.h>

@interface SWRenderer : NSObject <AVCaptureAudioDataOutputSampleBufferDelegate>

@property (nonatomic, readonly) BOOL isRecording;
@property (nonatomic) BOOL disableAudio;
@property (nonatomic, strong) AVCaptureAudioDataOutput *audioDataOutput;

+ (instancetype)rendererWithSceneView:(SCNView *)scene;

- (void)startRecordingAtOutputURL:(NSURL *)outputURL recordAudio:(BOOL)recordAudio;
- (void)finishRecordingWithCompletionHandler:(void(^)(BOOL success, NSURL *fileURL))completionHandler;
- (UIImage *)imageFromCurrentSceneView;

@end