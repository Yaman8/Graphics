#pragma once

#define WHITE {1.0f, 1.0f, 1.0f}
#define RED {1.0f, 0.0f, 0.0f}
#define GREEN {0.0f, 1.0f, 0.0f}
#define BLUE {0.0f, 0.0f, 1.0f}
#define YELLOW {1.0f, 1.0f, 0.0f}
#define BLACK {0.0f, 0.0f, 0.0f}
#define ORANGE {1.0f, 0.5f, 0.0f}
#define PURPLE {1.0f, 0.0f, 1.0f}


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