//
// Created by Tony Cheng on 10/27/16.
// Copyright (c) 2016 Tony Cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "SWConstants.h"
#import <UIKit/UIKit.h>

@class AVCaptureDevice;

@protocol SWAVSourceDelegate <NSObject>
- (void)pixelBufferReady:(CVPixelBufferRef)pixelBuffer;
@end

@interface SWAVSource : NSObject

/// exposed AVFoundation properties
@property (nonatomic) dispatch_queue_t videoSessionQueue;
@property (nonatomic) dispatch_queue_t audioSessionQueue;

@property (nonatomic, strong) AVCaptureSession *captureSession;
@property (nonatomic, strong) AVCaptureDevice *currentCaptureDevice;

@property (nonatomic, strong) AVCaptureDeviceInput *videoDeviceInput;
@property (nonatomic, strong) AVCaptureVideoDataOutput *videoDataOutput;

@property (nonatomic, strong) AVCaptureDeviceInput *audioDeviceInput;
@property (nonatomic, strong) AVCaptureAudioDataOutput *audioDataOutput;
@property (nonatomic, weak) id <SWAVSourceDelegate> delegate;

- (void)startWithCamera:(AVCaptureDevice *)device;
- (void)startWithCamera:(AVCaptureDevice *)device sessionPreset:(NSString *)preset;

- (void)stop;
- (void)changeToCamera:(AVCaptureDevice *)device;
- (AVCaptureDevicePosition)currentPosition;

@end
