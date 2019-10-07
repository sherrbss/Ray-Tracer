#ifndef SCENECOLOUR_H
#define SCENECOLOUR_H
#include "OpenGP/Image/Image.h"

using namespace OpenGP;

// Encapsulates information and functions pertaining to output colors
// of each area on the scene.
class SceneColour
{
public:

    // Constructors & Destructor
    SceneColour();
    SceneColour(float x, float y, float z);
    ~SceneColour();

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

    // Returns the diffuse coefficient
    float diffuseCoefficient(Vec3 intPoint, Vec3 normalEndpoint, Vec3 lightingSource);

    // Returns uchar if shading values are outside of the range
    uchar boundPixelValue(int shading);

    // Returns RGB of current pixel
    Vec3 calculateRGB(Vec3 ambient, Vec3 diffuse, float diffuseTerm);

private:
    Vec3 currentColor, ambientColour, diffuseColour;
};

#endif // SCENECOLOUR_H
