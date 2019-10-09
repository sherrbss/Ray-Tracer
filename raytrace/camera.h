#ifndef CAMERA_H
#define CAMERA_H
#include "OpenGP/Image/Image.h"
#include "ray.h"

using namespace OpenGP;


// Encapsulates camera position and performs functions related
// to the camera such as generation of rays, Vec3 objects.
class camera
{
public:

    // Constructors & Destructor
    camera();
    camera(Vec3 origin, Vec3 direction, float rows, float cols);
    ~camera();

    // Returns a Vec3 object that is a Vector from the origin
    // to the pixel position that was passed in. The pixel
    // position is passed in as an argument of type Vec3.
    Ray generateRay(float x, float y);

    //
    float getU();

    //
    float getV();

private:
    Vec3 origin_;
    float rows_, cols_, u, v;
    Vec3 upperRight_, lowerLeft_, horizontalDistance, verticalDistance;
};

#endif // CAMERA_H
