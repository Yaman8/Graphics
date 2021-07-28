#pragma once

#include "transform.h"
#include"model.h"
#include<gl/glut.h>
#include<vector>

void applyTransform(mat4f& transform, std::vector<Triangle>& triangles);
mat4f mul(mat4f a, mat4f b);
mat4f perspectiveMatrix();
mat4f rotateMatrix(float yaw, float pitch, float roll);
mat4f orthoprojectMatrix();
Point mul(mat4f matrix, Point& p);


mat4f mul(mat4f a, mat4f b)
{
    mat4f product = { 0 };
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                product.matrix4[i][j] += a.matrix4[i][k] * b.matrix4[k][j];
            }
        }
    }
    return product;
}

mat4f perspectiveMatrix()
{
    float zprp = 250, xprp = 100, yprp = 100;
    float zvp = 0;
    float dp = zprp - zvp;
    mat4f persmatrix = { {{1, 0, xprp / dp, -xprp * zvp / dp},
                         {0, 1, yprp / dp, -yprp * zvp / dp},
                         {0, 0, -zvp / dp, zvp * (zprp / dp)},
                         {0, 0, -1 / dp, zprp / dp}} };
    return persmatrix;
}

mat4f rotateMatrix(float yaw, float pitch = 0, float roll = 0)
{
    // std::cout << "Hello";
    mat4f rotation = { {{cos(yaw) * cos(pitch), cos(yaw) * sin(pitch) * sin(roll) - sin(yaw) * cos(roll), cos(yaw) * sin(pitch) * cos(roll) + sin(yaw) * sin(roll), 0},
                       {sin(yaw) * cos(pitch), sin(yaw) * sin(pitch) * sin(roll) + cos(yaw) * cos(roll), sin(yaw) * sin(pitch) * cos(roll) - cos(yaw) * sin(roll), 0},
                       {-sin(pitch), cos(pitch) * sin(roll), cos(pitch) * cos(roll), 0},
                       {0, 0, 0, 1}} };
    return rotation;
}

mat4f orthoprojectMatrix()
{
    mat4f ortho = { {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}} };
    return ortho;
}

void applyTransform(mat4f& transform, std::vector<Triangle>& triangles)
{
    for (auto& tri : triangles)
    {
        tri.vertices[0] = mul(transform, tri.vertices[0]);
        tri.vertices[1] = mul(transform, tri.vertices[1]);
        tri.vertices[2] = mul(transform, tri.vertices[2]);
    }
    glutPostRedisplay();
}

Point mul(mat4f matrix, Point& p)
{

    // float homogenous_b[] = {b[0], b[1], b[2], 1};
    Point temp;
    temp.x = matrix.matrix4[0][0] * p.x + matrix.matrix4[0][1] * p.y + matrix.matrix4[0][2] * p.z + matrix.matrix4[0][3];
    temp.y = matrix.matrix4[1][0] * p.x + matrix.matrix4[1][1] * p.y + matrix.matrix4[1][2] * p.z + matrix.matrix4[1][3];
    temp.z = matrix.matrix4[2][0] * p.x + matrix.matrix4[2][1] * p.y + matrix.matrix4[2][2] * p.z + matrix.matrix4[2][3];
    temp.w = p.w;
    return temp;
}