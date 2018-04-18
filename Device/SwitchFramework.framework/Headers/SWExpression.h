//
// Created by Tony Cheng on 11/3/16.
// Copyright (c) 2016 Tony Cheng. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SWCommon.h"

/*!
    @class SWExpression
 
    @brief This class provides a representation for a variety of detected facial expressions.
 */
@interface SWExpression : NSObject

@property (nonatomic, copy) NSString *label;
@property (nonatomic) float value;

- (instancetype) initWithAnimationLabel:(NSString *)label value:(float)value;

@end
