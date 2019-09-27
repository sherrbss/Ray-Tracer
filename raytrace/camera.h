#ifndef CAMERA_H
#define CAMERA_H

#include "OpenGP/Image/Image.h"

using namespace OpenGP;

class camera
{
public:

    // Constructors & Destructor
    camera();
    camera(Vec3 origin);
    ~camera();

    // Function to generate ray
    // make inline by declaring/initializing in header file
    Vec3 generateRay(Vec3 const& pixelPosition);

private:
    Vec3 mPosition_;
};

#endif // CAMERA_H
