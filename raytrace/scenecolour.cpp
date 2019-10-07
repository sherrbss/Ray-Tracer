#include "scenecolour.h"

SceneColour::SceneColour()
{
    Color(0.0f, 0.0f, 0.0f);
}

SceneColour::SceneColour(float x, float y, float z)
{
    currentColor = Vec3(x, y, z);
}

SceneColour::~SceneColour(){}

Vec3 SceneColour::white()
{
    return Vec3(256.0f, 256.0f, 256.0f);
}

Vec3 SceneColour::black()
{
    return Vec3(0.0f, 0.0f, 0.0f);
}

Vec3 SceneColour::grey()
{
    return Vec3(69.0f, 69.0f, 69.0f);
}

Vec3 SceneColour::getColour()
{
    return currentColor;
}

Vec3 SceneColour::getAmbient()
{
    return ambientColour;
}

Vec3 SceneColour::getDiffuse()
{
    return diffuseColour;
}

void SceneColour::setAmbient(Vec3 ambient)
{
    ambientColour = ambient;
}

void SceneColour::setDiffuse(Vec3 diffuse)
{
    diffuseColour = diffuse;
}

void SceneColour::updateColour(Vec3 toAdd)
{
    currentColor += toAdd;
}

float SceneColour::diffuseCoefficient(Vec3 intPoint, Vec3 normalEndpoint, Vec3 lightingSource)
{
    float cosAngle;

    Vec3 normal = (intPoint - normalEndpoint).normalized();
    Vec3 lightVector = (lightingSource - intPoint).normalized();
    cosAngle = (normal.dot(lightVector));

    return cosAngle;
}

uchar SceneColour::boundPixelValue(int shading)
{
    if (shading < 0) return 0;
    if (shading >= 255) return 255;
    return shading;
}

Vec3 SceneColour::calculateRGB(Vec3 ambient, Vec3 diffuse, float diffuseTerm)
{
    float r = static_cast<float>(ambient[0] + diffuse[0] * diffuseTerm);
    int tempR = boundPixelValue(static_cast<int>(r));
    float g = static_cast<float>(ambient[1] + diffuse[1] * diffuseTerm);
    int tempG = boundPixelValue(static_cast<int>(g));
    float b = static_cast<float>(ambient[2] + diffuse[2] * diffuseTerm);
    int tempB = boundPixelValue(static_cast<int>(b));

    return Vec3(tempR, tempB, tempG);
}


