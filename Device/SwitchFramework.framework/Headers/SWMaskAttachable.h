//
//  SWMaskAttachable.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 2/7/17.
//  Copyright © 2017 Tony Cheng. All rights reserved.
//

#ifndef SWMaskAttachable_h
#define SWMaskAttachable_h


#endif /* SWMaskAttachable_h */

#import "SWMeshAttachable.h"
#import "SWCommon.h"
#import <SceneKit/SceneKit.h>
#import <SpriteKit/SpriteKit.h>

@interface SWMaskAttachable : SWMeshAttachable

/*! initWithPNGFilePath:
 *
 * This is the default load method for mask attachables. It will take in the image and apply it as a texture to a fitted mask geometry
 *
 * @param imageFilePath
 * @param scale
 * @return
 */
- (instancetype)initWithImageFilePath:(NSString *)imageFilePath withScale:(CGFloat)scale;

@end
