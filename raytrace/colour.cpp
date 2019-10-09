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

Vec3 Colour::calculateCheckerboard(Vec3 planePoint)
{
    // Find odd and even area's and scale to remove noise.
    // NOTE: Smaller distances from origin can use "% 2 == 0"
    int scale = 9999999;
    bool x = static_cast<int>((planePoint(0) + scale)) % 20 >= 10;
    bool y = static_cast<int>((planePoint(1) + scale)) % 20 >= 10;
    bool z = static_cast<int>((planePoint(2) + scale)) % 20 >= 10;

    Vec3 tempCol;

    if (x ^ y ^ z) {
        return white();
    } else {
        return grey();
    }
}

Vec3 Colour::calculateGreys()
{
    // Generate random value between [50, 200]
    float randX = static_cast<float>(rand() % 150) + 50;

    return (randX * 0.5f) * Vec3(1.0f, 1.0f, 1.0f);
}

Vec3 Colour::calculateRandom()
{
    // Generate random values between [50, 200]
    float randX = static_cast<float>(rand() % 150) + 50;
    float randY = static_cast<float>(rand() % 150) + 50;
    float randZ = static_cast<float>(rand() % 150) + 50;

    return Vec3(1.0f * randX, 1.0f * randY, 1.0f * randZ);
}

