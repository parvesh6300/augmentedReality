//
//  SWEnvironmentAttachable.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 2/7/17.
//  Copyright © 2017 Tony Cheng. All rights reserved.
//

#ifndef SWEnvironmentAttachable_h
#define SWEnvironmentAttachable_h


#endif /* SWEnvironmentAttachable_h */

#import "SWMeshAttachable.h"
#import "SWCommon.h"
#import <SceneKit/SceneKit.h>
#import <SpriteKit/SpriteKit.h>

@interface SWEnvironmentAttachable : SWMeshAttachable

/*!
 * pointOfView
 * if this is set, it will use the SCNNode camera property as the new camera instead of the default
 */
@property (nonatomic, strong, readonly) SCNNode *pointOfView;

/*!
 *
 */
@property (nonatomic, strong, readonly) UIImage *lightingEnvironment;

/*!
 * background
 * this is used to fill the background of the entire scene, if necessary
 */
@property (nonatomic, strong, readonly) UIImage *background;

/*!
 * useAsBackground
 * determines whether the background image is used to fill
 */
@property (nonatomic) BOOL useAsBackground;

- (void)loadSceneAtPath:(NSString *)path;
- (void)loadTextureAtlasAtPath:(NSString *)path;

- (instancetype) initWithSCNNode:(SCNNode *)node withScale:(CGFloat)scale;

@end
