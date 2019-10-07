#include "OpenGP/Image/Image.h"
#include "bmpwrite.h"
#include <iostream>
#include "camera.h"
#include "sphere.h"
#include "imageplane.h"
#include "scenecolour.h"

using namespace OpenGP;

uchar BoundPixelValue(int shading)
{
    if (shading < 0) return 0;
    if (shading >= 255) return 255;
    return shading;
}

float ClampAngle(float angle)
{
    if (angle < 0.0f) {
        return 0.0f;
    }
    if (angle > 1.0f) {
        return 1.0f;
    }
    return angle;
}

int main(int, char**){

    // Define resolution of image
    int wResolution = 640;
    int hResolution = 480;

    // Define camera position & origin
    float xOrigin = 0.0f;
    float yOrigin = 0.0f;
    float zOrigin = 2.0f;

    // Define viewing angle (-Z)
    float zImage = -1.0f;

    // Define coordinates of Image Plane
    float imageBottom = -1;
    float imageTop = 1;
    float imageLeft = -1;
    float imageRight = 1;

    // Intialize sphere position and dimensions
    float sphereRadius = 1.0f;
    float xSphereOffset = 0.0f;
    float ySphereOffset = 0.0f;
    float zSphereDistance = -3.0f;

    // Define Anti-Aliasing factor
    int aaFactor = 1;

    // Define camera origin
    Vec3 origin = Vec3(xOrigin, yOrigin, zOrigin);
    camera cam = camera(origin);

    // Initialize lower left and upper right corner vectors
    Vec3 lowerLeft = Vec3(imageLeft, imageBottom, zImage);
    Vec3 upperRight = Vec3(imageRight, imageTop, zImage);

    // Build the image plane
    ImagePlane image = ImagePlane(wResolution, hResolution, lowerLeft, upperRight);

    // Add sphere onto the scene and define ambient/diffuse values
    Vec3 sphereCenter = Vec3(xSphereOffset, ySphereOffset, zSphereDistance);
    sphere sphereImage = sphere(sphereCenter, sphereRadius);
    SceneColour sphereColour = SceneColour();
    sphereColour.setAmbient(Vec3(7.0f, 70.0f, 70.0f));
    sphereColour.setDiffuse(Vec3(15.0f, 130.0f, 130.0f));

    // Add sphere onto the scene and define ambient/diffuse values
    SceneColour planeColour = SceneColour();
    planeColour.setAmbient(Vec3(0.0f, 0.0f, 0.0f));
    planeColour.setDiffuse(Vec3(69.0f, 69.0f, 69.0f));
    planeColour.updateColour(Vec3(69.0f, 69.0f, 69.0f));

    // Add generic scene colours
    SceneColour sceneColour = SceneColour();
    sceneColour.setAmbient(Vec3(0.0f, 0.0f, 0.0f));
    sceneColour.setDiffuse(Vec3(255.0f, 255.0f, 255.0f));
    sceneColour.updateColour(Vec3(255.0f, 255.0f, 255.0f));

    // Define lighting source
    Vec3 lightingSource = Vec3(-5.0f, 10.0f, -1.0f);

    // Define Image to write to bmp file
    Image<Vec3> imageWriter(hResolution, wResolution);

    // Ray Tracing
    for (int row = 0; row < hResolution; ++row) {
        for (int col = 0; col < wResolution; ++col) {

            // Define base colour
            SceneColour pixelColour = SceneColour(0.0f, 0.0f, 0.0f);

            // Anti-Aliasing via random rays
            for (int alias = 0; alias < aaFactor; alias++) {

                // Find current pixel position and generate ray
                Vec3 currPixel = image.generatePixelPos(row, col);
                Vec3 ray = cam.generateRay(currPixel).normalized();

                // Calculate ray-sphere intersection
                float t = sphereImage.intersectRay(ray, origin);
                if (t > 0.0f) {

                    // Calculate diffuse coefficient and clamp
                    Vec3 spherePoint = origin + t * ray;
                    float cosAngle = ClampAngle(sceneColour.diffuseCoefficient(spherePoint, sphereCenter, lightingSource));

                    // Calculate diffuse and ambient values
                    float diffuseTerm = cosAngle;

                    // Write colour to image with diffuse factors
                    Vec3 currentColour = sceneColour.calculateRGB(
                                sphereColour.getAmbient(),
                                sphereColour.getDiffuse(),
                                diffuseTerm);

                    pixelColour.updateColour(currentColour);

                } else {

                    // Calculate ray-plane intersection (floor)
                    float t = -(origin(1) + sphereRadius) / ray(1);
                    Vec3 planePoint = origin + t * ray;

                    // Calculate colour
                    if (t > 0.0f && planePoint(0) < 9.0f && planePoint(0) > -9.0f
                            && planePoint(2) < -1.0f && planePoint(2) > -19.0f) {

                        // Generate ray and test for intersection with sphere
                        Vec3 lightVector = (lightingSource - planePoint).normalized();
                        float dShadow = sphereImage.intersectRay(lightVector, planePoint);

                        // Print floor or shadow, depending on intersection
                        if (dShadow > 0.0f) {
                            Vec3 normal = Vec3(0.0f, 1.0f, 0.0f);
                            float cosAngle = ClampAngle(sceneColour.diffuseCoefficient(planePoint, normal, lightingSource));

                            // Calculate diffuse and ambient values
                            float diffuseTerm = -cosAngle;

                            Vec3 currentColour = sceneColour.calculateRGB(
                                        planeColour.getAmbient(),
                                        planeColour.getDiffuse(),
                                        diffuseTerm);

                            pixelColour.updateColour(currentColour);

                        } else {
                            pixelColour.updateColour(Vec3(planeColour.getColour()));
                        }

                    } else {
                        pixelColour.updateColour(Vec3(sceneColour.getColour()));
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

/*
 * 1. Adjust camera/coordinate system (+10%)---
 *      - allows for the camera to be moved
 * 2. Add plane class
 *      - intersection function
 * 3. Create colour class with calculations for
 *      - diffuse function
 *      - shadow funciton
 * 4. Add and touch up comments/cleanup code (+10%)---
 *      - functions/inline comments (+5%)
 *      - clean code (+5%)
 * 5.1 Add reflective material (+5%)
 * Line lengths
 *
*/

