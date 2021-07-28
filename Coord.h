#pragma once

#include<cmath>
#include<vector>
#include<iostream>

const unsigned int w = 800;
const unsigned int h = 600;
const unsigned int cH = 500;

struct Point {
	float x, y, z, w;
	float xfactor = w / 8.0f;
	float yfactor = h / 8.0f;
	float cube_height = cH / 8.0f;

    Point operator+(Point& translate)
    {
        return { x + translate.x, y + translate.y, z + translate.z, w };
    }
    //inverse the vector direction
    Point operator-(Point& sub)
    {
        return { x - sub.x, y - sub.y, z - sub.z, w };
    }
    Point operator*(float mul)
    {
        return { float(mul * x), float(mul * y), float(mul * z), w };
    }
    Point operator/(float div)
    {
        return { float(x / div), float(y / div), float(z / div), w };
    }
    Point scaleProduct(Point& pt)
    {
        return { x * pt.x, y * pt.y, z * pt.z, w };
    }
    Point crossProduct(Point& pt)
    {
        Point ret;
        ret.x = y * pt.z - z * pt.y;
        ret.y = z * pt.x - x * pt.z;
        ret.z = x * pt.y - y * pt.x;
        // std::cout<<ret;
        // ret = normalize(ret);
        return ret;
    }

    friend std::ostream& operator<<(std::ostream& out, Point& vec)
    {
        out << "( " << vec.x << ", " << vec.y << ", " << vec.z << " )\n";
        return out;
    }

    static Point normalize(Point& pt)
    {
        float mag = pt.x * pt.x + pt.y * pt.y + pt.z * pt.z;
        mag = pow(mag, 0.5);
        pt = pt / (mag);
        return pt;
    }
};

float dotProduct(Point& pt1, Point& pt2)
{
    return { pt1.x * pt2.x + pt1.y * pt2.y + pt1.z * pt2.z };
}

struct Triangle {
    Point vertices[3];
};

struct mat4f {
    float matrix4[4][4];
};