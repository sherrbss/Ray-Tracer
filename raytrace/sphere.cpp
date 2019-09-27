#include "sphere.h"
#include "camera.h"

sphere::sphere(){}

sphere::sphere(Vec3 sphereCenter, float sphereRadius)
{
    mCenter_ = sphereCenter;
    mRadius_ = sphereRadius;
}

sphere::~sphere(){}

float sphere::intersectRay(Vec3 const& direction, Vec3 const& origin)
{
    Vec3 ocVector = origin - mCenter_;

    float A = direction.dot(direction);
    float B = 2.0f * ocVector.dot(direction);
    float C = ocVector.dot(ocVector) - mRadius_*mRadius_;
    float discriminant = (B*B) - (4*A*C);

    float solA;
    float solB;

    // Return where no solutions exist
    if (discriminant < 0.0f) {
        return -1.0f;
    }

    // Find intersection point
    solA = (-B + sqrt(discriminant)) / (2.0f*A);
    solB = (-B - sqrt(discriminant)) / (2.0f*A);

    // Return where both solutions are on the dark side of the circle
    if (solA < 0.0f && solB < 0.0f) {
        return -1.0f;
        //return -0.5f;
    }

    // Return the greater of solution A and B
    return (solA > solB) ? solB : solA;
}



