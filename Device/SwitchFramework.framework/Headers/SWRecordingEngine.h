//
// Created by Tony Cheng on 4/1/16.
// Copyright (c) 2016 kanvas. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

@class SWRecordingEngine;
@class SWAVSource;

typedef void(^RenderingProgressBlock)(double percent);
typedef void(^RenderingCompletionBlock)(BOOL success, NSURL *fileURL);
typedef void(^RenderingImageCompletionBlock)(BOOL success, UIImage *image);

@protocol RenderingEngineDelegate <NSObject>
- (void)renderingEngine:(SWRecordingEngine *)engine didTakeSnapshot:(id)sender; // for burst
- (void)renderingEngine:(SWRecordingEngine *)engine didFinishSnapshots:(id)sender; // after bursts are complete
@end

@interface SWRecordingEngine : NSObject

@property (nonatomic, weak) id<RenderingEngineDelegate> delegate;

/*
 * recordingView
 * Set this view for whatever view you wish to record.
 */
@property (nonatomic, strong) UIView *recordingView;

/*
 * set this to before recording to change the frame rate of video recordings
 *
 */
@property (nonatomic) NSInteger fps;

/*
 * The @x resolution of the output. Defaults to 1.0, setting it to [UIScreen mainScreen].scale will improve resolution but decrease performance
 */
@property (nonatomic) CGFloat scale;

/*
 * avSource
 * corresponds to a SWAVSource (AudioVideo Source). Required for audio to function properly.
 */
@property (nonatomic, strong) SWAVSource *avSource;

/*
 * outputURL
 * Do not set while recording. Will be set to default FinalVideo.mp4 if not set at startRecordingWithOutputURL:
 */
@property (nonatomic, strong) NSURL *outputURL;

/*
 * disableAudio
 * can be called while recording.
 */
@property (nonatomic) BOOL disableAudio;

/*
 * The UIImages array from burst mode
 */
@property (nonatomic, strong, readonly) NSMutableArray *gifImagesArray;

+ (SWRecordingEngine *)sharedInstance;

/*
 * checks if recordingView is set and whether the video is actually recording.
 */
- (BOOL)isRecordingView;

/*
 * Creates gifs of 10 frames.
 */
- (void)renderBurstWithProgressBlock:(RenderingProgressBlock)progressBlock completionBlock:(RenderingCompletionBlock)completionBlock;
- (void)renderPhotoWithCompletionBlock:(RenderingImageCompletionBlock)completionBlock;

/*
 * startRecordingWithCompletion: calls startRecordingWithOutputURL: with nil url. A nil url argument will use the default path at FinalVideo.mp4 in the Temporary directory.
 */
- (void)startRecordingWithCompletion:(void (^)(BOOL success))completionBlock;
- (void)startRecordingWithOutputURL:(NSURL *)url WithCompletion:(void (^)(BOOL success))completionBlock;

/*
 * stopRecordingWithCompletion:
 * this will complete the recording and return a success bool and a fileURL for the finished video. This will either be FinalVideo.mp4 or at the supplied OutputURL
 */
- (void)stopRecordingWithCompletion:(RenderingCompletionBlock)completionBlock;

/*
 * cancelRecordingWithCompletion: will cancel the recording, returning success on cancellation.
 */
- (void)cancelRecordingWithCompletion:(void (^)(BOOL success))completionBlock;

/*
 * This convenience method will loop smaller assets to be at least 7 seconds long. The minimum duration can also be specified
 */
- (void)loopAsset:(AVAsset *)asset completionBlock:(RenderingCompletionBlock)completionBlock;
- (void)loopAsset:(AVAsset *)asset toMinimumDuration:(NSTimeInterval)seconds completionBlock:(RenderingCompletionBlock)completionBlock;

@end
