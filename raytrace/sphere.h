#ifndef SPHERE_H
#define SPHERE_H

#include "OpenGP/Image/Image.h"

using namespace OpenGP;

class sphere
{
public:
    // Constructors and Destructor
    sphere();
    sphere(Vec3 sphereCenter, float sphereRadius);
    ~sphere();

    // A function to check if the ray intersects with the sphere
    // make inline by declaring/initializing in header file
    float intersectRay(Vec3 const& direction, Vec3 const& origin);

private:
    Vec3 mCenter_;
    float mRadius_;
};

#endif // SPHERE_H
