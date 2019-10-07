#ifndef CAMERA_H
#define CAMERA_H
#include "OpenGP/Image/Image.h"

using namespace OpenGP;


// Encapsulates camera position and performs functions related
// to the camera such as generation of rays, Vec3 objects.
class camera
{
public:

    // Constructors & Destructor
    camera();
    camera(Vec3 origin);
    ~camera();

    // Returns a Vec3 object that is a Vector from the origin
    // to the pixel position that was passed in. The pixel
    // position is passed in as an argument of type Vec3.
    Vec3 generateRay(Vec3 const& pixelPosition);

private:
    Vec3 mPosition_;
};

#endif // CAMERA_H
