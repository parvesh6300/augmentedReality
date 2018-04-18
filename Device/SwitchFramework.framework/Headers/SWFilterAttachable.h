//
//  SWFilterAttachable.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 2/7/17.
//  Copyright © 2017 Tony Cheng. All rights reserved.
//

#ifndef SWFilterAttachable_h
#define SWFilterAttachable_h


#endif /* SWFilterAttachable_h */

#import "SWAttachable.h"
#import <SceneKit/SceneKit.h>

@interface SWFilterAttachable : SWAttachable

@property (nonatomic, strong, readonly) SCNTechnique *shadingTechnique;

- (instancetype) initWithPlistFilePath:(NSString *)plistFilePath;

@end
