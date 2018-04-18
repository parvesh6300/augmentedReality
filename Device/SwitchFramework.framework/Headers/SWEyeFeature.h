//
//  SWEyeFeature.h
//  SwitchSceneKit
//
//  Created by Tony Cheng on 11/3/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#import "SWFeature.h"
#import "SWCommon.h"

/*!
    @class SWEyeFeature
 
    @brief This class provides a representation of an eye feature on the face.
 */
@interface SWEyeFeature : SWFeature

/*!
    @property rotation
 
    @brief The rotation of the eye in three dimensions.
 
    @discussion The rotation is given as Euler angles.
 
    @warning The rotation is not currently available.
 */
@property (nonatomic) SWPoint3D rotation;

- (instancetype) initWithBounds:(CGRect)bounds position:(SWPoint3D)position Rotation:(SWPoint3D)rotation;

@end
