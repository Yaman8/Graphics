#pragma once

#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <math.h>
#include <array>

#include "colorOptions.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;
const unsigned int ZHEIGHT = 500;

const int m = 4;

float deg_to_rad(float degree)
{
    return (3.1416 * degree / 180);
}

float rad_to_deg(float radian)
{
    return (180 * radian) / 3.1416;
}

template <typename T>
inline T wrap_angle(T theta)
{
    if (theta >= 360)
        theta = 0;
    return theta;

}

struct vec2i
{
    float x, y;
};

struct mat4f
{
    float matrix4[4][4];
};

struct vect4
{
    float x = 0, y = 0, z = 0, w = 1;
    float xfactor = WIDTH / 8.0f;
    float yfactor = HEIGHT / 8.0f;
    float zheight = ZHEIGHT / 8.0f;


    vect4 Convert_to_Screen()
    {
        x = (x + 1.0f) * xfactor;
        y = (y + 1.0f) * yfactor;

        z = (z)*zheight;
        return { x,y,z };
    }
    vect4 inverse()
    {
        return { -x, -y, -z, w };
    }
    //vector addition of a point
    vect4 operator+(vect4 translate)
    {
        return { x + translate.x, y + translate.y, z + translate.z, w };
    }
    //inverse the vector direction
    vect4 operator-(vect4 sub)
    {
        return { x - sub.x, y - sub.y, z - sub.z, w };
    }
    vect4 operator*(float mul)
    {
        return { float(mul * x), float(mul * y), float(mul * z), w };
    }
    vect4 operator*(vect4 mul)
    {
        return { float(mul.x * x), float(mul.y * y), float(mul.z * z), w };
    }
    vect4 operator/(float div)
    {
        return { float(x / div), float(y / div), float(z / div), w };
    }
    vect4 scaleProduct(float pt)
    {
        return { x * pt, y * pt, z * pt, w };
    }
    vect4 crossProduct(vect4 pt)
    {
        vect4 ret;
        ret.x = y * pt.z - z * pt.y;
        ret.y = z * pt.x - x * pt.z;
        ret.z = x * pt.y - y * pt.x;
        // std::cout<<ret;
        // ret = normalize(ret);
        return ret;
    }

    friend std::ostream& operator<<(std::ostream& out, vect4& vec)
    {
        out << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )\n";
        return out;
    }

    vect4 normalize()
    {
        float mag = x * x + y * y + z * z;
        mag = pow(mag, 0.5);
        return { x / mag, y / mag, z / mag };
    }
};

float dotProduct(vect4 pt1, vect4 pt2)
{
    return { pt1.x * pt2.x + pt1.y * pt2.y + pt1.z * pt2.z };
}

struct Triangle {
    vect4 vertices[3];
    vect4 normals[3];
    vec2i texCoords[3];
    vec3 color;
    vect4 vertex_intensity[3];
    float zbuffer;

    Triangle(const Triangle& tri)
    {
        for (int i = 0; i < 3; i++) {
            vertices[i] = tri.vertices[i];
            normals[i] = tri.normals[i];
            texCoords[i] = tri.texCoords[i];
        }
        color = tri.color;
    }

    Triangle()
    {
        color = { 0.8,0.8,0.8 };

        vertices[0] = vect4{ 0, 0, 0 };
        vertices[1] = vect4{ 0, 0, 0 };
        vertices[2] = vect4{ 0, 0, 0 };
    }

    Triangle(vect4 a, vect4 b, vect4 c)
    {
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;
    }

    Triangle(vect4 a, vect4 b, vect4 c, vec3 mcolor)
    {
        color = mcolor;
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;
    }

    void setVertex(vect4 a, vect4 b, vect4 c)
    {
        vertices[0] = a;
        vertices[1] = b;
        vertices[2] = c;
    }

    void setNormals(vect4 na, vect4 nb, vect4 nc)
    {
        normals[0] = na;
        normals[1] = nb;
        normals[2] = nc;
    }

    void setTexCoords(vec2i uv1, vec2i uv2, vec2i uv3)
    {
        texCoords[0] = uv1;
        texCoords[1] = uv2;
        texCoords[2] = uv3;

    }

    void setIntensity(std::vector<float> intense);
    void Rasterize1();
    void Rasterize2();
};