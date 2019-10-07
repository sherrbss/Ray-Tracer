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

    // Updates the current colour for use in Anti-Aliasing
    Vec3 updateColour(Vec3 toAdd);

private:
    Vec3 currentColor, ambientColour, diffuseColour;
};

#endif // SCENECOLOUR_H
