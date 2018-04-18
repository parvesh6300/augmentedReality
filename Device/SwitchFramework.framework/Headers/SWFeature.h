//
//  SWFeature.h
//  SwitchSceneKit
//
//  Created by Tony Cheng on 11/3/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SWCommon.h"

/*!
    @class SWFeature
    
    @brief This class provides a representation of a facial feature.
 */
@interface SWFeature : NSObject

/*!
    @property bounds
 
    @brief A CGRect that frames the feature.
 */
@property (nonatomic) CGRect bounds;

/*!
    @property position
 
    @brief The top left corner of the bounding rectangle.
 
    @discussion The xy coordinate plane goes from the top left as (0.0, 0.0) to the bottom right as (1.0, 1.0).
 */
@property (nonatomic) SWPoint3D position;

- (instancetype) initWithBounds:(CGRect)bounds position:(SWPoint3D)position;

@end
