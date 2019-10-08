#include "sphere.h"

sphere::sphere(){}

sphere::sphere(Vec3 sphereCenter, float sphereRadius)
{
    mCenter_ = sphereCenter;
    mRadius_ = sphereRadius;
}

sphere::~sphere(){}

//float sphere::intersectRay(Vec3 const& direction, Vec3 const& origin)
float sphere::intersectRay(Ray currRay)
{
    Vec3 originToSphereCenter = currRay.getOrigin() - mCenter_;

    float A = currRay.getDirection().dot(currRay.getDirection());
    float B = 2.0f * currRay.getDirection().dot(originToSphereCenter);
    float C = originToSphereCenter.dot(originToSphereCenter) -
            (mRadius_ * mRadius_);

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
    }

    // Return the greater of solution A and B
    return (solA > solB) ? solB : solA;
}
