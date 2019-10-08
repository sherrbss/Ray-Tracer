#include "ray.h"

Ray::Ray(){}

Ray::Ray(Vec3 origin, Vec3 direction)
{
    origin_ = origin;
    direction_ = direction;
}

Ray::~Ray(){}


Vec3 Ray::getPoint(float solution) {
    return origin_ + (solution * direction_);
}

Vec3 Ray::getOrigin() {
    return origin_;
}

Vec3 Ray::getDirection() {
    return direction_;
}
