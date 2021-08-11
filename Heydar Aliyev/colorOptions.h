#pragma once


#include<iostream>

struct vec3
{
    float x, y, z;

    vec3 operator*(float mul)
    {
        return { float(mul * x), float(mul * y), float(mul * z) };
    }
    vec3 normalize()
    {
        float mag = x * x + y * y + z * z;
        mag = pow(mag, 0.5);
        return { x / mag,y / mag,z / mag };
    }
};

vec3 WHITE = { 1.0f, 1.0f, 1.0f };
vec3 RED={ 1.0f, 0.0f, 0.0f };
vec3 GREEN= {0.0f, 1.0f, 0.0f};
vec3 BLUE ={0.0f, 0.0f, 1.0f};
vec3 YELLOW ={1.0f, 1.0f, 0.0f};
vec3 BLACK ={0.0f, 0.0f, 0.0f};
vec3 ORANGE ={1.0f, 0.5f, 0.0f};
vec3 PURPLE ={1.0f, 0.0f, 1.0f};