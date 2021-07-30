#pragma once

#include "Coord.h"
#include "triangleRaster.h"
#include"colorOptions.h"
#include"triangleRaster.h"

Point lightDir = { 0,0,3 };


void drawWireframe_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel);
void draw_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel);
float backfaceDetectionNormalize(Point v1, Point v2, Point v3);

void drawWireframe_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel)
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

void draw_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            
        }
        Point n = (wmodel[i].vertices[2] - wmodel[i].vertices[0]).crossProduct(wmodel[i].vertices[1] - wmodel[i].vertices[0]);
        n.normalize();
        float intensity = dotProduct(n, lightDir);
        std::cout<<intensity<<std::endl;
        vec3 col;
        if (intensity > 0)
            fillTriangle(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], red);
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