#pragma once

#include "Coord.h"
#include "triangleRaster.h"
#include"colorOptions.h"
#include"triangleRaster.h"

void drawWireframe_model(std::vector<Triangle>& model);
void draw_model(std::vector<Triangle>& model);
float backfaceDetectionNormalize(Point v1, Point v2, Point v3);

void drawWireframe_model(std::vector<Triangle>& model)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float val = backfaceDetectionNormalize(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2]);
            if (val < 0)
                wireFrame(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], red);

            // std::cout << model[i].vertices[0];
            // std::cout << model[i].vertices[1];
            // std::cout << model[i].vertices[2]<<std::endl;
        }
    }
}

void draw_model(std::vector<Triangle>& model)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fillTriangle(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], red);
        }
    }
}

float backfaceDetectionNormalize(Point v1, Point v2, Point v3)
{
    Point V = { 0,0,100,0 };
    V = V.normalize();
    Point newPoint1 = v1, newPoint2 = v2, newPoint3 = v3;
    newPoint2 = newPoint2 - newPoint1;
    newPoint3 = newPoint3 - newPoint1;

    Point normal = newPoint2.crossProduct(newPoint3);
    normal = normal.normalize();
    // std::cout<<normal;

    float value = dotProduct(normal, V);

    return value;
}