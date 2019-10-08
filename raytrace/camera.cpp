#include "camera.h"

camera::camera(){}

camera::camera(Vec3 origin, Vec3 direction, float rows, float cols)
{
    // Assign generic up vector for the system
    Vec3 upVector = Vec3(0.0f, 1.0f, 0.0f);

    // Dimensions in proportionally scaled [0, 1] system
    rows_ = rows;
    cols_ = cols;
    float height = 1.0f;
    float width = height * (cols_ / rows_);

    // Generate coordinate system of the camera plane
    Vec3 z = (origin - direction).normalized();
    Vec3 x = (upVector.cross(z)).normalized();
    Vec3 y = z.cross(x);
    //Vec3 x = (origin - direction).normalized();
    //Vec3 y = (upVector.cross(x)).normalized();
    //Vec3 z = x.cross(y);

    // Generate x and y coordinates
    Vec3 tempX = width * x;
    Vec3 tempY = height * y;
    upperRight_ = origin + z + tempX + tempY;
    lowerLeft_ = origin - x*width - y*height - z;

    // Adjust coordinates for larger [-1, 1] coordinate system
    horizontalDistance = 2.0f * tempX;
    verticalDistance = 2.0f * tempY;
}

camera::~camera(){}

Ray camera::generateRay(float row, float col)
{
    // Generate random values for anti-aliasing
    float randX = static_cast<float>(rand() % 100) / 100;
    float randY = static_cast<float>(rand() % 100) / 100;

    // Calculate percentages of x and y coordinates
    float x = (col + randX) / cols_;
    float y = (row + randY) / rows_;

    // Calculate a new ray for the camera space and return
    Vec3 currDirection = (x * horizontalDistance) + (y * verticalDistance) - upperRight_ - origin_;
    Ray currRay = Ray(origin_, currDirection);

    return currRay;
}



