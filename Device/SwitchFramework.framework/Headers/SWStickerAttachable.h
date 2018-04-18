//
//  SWStickerAttachable.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 2/7/17.
//  Copyright © 2017 Tony Cheng. All rights reserved.
//

#ifndef SWStickerAttachable_h
#define SWStickerAttachable_h


#endif /* SWStickerAttachable_h */

#import "SWMeshAttachable.h"
#import "SWCommon.h"
#import <SceneKit/SceneKit.h>
#import <SpriteKit/SpriteKit.h>

/*!
 * SWStickerAttachable
 * This is an instance of a tracked object in reference to a specific point on a face.
 * The tracked point is defined as indexPoint, which corresponds to the vertices in the render mesh.
 */
@interface SWStickerAttachable : SWMeshAttachable

/*!
 * indexPoint
 * The tracked point on a face.
 */
@property (nonatomic) NSInteger indexPoint;

/*!
 * isTransformingEnabled
 * allows translation in space
 */
@property (nonatomic) BOOL isTranslationEnabled;

/*!
 * currentPan
 * translates the node in 2D space given the x and y offsets
 */
@property (nonatomic) CGPoint currentPan;

/*!
 * currentRotation
 * the current rotation of the node. This is applied on top of the original rotation
 */
@property (nonatomic) SCNVector3 currentRotation;

/*!
 * currentPanAdjustmentIn3D
 * translates the node in 3D space given the x, y, z offsets
 */
@property (nonatomic) CGPoint currentPanAdjustmentIn3D;

/*!
 * trackedVertex
 * which vertex that the sticker gets pinned to.
 */
@property (nonatomic) int trackedVertex;

/*!
 * useEyeGaze
 * if enabled, the node will rotate along with the eye direction.
 */
@property (nonatomic) BOOL useEyeGaze;

/*!
 * @brief initWithSCNNode - creates an instance of an attachable with a root node
 * @param node
 * @return
 */
- (instancetype) initWithSCNNode:(SCNNode *)node;

- (void)loadAnimationAtFilePath:(NSString *)path;

@end
