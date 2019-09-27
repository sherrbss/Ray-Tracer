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
