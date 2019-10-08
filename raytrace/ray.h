#ifndef RAY_H
#define RAY_H

#include "OpenGP/Image/Image.h"

using namespace OpenGP;

class Ray
{
public:
    // Constructors and Destructor
    Ray();
    Ray(Vec3 origin, Vec3 direction);
    ~Ray();

    // Returns point on the vector
    Vec3 getPoint(float solution);

    // Returns the origin
    Vec3 getOrigin();

    // Returns the direction
    Vec3 getDirection();

private:
    Vec3 origin_, direction_;
};

#endif // RAY_H
