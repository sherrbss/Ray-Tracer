#ifndef SPHERE_H
#define SPHERE_H

#include "OpenGP/Image/Image.h"

using namespace OpenGP;

// Encapsulates information and functions pertaining to spheres
// that are projected onto a given scene. Information includes
// the center of the sphere, as a Vec3 object, as well as the
// raduis of the sphere, as a float. Functions include
// intersectRay, which finds whether an intersection exists.
//
class sphere
{
public:
    // Constructors and Destructor
    sphere();
    sphere(Vec3 sphereCenter, float sphereRadius);
    ~sphere();

    // Returns a float that signifies whether a solution exists
    // between a ray and a sphere, taking two parameters,
    // direction and origin, both Vec3 objects. The function
    // returns -1 where no solutions are found or if the solution
    // found is on the dark side of the sphere. If a solution
    // is found on the bright side of the circle, the greater of the
    //two solutions is returned.
    float intersectRay(Vec3 const& direction, Vec3 const& origin);


private:
    Vec3 mCenter_;
    float mRadius_;
};

#endif
