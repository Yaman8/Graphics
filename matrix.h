#pragma once

#include "transform.h"
#include"model.h"
#include<gl/glut.h>
#include<vector>

mat4f mul(mat4f a, mat4f b);
mat4f perspectiveMatrix(vect4 eye);
mat4f rotateMatrix(float yaw, float pitch, float roll);
mat4f orthoprojectMatrix();
vect4 mul(mat4f matrix, vect4& p);
mat4f newPerspective(float fov, float aspect);
vect4 getnormal(vect4 point1, vect4 point2, vect4 point3);
std::vector<float> interpolate(float i0, float d0, float il, float dl);


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

mat4f perspectiveMatrix(vect4 eye)
{
    float zprp = eye.z, xprp = eye.x, yprp = eye.y;
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

mat4f newPerspective(float fov, float aspect)
{
    float zNear = 0.1;

    // float zFar = 100.0f;

    float zFar = -100.0f;
    float zRange = zNear - zFar;
    mat4f projection = { {{1 / (aspect * tan(fov / 2)), 0, 0, 0},
                         {0, 1 / tan(fov / 2), 0, 0},
                         {0, 0, (zFar + zNear) / zRange, (2 * zFar * zNear) / zRange},
                         {0, 0, -1, 0}} };


    return projection;
}

mat4f orthoprojectMatrix()
{
    mat4f ortho = { {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}} };
    return ortho;
}


vect4 mul(mat4f matrix, vect4& p)
{

    // float homogenous_b[] = {b[0], b[1], b[2], 1};
    vect4 temp;
    temp.x = matrix.matrix4[0][0] * p.x + matrix.matrix4[0][1] * p.y + matrix.matrix4[0][2] * p.z + matrix.matrix4[0][3];
    temp.y = matrix.matrix4[1][0] * p.x + matrix.matrix4[1][1] * p.y + matrix.matrix4[1][2] * p.z + matrix.matrix4[1][3];
    temp.z = matrix.matrix4[2][0] * p.x + matrix.matrix4[2][1] * p.y + matrix.matrix4[2][2] * p.z + matrix.matrix4[2][3];
    temp.w = p.w;
    return temp;
}

//std::vector<float> interpolate(float i0, float d0, float il, float dl)
//{
//    std::vector<float> values;
//
//    if (i0 == il)
//    {
//        values.push_back(d0);
//        return values;
//    }
//
//    float a = (dl - d0) / (il - i0);
//    float d = d0;
//
//    for (int i = i0; i < il; i++)
//    {
//        values.push_back(d);
//        d = d + a;
//    }
//    return values;
//}

vect4 getnormal(vect4 point1, vect4 point2, vect4 point3)
{
    vect4 ver1 = point1 - point2;
    vect4 ver2 = point1 - point3;;

    vect4 normal = (ver1.crossProduct(ver2)).normalize();
    return normal;
}