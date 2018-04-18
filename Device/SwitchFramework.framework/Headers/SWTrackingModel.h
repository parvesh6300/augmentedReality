//
//  SWTrackingModel.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 11/29/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#ifndef SWTrackingModel_h
#define SWTrackingModel_h


#endif /* SWTrackingModel_h */

#import <Foundation/Foundation.h>
#import "SWFace.h"
#import "SWCoordinateSystem.h"
#import "SWMeshData.h"

/*!
    @class SWTrackingModel
 
    @brief This class represents the face tracking data returned from SWTrackingEngine.
 
    @discussion Further information on the layers of data representation can be found in the appropriate header files.
 */
@interface SWTrackingModel : NSObject

/*!
    @property faceModel
 
    @brief High-level tracking information organized around location, rotation, and facial expression of the human face.
 */
@property (nonatomic, strong) SWFace *faceModel;

/*!
    @property modelCoordinateSystem
 
    @brief Low-level tracking information organized around matrix-representations of the camera pose estimation.
 */
@property (nonatomic, strong) SWCoordinateSystem *modelCoordinateSystem;

/*!
    @property meshModel
 
    @brief Low-level tracking information organized around tracking model rendering data.
 */
@property (nonatomic, strong) SWMeshData *meshModel;

- (instancetype) initWithFace:(SWFace *)face coordinateSystem:(SWCoordinateSystem*)coordinateSystem meshData:(SWMeshData*)meshData;
- (instancetype) initWithFace:(SWFace *)face;

@end
