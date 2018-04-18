//
//  SWMeshData.h
//  SwitchFramework
//
//  Created by Kyle Gonzalez on 11/29/16.
//  Copyright © 2016 Tony Cheng. All rights reserved.
//

#ifndef SWMeshData_h
#define SWMeshData_h


#endif /* SWMeshData_h */

#import "SWCommon.h"

/*!
    @class SWMeshData
    
    @brief This class provides the low-level facial tracking information in the form of tracking model vertex and index data.
 
    @discussion Further information on the layers of data representation can be found in the appropriate header files.
 */
@interface SWMeshData : NSObject

/*!
    @property vertexData
 
    @brief Vertex position, normal, and texture coordinates data of the fitted facial tracking model.
 */
@property (nonatomic) SWVertex *vertexData;

/*!
    @property numberOfVertices
 
    @brief The number of elements represented in vertexData.
 */
@property (nonatomic) int numberOfVertices; // Number of tuples <x, y, z>


/*!
    @property indexData
 
    @brief Index position data for rendering the mesh faces of the fitted facial tracking model.
 */
@property (nonatomic) SWFaceIndices *indexData;

/*!
    @property numberOfIndices
 
    @brief The number of elements represented in indexData.
 */
@property (nonatomic) int numberOfIndices; // Number of tuples <v1, v2, v3>

/*!
    @property indexListType
 
    @brief A string of either @"KT_TRIANGLES" or @"KT_LINES" to represent whether the facial tracking model mesh is represented through triangular faces or lines.
 */
@property (nonatomic) NSString *indexListType;

- (instancetype) initWithVertices:(SWVertex*)vertexData numberOfVertices:(int)nVertices indices:(SWFaceIndices*)indexData numberOfIndices:(int)nIndices;

@end
