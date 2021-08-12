#include <math.h>
#include <iostream>

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

struct vec2i
{
    float x, y;
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
    vect4 operator+(vect4 translate)
    {
        return { x + translate.x, y + translate.y, z + translate.z, w };
    }
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
