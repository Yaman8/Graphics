#pragma once

#include <GL/glut.h>

#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#include <array>

#include "colorOptions.h"
#include"vect.h"

template <typename T>
inline T wrap_angle(T theta)
{
    if (theta >= 360)
        theta = 0;
    return theta;

}



struct mat4f
{
    float matrix4[4][4];
};


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