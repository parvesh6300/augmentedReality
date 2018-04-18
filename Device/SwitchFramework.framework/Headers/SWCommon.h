#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

#define DEGREES_FROM_RADIANS(radians)(radians * 180.0 / M_PI)
#define RADIANS_FROM_DEGREES(degrees)(degrees * M_PI / 180.0f)

#define STICKER_AND_ENVIRONMENT_RENDERING_ORDER 1
#define MASK_RENDERING_ORDER 0
#define INITIAL_MESH_LIGHTING_MODEL SCNLightingModelConstant

#define INITIAL_STICKER_SCALE 1.0f

#define INITIAL_MASK_SCALE 2.85f

#define INITIAL_ENVIRONMENT_SCALE 1.0f


/*!
    @typedef SWPoint3D

    @brief This represents a 3-dimensional vector.

    @field x The x-component; the first component of the vector.

    @field y The y-component; the second component of the vector.

    @field z The z-component; the third component of the vector.
 */
typedef struct SWPoint3D {
    CGFloat x, y, z;
} SWPoint3D;

static inline SWPoint3D SWPoint3DMake(CGFloat x, CGFloat y, CGFloat z)
{
    SWPoint3D p; p.x = x; p.y = y; p.z = z; return p;
}


/*!
    @typedef SWVoordinateUV

    @brief This represents the texture coordinates of a single vertex.

    @field u The u-component of the texture coordinates.

    @field v The v-component of the texture coordinates.
 */
typedef struct SWCoordinateUV
{
    float u, v;
} SWCoordinateUV;


/*!
    @typedef SWMatrix4x4

    @brief This represents a matrix, often seen as a transformation matrix.

    @field matrix A 4-by-4 matrix. It takes the representation [rows][columns].
 */
typedef struct SWMatrix4x4{
    /*! A 4-by-4 matrix. It takes the representation [rows][columns]. */
    float matrix[4][4];
} SWMatrix4x4;


/*!
    @typedef SWVertex

    @brief This represents the vertex data of each vertex in a mesh.

    @field x The x-component of the vertex location.

    @field y The y-component of the vertex location.

    @field z The z-component of the vertex location.

    @field nx The x-component of the vertex normal.

    @field ny The y-component of the vertex normal.

    @field nz The z-component of the vertex normal.

    @field u The u-component of the vertex texture coordinates.

    @field v The v-component of the vertex texture coordinates.
 */
typedef struct SWVertex
{
    float x, y, z;
    float nx, ny, nz;
    float u, v;
} SWVertex;

/*!
    @typedef SWFaceIndices

    @brief This represents the index data used for constructing a mesh face.

    @field v1 The first vertex index.

    @field v2 The second vertex index.

    @field v3 The third vertex index.
 */
typedef struct SWFaceIndices
{
    int v1, v2, v3;
} SWFaceIndices;


