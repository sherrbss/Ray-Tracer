#include "colour.h"

Colour::Colour()
{
    Color(0.0f, 0.0f, 0.0f);
}

Colour::Colour(float x, float y, float z)
{
    currentColor = Vec3(x, y, z);
}

Colour::~Colour(){}

Vec3 Colour::white()
{
    return Vec3(256.0f, 256.0f, 256.0f);
}

Vec3 Colour::black()
{
    return Vec3(0.0f, 0.0f, 0.0f);
}

Vec3 Colour::grey()
{
    return Vec3(69.0f, 69.0f, 69.0f);
}

Vec3 Colour::getColour()
{
    return currentColor;
}

Vec3 Colour::getAmbient()
{
    return ambientColour;
}

Vec3 Colour::getDiffuse()
{
    return diffuseColour;
}

void Colour::setAmbient(Vec3 ambient)
{
    ambientColour = ambient;
}

void Colour::setDiffuse(Vec3 diffuse)
{
    diffuseColour = diffuse;
}

void Colour::updateColour(Vec3 toAdd)
{
    currentColor += toAdd;
}

float Colour::diffuseCoefficient(Ray sphereNormal, Ray lightRay)
{
    float cosAngle;

    Vec3 normal = (sphereNormal.getDirection() - sphereNormal.getOrigin()).normalized();
    Vec3 lightVector = (lightRay.getOrigin() - sphereNormal.getDirection()).normalized();
    cosAngle = (normal.dot(lightVector));

    if (cosAngle < 0.0f) {
        cosAngle = 0.0f;
    }
    if (cosAngle > 1.0f) {
        cosAngle = 1.0f;
    }

    return cosAngle;
}

uchar Colour::boundPixelValue(int shading)
{
    if (shading < 0) return 0;
    if (shading >= 255) return 255;
    return shading;
}

Vec3 Colour::calculateRGB(Vec3 ambient, Vec3 diffuse, float diffuseTerm)
{
    float r = static_cast<float>(ambient[0] + diffuse[0] * diffuseTerm);
    int tempR = boundPixelValue(static_cast<int>(r));
    float g = static_cast<float>(ambient[1] + diffuse[1] * diffuseTerm);
    int tempG = boundPixelValue(static_cast<int>(g));
    float b = static_cast<float>(ambient[2] + diffuse[2] * diffuseTerm);
    int tempB = boundPixelValue(static_cast<int>(b));

    return Vec3(tempR, tempB, tempG);
}


