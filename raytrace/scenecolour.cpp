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
    return Vec3(7, 70, 70);
}

Vec3 SceneColour::getDiffuse()
{
    return Vec3(15, 130, 130);
}

void SceneColour::setAmbient(Vec3 ambient)
{
    ambientColour = ambient;
}

void SceneColour::setDiffuse(Vec3 diffuse)
{
    diffuseColour = diffuse;
}

Vec3 SceneColour::updateColour(Vec3 toAdd)
{
    currentColor += toAdd;
    return currentColor;
}
