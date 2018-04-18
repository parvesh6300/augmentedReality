//
//  SWCoordinateSystem.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 11/29/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#ifndef SWCoordinateSystem_h
#define SWCoordinateSystem_h


#endif /* SWCoordinateSystem_h */

#import "SWCommon.h"


/*!
    @class SWCoordinateSystem
 
    @brief This class provides the low-level facial tracking information in the form of transformation matrices for the estimated camera position.
 
    @discussion The transformation matrices register a model to the same coordinate system as the detected facial model.
 */
@interface SWCoordinateSystem : NSObject

/*!
    @property projectionTransformation
 
    @brief Transformation matrix for perspective projection.
 */
@property (nonatomic) SWMatrix4x4 *projectionTransformation;

/*!
    @property cameraTransformation
 
    @brief Transformation matrix for the movement of the camera.
 
    @warning Is not currently available - use the projectionTransformation and modelViewTransformation matrices by themselves instead.
 */
@property (nonatomic) SWMatrix4x4 *cameraTransformation;

/*!
    @property modelViewTransformation
 
    @brief Transformation matrix for the movement of the model.
 */
@property (nonatomic) SWMatrix4x4 *modelViewTransformation;

- (instancetype) initWithProjectionTransformation:(SWMatrix4x4*)projectionTransformation cameraTransformation:(SWMatrix4x4*)cameraTransformation modelViewTransformation:(SWMatrix4x4*)modelViewTransformation;

@end
