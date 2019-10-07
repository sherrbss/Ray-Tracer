#include "camera.h"

camera::camera()
{
    camera(Vec3(0.0f, 0.0f, 0.0f));
}

camera::camera(Vec3 origin)
{
    mPosition_ = origin;
}

camera::~camera(){}

Vec3 camera::generateRay(Vec3 const& pixelPosition)
{
    Vec3 origin = mPosition_;
    Vec3 direction = pixelPosition - origin;
    return direction;
}
