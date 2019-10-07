#include "imageplane.h"

ImagePlane::ImagePlane(){}

ImagePlane::ImagePlane(float cols, float rows, Vec3 lowerLeft, Vec3 upperRight)
{
    xCols_ = cols;
    yRows_ = rows;
    zConst_ = lowerLeft(2);
    lowerLeft_ = lowerLeft;
    upperRight_ = upperRight;
}

ImagePlane::~ImagePlane(){}

Vec3 ImagePlane::generatePixelPos(float row, float col)
{
    /*
    Vec3 origin = Vec3(0.0f, 0.0f, 2.0f);
    Vec3 lookat = Vec3(0.0f, 0.0f, -1.0f);
    Vec3 vup = Vec3(0.0f, 1.0f, 0.0f);
    float aspectRatio = xCols_ / yRows_;
    //float fov = 90.0f;

    Vec3 x, y, z;
    float halfHeight = 0.5f;
    float halfWidth = halfHeight * aspectRatio;
    z = (origin - lookat).normalized();
    x = (vup.cross(z)).normalized();
    y = z.cross(x);

    Vec3 ll = Vec3(-halfWidth, -halfHeight, -1.0f);
    ll = origin - (halfWidth * x) - (halfHeight * y) - z;
    Vec3 horizontal = 2.0f * halfWidth * x;
    Vec3 vertical = 2.0f * halfHeight * y;

    Vec3 temp = ll + (row + randU) * horizontal + (col + randV) * vertical - origin;
    return temp - origin;
    */

    // Choose field of view
    float fov = 90.0f;

    // Create random values within sub-pixel
    float randU = static_cast<float>(rand() % 100) / 100;
    float randV = static_cast<float>(rand() % 100) / 100;

    // Calculate u & v in the coordinate space
    float u = ((2.0f * (col + randU) / xCols_) - upperRight_(0)) * (xCols_ / yRows_) * tan(fov / 2.0f);
    float v = ((2.0f * (row + randV) / yRows_) - upperRight_(1)) * tan(fov / 2.0f);
    return Vec3(u, v, zConst_);
}
