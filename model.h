#pragma once

#include<fstream>
#include<sstream>
#include<vector>
#include "transform.h"
#include"Coord.h"
#include"camera.h"
#include"triangleRaster.h"

class Model {
private:
    std::vector<Triangle> triangles;
    std::vector<Triangle> ftriangles;
public:
    void load(std::string);
    void convertToScreen_model();
    void rotate_model(float);
    void translate_model(vect4);
    void scale_model(float);
    void applyTransform(mat4f&);
    bool backfaceDetectionNormalize(Triangle& tri);
    void draw();
    float calculateIntensity(vect4, vect4, vect4, float);
    void phongIlluminationModel(Triangle&);

    Camera* camera;
};

void Model::draw() {
    //drawWireframe_model(ftriangles);
    draw_model(ftriangles);
}

void Model::load(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    if (file.fail())
    {
        std::cout << "File cannot be opened \n";
        exit(-1);
    }
    //std::cout << "open";
    // Local cache of verts
    std::vector<vect4> verts;

    while (!file.eof())
    {
        char line[128];
        file.getline(line, 128);

        std::stringstream s;
        s << line;

        char junk;

        if (line[0] == 'v')
        {
            vect4 v;
            s >> junk >> v.x >> v.y >> v.z;
            verts.push_back(v);
        }

        if (line[0] == 'f')
        {
            int f[3];
            s >> junk >> f[0] >> f[1] >> f[2];
            triangles.push_back(Triangle{ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
        }
    }
    ftriangles = triangles;
}

void Model::convertToScreen_model() {
    for (int i = 0; i < triangles.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            triangles[i].vertices[j] = triangles[i].vertices[j].Convert_to_Screen();
        }
    }
}

void Model::translate_model(vect4 pt) {
    for (int i = 0; i < triangles.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            transate_polygon(triangles[i].vertices[j], pt); 
        }
    }
}

void Model::scale_model(float pt) {
    for (int i = 0; i < triangles.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scale_polygon(triangles[i].vertices[j], pt);
        }
    }
}

void Model::rotate_model(float angle) {
    for (int i = 0; i < triangles.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            rotateX(triangles[i].vertices[j], angle);
            rotateY(triangles[i].vertices[j], angle);
            //rotateZ(triangles[i].vertices[j], angle);
        }
    }
}

void Model::applyTransform(mat4f& transform)
{
    ftriangles.clear();
    int cullCount = 0;

    for (auto& tri : triangles)
    {
        Triangle temptri = tri;
        temptri.vertices[0] = mul(transform, tri.vertices[0]);
        temptri.vertices[1] = mul(transform, tri.vertices[1]);
        temptri.vertices[2] = mul(transform, tri.vertices[2]);
        bool culled = backfaceDetectionNormalize(temptri);
        if (culled)
            cullCount++;
    }
    int counter = 0;
    for (auto& tri : ftriangles)
    {
        counter++;
        phongIlluminationModel(tri);
    }
    // std::cout << "The counter is: " << counter;
}

bool Model::backfaceDetectionNormalize(Triangle& tri)
{
    vect4 v1 = tri.vertices[0], v2 = tri.vertices[1], v3 = tri.vertices[2];
    vect4 centroid;
    centroid.x = (v1.x + v2.x + v3.x) / 3;
    centroid.y = (v1.y + v2.y + v3.y) / 3;
    centroid.z = (v1.z + v2.z + v3.z) / 3;

    vect4 V = (camera->Position - centroid).normalize();
    // Point cameraPosition = {0,0,-1000};
    // Point V = (cameraPosition - centroid).normalize();

    v2 = v2 - v1;
    v3 = v3 - v1;

    vect4 normal = v2.crossProduct(v3);
    normal = normal.normalize();
    // std::cout<<normal;

    float value = dotProduct(normal, V);
    if (value < 0)
    {
        ftriangles.push_back(tri);
        return false;
    }
    return true;
}

float Model::calculateIntensity(vect4 point, vect4 Normal, vect4 View, float specularExp)
{
    float i = 0.0;
    vect4 position = { 500, 600, -200 };
    vect4 Ldir = (position - point).normalize();
    std::cout << point.x << "\t" << point.y << "\t" << point.z << "\n";
    float ambientInt = 0.4;
    float pointInt = 0.5;

    float ambientConstant = 0.8;
    float diffuseConstant = 0.7;
    float specularConstant = 0.8;

    float ambientLight = ambientConstant * ambientInt;

    float diffuseLight = diffuseConstant * pointInt * dotProduct(Normal, Ldir);

    // Point R = maths::sub(maths::mul(Normal, (2 * maths::dot(Normal, Ldir))), Ldir);
    vect4 R = (Normal * (2 * dotProduct(Normal, Ldir))) - Ldir;
    float specularLight = specularConstant * pointInt * pow(dotProduct(R, View), specularExp);

    float tmp = ambientLight + specularLight + diffuseLight;
    tmp = tmp > 1 ? 1 : tmp;
    return tmp;
}

void Model::phongIlluminationModel(Triangle& tri)
{
    // for (auto &triangle : cube.triangles)
    // {
    vect4 v1 = tri.vertices[0];
    vect4 v2 = tri.vertices[1];
    vect4 v3 = tri.vertices[2];

    vect4 centroid;
    centroid.x = (v1.x + v2.x + v3.x) / 3;
    centroid.y = (v1.y + v2.y + v3.y) / 3;
    centroid.z = (v1.z + v2.z + v3.z) / 3;

    // std::cout << centroid[0] <<"\t";

    vect4 view = (camera->Position - centroid).normalize();

    // generating the normal vector of a triangle
    vect4 ver1 = v1 - v2;
    vect4 ver2 = v1 - v3;

    vect4 normal = (v1.crossProduct(ver2)).normalize();

    float intensity = calculateIntensity(centroid, normal, view, 10);
    //std::cout << "The intensity: " << intensity << "\n";
    vec3 newColor = tri.color * intensity;

    tri.color = newColor;
    // triangle.print();
}