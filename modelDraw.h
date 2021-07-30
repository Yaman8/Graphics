#pragma once

#include "Coord.h"
#include "triangleRaster.h"
#include"colorOptions.h"
#include"triangleRaster.h"

Point lightDir = { 0,0,-3 };


void drawWireframe_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel);
void draw_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel);
float backfaceDetectionNormalize(Point v1, Point v2, Point v3);
float calcIntensity(Point point, Point N, Point view, float specularVal);
void phongIlluminationModel(Triangle& tri, Camera& camera);

void drawWireframe_model(std::vector<Triangle>& model, std::vector<Triangle>& wmodel)
{
    for (int i = 0; i < model.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float val = backfaceDetectionNormalize(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2]);
            if (val < 0)
                wireFrame(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], red);

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
        //Point n = (wmodel[i].vertices[2] - wmodel[i].vertices[0]).crossProduct(wmodel[i].vertices[1] - wmodel[i].vertices[0]);
        //n.normalize();
        //float intensity = dotProduct(n, lightDir);
        //std::cout<<intensity<<std::endl;
        //vec3 col;
        //if (intensity > 0)
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

float calcIntensity(Point point, Point N, Point view, float specularVal) {
    float i = 0.0;
    Point position = { 500, 1000, 800 };
    Point Ldir = (position - point).normalize();
    std::cout << point.x << "\t" << point.y << "\t" << point.z << "\n";
    float ambientInt = 0.4;
    float pointInt = 0.5;

    float ambientConstant = 0.8;
    float diffuseConstant = 0.7;
    float specularConstant = 0.8;

    float ambientLight = ambientConstant * ambientInt;

    float diffuseLight = diffuseConstant * pointInt * dotProduct(N, Ldir);

    // Point R = maths::sub(maths::mul(Normal, (2 * maths::dot(Normal, Ldir))), Ldir);
    Point R = (N * (2 * dotProduct(N, Ldir))) - Ldir;
    float specularLight = specularConstant * pointInt * pow(dotProduct(R, view), specularVal);

    float tmp = ambientLight + specularLight + diffuseLight;
    tmp = tmp > 1 ? 1 : tmp;
    return tmp;
}

void phongIlluminationModel(Triangle& tri, Camera& camera) {
    // for (auto &triangle : cube.triangles)
// {
    Point v1 = tri.vertices[0];
    Point v2 = tri.vertices[1];
    Point v3 = tri.vertices[2];

    Point centroid;
    centroid.x = (v1.x + v2.x + v3.x) / 3;
    centroid.y = (v1.y + v2.y + v3.y) / 3;
    centroid.z = (v1.z + v2.z + v3.z) / 3;

    // std::cout << centroid[0] <<"\t";

    Point view = (camera.Position - centroid).normalize();

    // generating the normal vector of a triangle
    Point ver1 = v1 - v2;
    Point ver2 = v1 - v3;

    Point normal = (v1.crossProduct(ver2)).normalize();

    float intensity = calcIntensity(centroid, normal, view, 10);
    std::cout << "The intensity: " << intensity << "\n";
    vec3 newColor = tri.color * intensity;

    tri.color = newColor;
    // triangle.print();
}
