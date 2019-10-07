#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "OpenGP/Image/Image.h"

using namespace OpenGP;


// Encapsulates information pertaining to the image plane such
// as the dimensions of the output (rows and cols), its position
// in the -Z direction, and the lower left and upper right
// corners of the image plane.
class ImagePlane
{
public:

    // Constructors and Destructors
    ImagePlane();
    ImagePlane(float cols, float rows, Vec3 lowerLeft, Vec3 upperRight);
    ~ImagePlane();

    // Returns the pixel position in a given plane, taking the
    // current row and column of type float. The row and column
    // pertain to the current coordinates of the output file,
    // which is determined by its dimensions.
    Vec3 generatePixelPos(float row, float col);

private:
    float xCols_, yRows_, zConst_;
    Vec3 lowerLeft_, upperRight_;
};

#endif // IMAGEPLANE_H
