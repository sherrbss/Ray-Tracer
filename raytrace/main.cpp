#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "camera.h"
#include "sphere.h"
#include "colour.h"
#include "ray.h"

using namespace OpenGP;

int main(int, char**){

    // Define resolution of image
    int wResolution = 1280;
    int hResolution = 720;

    // Define camera position & origin
    float xOrigin = 0.0f;
    float yOrigin = 0.0f;
    float zOrigin = 0.0f;

    // Define viewing angle (-Z)
    float zImage = -5.0f;

    // Intialize sphere position and dimensions
    float sphereRadius = 4.0f;
    float xSphereOffset = 0.0f;
    float ySphereOffset = 3.0f;
    float zSphereDistance = -14.0f;

    // Define Anti-Aliasing factor
    int aaFactor = 10;

    // Add sphere onto the scene and define ambient/diffuse values
    Vec3 sphereCenter = Vec3(xSphereOffset, ySphereOffset, zSphereDistance);
    sphere sphereImage = sphere(sphereCenter, sphereRadius);
    Colour sphereColour = Colour();
    sphereColour.setAmbient(Vec3(7.0f, 70.0f, 70.0f));
    sphereColour.setDiffuse(Vec3(15.0f, 130.0f, 130.0f));

    // Define camera origin
    Vec3 origin = Vec3(xOrigin, yOrigin, zOrigin);
    Vec3 originViewDirection = Vec3(0.0f, 0.0f, zImage);
    camera cam = camera(origin, originViewDirection, hResolution, wResolution);

    // Add sphere onto the scene and define ambient/diffuse values
    Colour planeColour = Colour();
    planeColour.setAmbient(Vec3(10.0f, 10.0f, 10.0f));
    planeColour.setDiffuse(Vec3(69.0f, 69.0f, 69.0f));
    planeColour.updateColour(Vec3(69.0f, 69.0f, 69.0f));

    // Add generic scene colours
    Colour sceneColour = Colour();
    sceneColour.setAmbient(Vec3(0.0f, 0.0f, 0.0f));
    sceneColour.setDiffuse(Vec3(255.0f, 255.0f, 255.0f));
    sceneColour.updateColour(Vec3(220.0f, 220.0f, 220.0f));

    // Define lighting source
    Vec3 lightingSource = Vec3(-5.0f, 10.0f, 2.0f);

    // Define Image to write to bmp file
    Image<Vec3> imageWriter(hResolution, wResolution);

    // Ray Tracing
    for (int row = 0; row < hResolution; ++row) {
        for (int col = 0; col < wResolution; ++col) {

            // Define base colour
            Colour pixelColour = Colour(0.0f, 0.0f, 0.0f);

            // Anti-Aliasing for additional sampling
            for (int alias = 0; alias < aaFactor; alias++) {

                // Find current pixel position and generate ray
                Ray currRay = cam.generateRay(row, col);
                Vec3 ray = currRay.getDirection();

                // Calculate ray-sphere intersection
                float t = sphereImage.intersectRay(currRay);
                if (t > 0.0f) {

                    // Define rays for diffuse calculation
                    Vec3 spherePoint = currRay.getPoint(t);
                    Ray sphereNormal = Ray(sphereCenter, spherePoint);
                    Ray lightRay = Ray(lightingSource, spherePoint);

                    // Calculate diffuse coefficient and clamp
                    float diffuseTerm = sceneColour.diffuseCoefficient(sphereNormal, lightRay);

                    // Write colour to image with diffuse factors
                    Vec3 currentColour = sceneColour.calculateRGB(
                                sphereColour.getAmbient(),
                                sphereColour.getDiffuse(),
                                diffuseTerm);

                    pixelColour.updateColour(currentColour);

                } else {

                    // Calculate ray-plane intersection (floor)
                    float t = -(origin(1) + sphereRadius) / ray(1);
                    Vec3 planePoint = currRay.getPoint(t);
                    if (t > 0.0f && planePoint(0) < 15.0f && planePoint(0) > -15.0f
                            && planePoint(2) < -8.0f && planePoint(2) > -20.0f) {

                        // Generate ray and test for intersection with sphere
                        Ray normal = Ray(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
                        Ray lightRay = Ray(planePoint, lightingSource);
                        float tShadow = sphereImage.intersectRay(lightRay);

                        // Colour the floor and check for shadows
                        if (tShadow > 0.0f) {

                            // Calculate diffuse and ambient values
                            float diffuseTerm = sceneColour.diffuseCoefficient(
                                        lightRay, normal);

                            Vec3 currentColour = sceneColour.calculateRGB(
                                        planeColour.getAmbient(),
                                        planeColour.getDiffuse(),
                                        diffuseTerm);

                            pixelColour.updateColour(currentColour);

                        } else {

                            // Add checkerboard shading
                            //Vec3 tempCol = planeColour.calculateCheckerboard(planePoint);
                            //pixelColour.updateColour(tempCol);

                            // Add grey cloth-like material
                            Vec3 tempCol = planeColour.calculateGreys();
                            pixelColour.updateColour(tempCol);

                            // Add random RGB static material
                            //Vec3 tempCol = planeColour.calculateRandom();
                            //pixelColour.updateColour(tempCol);
                        }

                    } else {

                        // Colour background and shade dependant upon solution
                        Vec3 currRayVector = currRay.getDirection().normalized();
                        float t = 0.5f * (currRayVector(1) + 1.0f);
                        Vec3 tempCol = ((1.0f - t) * sphereColour.white()) + (t * sceneColour.black());
                        pixelColour.updateColour(Vec3(tempCol));
                    }
                }
            }

            // Scale RGB values output
            Vec3 currPixel = pixelColour.getColour();
            currPixel /= (static_cast<float>(aaFactor) * 256.0f);
            imageWriter(row, col) = currPixel;
        }
    }

    // Write output to .bmp file
    bmpwrite("../../out.bmp", imageWriter);
    imshow(imageWriter);

    return EXIT_SUCCESS;
}
