//
//  SWFace.h
//  SwitchSceneKit
//
//  Created by Tony Cheng on 11/3/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "SWFeature.h"
#import "SWEyeFeature.h"
#import "SWCommon.h"
#import "SWExpression.h"

/*!
    @class SWFace
 
    @brief This class provides the high-level tracking information in the form of position, rotation, and expressions of features on a human face.
 
    @discussion Further information on the layers of data representation can be found in the appropriate header files.
 */
@interface SWFace : NSObject


/*!
    @property bounds
 
    @brief A CGRect that frames the entire face.
 */
@property (nonatomic) CGRect bounds;

/*! 
    @property position
 
    @brief The top left corner of the bounding rectangle.
 
    @discussion The xy coordinate plane goes from the top left as (0.0, 0.0) to the bottom right as (1.0, 1.0).
 */
@property (nonatomic) SWPoint3D position;

/*! 
    @property rotation
 
    @brief The rotation of the head in three dimensions.
 
    @discussion The rotation is given as Euler angles.
 */
@property (nonatomic) SWPoint3D rotation;

/*!
    @property facePoints
 
    @brief An array of all the facial tracking points.

    @discussion These points are projected onto a 2d plane
 */
@property (nonatomic) SWPoint3D *facePoints;

- (instancetype)initWithLeftEye:(SWEyeFeature*)leftEye rightEye:(SWEyeFeature*)rightEye mouth:(SWFeature*)mouth expressions:(NSMutableArray*)expressions bounds:(CGRect)bounds position:(SWPoint3D)position rotation:(SWPoint3D)rotation facePoints:(SWPoint3D*)facePoints;

/*!
    @brief Returns the tracking information of the left and right eyes.
 
    @discussion The left eye is the first element and the right eye is the second element.
 
    @return NSArray<SWFeature*>* An array of tracking information for the eye features.
 */
- (NSArray <SWFeature *> *)getEyes;

/*!
    @brief Returns the tracking information of the mouth.
 
    @return SWFeature* Tracking information for the mouth feature.
 */
- (SWFeature *)getMouth;


/*!
    @brief Returns the detected weights of a variety of facial expressions.
 
    @discussion Each weight has the range of 0.0 to 1.0 measuring how present the facial expression is in the detected face. 0.0 means the facial expression is not detected at all, while 1.0 means the facial expression is extremely present. There can be a simultaneous variety of values, one for each expression. This represents the presence of a simultaneous combination of expressions.
 
    @return NSArray<SWExpression*>* An array of tracking information for a variety of facial expressions.
 */
- (NSArray <SWExpression *> *)expressions;

@end
