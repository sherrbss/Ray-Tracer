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
    int aaFactor = 5;

    // Define camera origin
    Vec3 origin = Vec3(xOrigin, yOrigin, zOrigin);
    camera cam = camera(origin);

    // Initialize lower left and upper right corner vectors
    Vec3 lowerLeft = Vec3(imageLeft, imageBottom, zImage);
    Vec3 upperRight = Vec3(imageRight, imageTop, zImage);

    // Build the image plane
    ImagePlane image = ImagePlane(wResolution, hResolution, lowerLeft, upperRight);

    // Add items onto the scene
    Vec3 sphereCenter = Vec3(xSphereOffset, ySphereOffset, zSphereDistance);
    sphere sphereImage = sphere(sphereCenter, sphereRadius);

    // Define lighting source ambient and diffuse colors
    Vec3 lightingSource = Vec3(-5.0f, 10.0f, 0.0f);
    SceneColour sceneColour = SceneColour();
    sceneColour.setAmbient(Vec3(7.0f, 70.0f, 70.0f));
    sceneColour.setDiffuse(Vec3(15.0f, 130.0f, 130.0f));

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
                    Vec3 normal = (spherePoint - sphereCenter).normalized();
                    Vec3 lightVector = (lightingSource - spherePoint).normalized();
                    float cosAngle = (normal.dot(lightVector));

                    // Clamp angle
                    if (cosAngle < 0.0f) {
                        cosAngle = 0.0f;
                    }
                    if (cosAngle > 1.0f) {
                        cosAngle = 1.0f;
                    }

                    // Calculate diffuse and ambient values
                    float diffuseTerm = cosAngle;

                    // Adjust colours and scale to [0.0, 1.0]
                    float r = static_cast<float>(sceneColour.getAmbient()[0] + sceneColour.getDiffuse()[0] * diffuseTerm);
                    int tempR = BoundPixelValue(static_cast<int>(r));
                    float g = static_cast<float>(sceneColour.getAmbient()[1] + sceneColour.getDiffuse()[1] * diffuseTerm);
                    int tempG = BoundPixelValue(static_cast<int>(g));
                    float b = static_cast<float>(sceneColour.getAmbient()[2] + sceneColour.getDiffuse()[2] * diffuseTerm);
                    int tempB = BoundPixelValue(static_cast<int>(b));

                    // Write colour to image with diffuse factors
                    pixelColour.updateColour(Vec3(tempR, tempG, tempB));

                } else {

                    // Calculate ray-plane intersection (floor)
                    float t = -(origin(1) + sphereRadius) / ray(1);
                    Vec3 planePoint = origin + t * ray;

                    // Calculate colour
                    if (t > 0.0f && planePoint(0) < 9.0f && planePoint(0) > -9.0f
                            && planePoint(2) < -1.0f && planePoint(2) > -19.0f) {

                        // Generate ray and test for intersection with sphere
                        Vec3 lightVector = (lightingSource - planePoint);
                        float dShadow = sphereImage.intersectRay(lightVector, planePoint);

                        // Print floor or shadow, depending on intersection
                        if (dShadow > 0.0f) {
                            pixelColour.updateColour(Vec3(sceneColour.black()));
                        } else {
                            pixelColour.updateColour(Vec3(sceneColour.grey()));
                        }
                    } else {
                        pixelColour.updateColour(Vec3(sceneColour.white()));
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
 *
*/

