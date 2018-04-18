//
//  SWTrackingEngine.h
//  SwitchSceneKit
//
//  Created by Tony Cheng on 11/3/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import "SWCommon.h"
#import "SWTrackingModel.h"
#import <SceneKit/SceneKit.h>
#import "SWAttachable.h"
#import "SWStickerAttachable.h"
#import <AVFoundation/AVFoundation.h>

/*!
    @class SWTrackingEngine
 
    @brief This class provides face tracking and asset rendering capabilities.
 
    @discussion Use the function trackingModelForUIImage:renderObjectsToSCNView: to get tracking data like location, orientation, or facial expression. If also rendering assets, initialize a scene view with createSCNViewWithFrame: and load objects before calling trackingModelForUIImage:renderObjectsToSCNView:
 */
@interface SWTrackingEngine : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, strong) NSMutableArray *stickerAttachables;
@property (nonatomic, strong) NSMutableArray *maskAttachables;
@property (nonatomic, strong) NSMutableArray *environmentAttachables;
@property (nonatomic, strong) NSMutableArray *filterAttachables;

- (instancetype)init;

/*!
    @brief Initializes and returns a scene view object with the specified frame rectangle. All tracking engine functions that interact with a view use the last created scene view.
 
    @discussion Render calls within the tracking engine draw to the last created scene view. Sticker detection and movement use the dimensions of the last created scene view.
 
    @param frame
        A CGRect with the dimensions of the desired scene view.
 
    @return An initialized scene view object.
 */
- (SCNView *)SCNViewWithFrame:(CGRect)frame;

/*!
 * addAttachable: - adds an object to the SCNView. These attachables are tracked to the face depending on their tracked vertex
 * @param attachable
 */
- (void)addAttachable:(SWAttachable *)attachable;
- (void)addAttachables:(NSArray<SWAttachable *> *)attachables;

/*!
 * removeAttachable: - removes objects from the SCNView and stops tracking
 * valid attachables are stickers, environments and masks. Stickers track a point on the face. Environments are loaded into the SCNView but are not tracked. Masks are attached to the face mesh
 * @param attachable
 */
- (void)removeAttachable:(SWAttachable *)attachable;
- (void)removeAttachables:(NSArray<SWAttachable *> *)attachables;
- (void)removeAllAttachables;

/*!
 * @param position - position on the SCNView
 * @return SWStickerAttachable that corresponds to the point
 */
- (SWStickerAttachable *)stickerAttachableAtSCNViewPosition:(CGPoint)position;

/*!
 * transformStickerAttachable:
 * @brief these functions move a sticker around the screen based on screen coordinates and degrees. When transforming a sticker, the engine will pause tracking for that particular sticker until endTransformForStickerAttachable: is called
 * @param stickerAttachable
 * @param translation
 */
- (void)transformStickerAttachable:(SWStickerAttachable *)stickerAttachable withSCNViewTranslation:(CGPoint)translation;

/*!
 * @brief transformStickerAttachable: rotates the sticker given the euler angles (x, y, z) in radians
 */
- (void)transformStickerAttachable:(SWStickerAttachable *)stickerAttachable withEulerAngles:(SCNVector3)angles;

- (void)transformStickerAttachable:(SWStickerAttachable *)stickerAttachable withScale:(CGFloat)scale;
- (void)endTransformForStickerAttachable:(SWStickerAttachable *)stickerAttachable;

/*!
 * @brief Returns tracking data representation for a face in the specified image. If isRendering is YES, it will also track and render all objects loaded in the current SCNView.
 * @param pixelBuffer the pixel buffer input
 * @param isRendering determines whether to render tracked objects in SCNView
 * @return SWTrackingModel - more information can be found in the that header
 */
- (SWTrackingModel *)trackingModelForCVPixelBufferRef:(CVPixelBufferRef)pixelBuffer renderObjects:(BOOL)isRendering;

/*!
 * debug information
 */
- (void)printConfiguration;

@end

