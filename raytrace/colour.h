#ifndef SCENECOLOUR_H
#define SCENECOLOUR_H
#include "OpenGP/Image/Image.h"
#include "ray.h"

using namespace OpenGP;

// Encapsulates information and functions pertaining to output colors
// of each area on the scene.
class Colour
{
public:

    // Constructors & Destructor
    Colour();
    Colour(float x, float y, float z);
    ~Colour();

    // Return white as an Vec3 object with RBG with values [0, 255]
    Vec3 white();

    // Return black as an Vec3 object with RBG with values [0, 255]
    Vec3 black();

    // Return grey as an Vec3 object with RBG with values [0, 255]
    Vec3 grey();

    // Returns the current colour as a Vec3 object
    Vec3 getColour();

    // Returns the ambient colour as a Vec3 object
    Vec3 getAmbient();

    // Returns the diffuse colour as a Vec3 object
    Vec3 getDiffuse();

    // Sets the ambient colour
    void setAmbient(Vec3 ambient);

    // Sets the diffuse colour
    void setDiffuse(Vec3 diffuse);

    // Sets the current colour for use in Anti-Aliasing
    void updateColour(Vec3 toAdd);

    // Returns the clamped diffuse coefficient
    float diffuseCoefficient(Ray sphereNormal, Ray lightRay);

    // Returns clamped value for shading values outside of the RGB range
    uchar boundPixelValue(int shading);

    // Returns RGB of current pixel
    Vec3 calculateRGB(Vec3 ambient, Vec3 diffuse, float diffuseTerm);

private:
    Vec3 currentColor, ambientColour, diffuseColour;
};

#endif // SCENECOLOUR_H
