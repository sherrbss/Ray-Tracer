#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "OpenGP/Image/Image.h"

using namespace OpenGP;

class ImagePlane
{
public:

    // Constructors and Destructors
    ImagePlane();
    ImagePlane(float cols, float rows, Vec3 lowerLeft, Vec3 upperRight);
    ~ImagePlane();

    // Function to generate pixel positions in image plane
    //Vec3 generatePixelPos(int row, int col);
    Vec3 generatePixelPos(float row, float col);

private:
    float xCols_, yRows_, zConst_;
    Vec3 lowerLeft_, upperRight_;
};



#endif // IMAGEPLANE_H
