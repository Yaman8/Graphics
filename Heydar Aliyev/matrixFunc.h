#pragma once

#include "Coord.h"

//Required matrix transformations

vect4 mul(mat4f matrix, vect4& p)
{

    vect4 temp;
    temp.x = matrix.matrix4[0][0] * p.x + matrix.matrix4[0][1] * p.y + matrix.matrix4[0][2] * p.z + matrix.matrix4[0][3];
    temp.y = matrix.matrix4[1][0] * p.x + matrix.matrix4[1][1] * p.y + matrix.matrix4[1][2] * p.z + matrix.matrix4[1][3];
    temp.z = matrix.matrix4[2][0] * p.x + matrix.matrix4[2][1] * p.y + matrix.matrix4[2][2] * p.z + matrix.matrix4[2][3];
    temp.w = p.w;
    return temp;
}

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

mat4f Perspective(float fov, float aspect)
{
    float zNear = 0.9;

    float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

    float zFar = -1.0f;
    float zRange = zNear - zFar;


    mat4f projection = { {{aspect * fovRad, 0,0,0},
                        {0, fovRad, 0, 0},
                        {0,0,zFar / (zFar - zNear),1},
                        {0,0,(-zFar * zNear) / (zFar - zNear), 0}} };
    return projection;


}

mat4f rotateMatrix(float yaw, float pitch = 0, float roll = 0)
{
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

std::vector<float> interpolate(float i0, float d0, float il, float dl)
{
    std::vector<float> values;

    if (i0 == il)
    {
        values.push_back(d0);
        return values;
    }

    float a = (dl - d0) / (il - i0);
    float d = d0;

    for (int i = i0; i < il; i++)
    {
        values.push_back(d);
        d = d + a;
    }
    return values;
}

vect4 getnormal(vect4 point1, vect4 point2, vect4 point3)
{
    vect4 ver1 = point1 - point2;
    vect4 ver2 = point1 - point3;;

    vect4 normal = (ver1.crossProduct(ver2)).normalize();
    return normal;
}

static mat4f RotView(vect4 right, vect4 up, vect4 dir)
{
    return {
        right.x,right.y,right.z,0.0f,
        up.x,up.y,up.z,0.0f,
        dir.x,dir.y,dir.z,0.0f,
        0.0f,0.0f,0.0f,1.0f,
    };
}

static mat4f TranslateView(vect4 pos)
{
    return {
        1.0f,0.0f,0.0f,-pos.x,
        0.0f,1.0f,0.0f,-pos.y,
        0.0f,0.0f,1.0f,-pos.z,
        0.0f,0.0f,0.0f,1.0f,
    };
}

mat4f Matrix_PointAt(vect4& pos, vect4& target, vect4& up)
{
    // Calculate new forward direction
    vect4 newForward = target - pos;
    newForward = newForward.normalize();

    // Calculate new Up direction
    vect4 a = (newForward * dotProduct(up, newForward));
    vect4 newUp = up - a;
    newUp = newUp.normalize();

    // New Right direction is just cross product
    vect4 newRight = (newUp.crossProduct(newForward));

    mat4f matrix;
    matrix.matrix4[0][0] = newRight.x;
    matrix.matrix4[0][1] = newRight.y;
    matrix.matrix4[0][2] = newRight.z;
    matrix.matrix4[0][3] = 0.0f;
    matrix.matrix4[1][0] = newUp.x;
    matrix.matrix4[1][1] = newUp.y;
    matrix.matrix4[1][2] = newUp.z;
    matrix.matrix4[1][3] = 0.0f;
    matrix.matrix4[2][0] = newForward.x;
    matrix.matrix4[2][1] = newForward.y;
    matrix.matrix4[2][2] = newForward.z;
    matrix.matrix4[2][3] = 0.0f;
    matrix.matrix4[3][0] = pos.x;
    matrix.matrix4[3][1] = pos.y;
    matrix.matrix4[3][2] = pos.z;
    matrix.matrix4[3][3] = 1.0f;
    return matrix;
}

mat4f Matrix_QuickInverse(mat4f& m) // Only for Rotation/Translation Matrices
{
    mat4f matrix;
    matrix.matrix4[0][0] = m.matrix4[0][0];
    matrix.matrix4[0][1] = m.matrix4[1][0];
    matrix.matrix4[0][2] = m.matrix4[2][0];
    matrix.matrix4[0][3] = 0.0f;
    matrix.matrix4[1][0] = m.matrix4[0][1];
    matrix.matrix4[1][1] = m.matrix4[1][1];
    matrix.matrix4[1][2] = m.matrix4[2][1];
    matrix.matrix4[1][3] = 0.0f;
    matrix.matrix4[2][0] = m.matrix4[0][2];
    matrix.matrix4[2][1] = m.matrix4[1][2];
    matrix.matrix4[2][2] = m.matrix4[2][2];
    matrix.matrix4[2][3] = 0.0f;
    matrix.matrix4[3][0] = -(m.matrix4[3][0] * matrix.matrix4[0][0] + m.matrix4[3][1] * matrix.matrix4[1][0] + m.matrix4[3][2] * matrix.matrix4[2][0]);
    matrix.matrix4[3][1] = -(m.matrix4[3][0] * matrix.matrix4[0][1] + m.matrix4[3][1] * matrix.matrix4[1][1] + m.matrix4[3][2] * matrix.matrix4[2][1]);
    matrix.matrix4[3][2] = -(m.matrix4[3][0] * matrix.matrix4[0][2] + m.matrix4[3][1] * matrix.matrix4[1][2] + m.matrix4[3][2] * matrix.matrix4[2][2]);
    matrix.matrix4[3][3] = 1.0f;
    return matrix;
}


mat4f Matrix_MakeRotationX(float fAngleRad)
{
    mat4f matrix;
    matrix.matrix4[0][0] = 1.0f;
    matrix.matrix4[1][1] = cosf(fAngleRad);
    matrix.matrix4[1][2] = sinf(fAngleRad);
    matrix.matrix4[2][1] = -sinf(fAngleRad);
    matrix.matrix4[2][2] = cosf(fAngleRad);
    matrix.matrix4[3][3] = 1.0f;
    return matrix;
}
mat4f Matrix_MakeRotationY(float fAngleRad)
{
    mat4f matrix = { {{cosf(fAngleRad), 0.0f, sinf(fAngleRad), 0.0f},
                     {0.0f, 1.0f, 0.0f, 0.0f},
                     {-sinf(fAngleRad), 0.0f, cosf(fAngleRad), 0.0f},
                     {0.0f,0.0f,0.0f,1.0f}} };

    return matrix;
}

mat4f Matrix_MakeRotationZ(float fAngleRad)
{
    mat4f matrix;
    matrix.matrix4[0][0] = cosf(fAngleRad);
    matrix.matrix4[0][1] = sinf(fAngleRad);
    matrix.matrix4[1][0] = -sinf(fAngleRad);
    matrix.matrix4[1][1] = cosf(fAngleRad);
    matrix.matrix4[2][2] = 1.0f;
    matrix.matrix4[3][3] = 1.0f;
    return matrix;
}

static mat4f Translation(float tx, float ty, float tz)
{
    return {
        1.0,0.0,0.0,tx,
        0.0,1.0,0.0,ty,
        0.0,0.0,1.0,tz,
        0.0,0.0,0.0,1.0,
    };
}