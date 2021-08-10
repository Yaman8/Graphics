#pragma once

#include "Coord.h"
#include "colorOptions.h"
#include"math.h"

class Vertex
{
public:
    vect4 pos;
    vect4 normal;
    vect4 color;

public:
    Vertex() = default;
    /*Vertex(const Point& pos)
        :
        pos(pos)
    {}
    Vertex(const Point& pos, const Vertex& src)
        :
        color(src.color),
        pos(pos)
    {}*/
    Vertex(const vect4& pos, const vect4& normal, const vec3& c)
        :
        normal(normal),
        pos(pos)
    {
        color.x = c.x;
        color.y = c.y;
        color.z = c.z;
    }
    Vertex& operator+=(const Vertex& rhs)
    {
        pos = pos + rhs.pos;
        color = color + rhs.color;
        return *this;
    }
    Vertex operator+(const Vertex& rhs) const
    {
        return Vertex(*this) += rhs;
    }
    Vertex& operator-=(const Vertex& rhs)
    {
        pos = pos - rhs.pos;
        color = color - rhs.color;
        return *this;
    }
    Vertex operator-(const Vertex& rhs) const
    {
        return Vertex(*this) -= rhs;
    }
    Vertex& operator*=(float rhs)
    {
        pos = pos * rhs;
        color = color * rhs;
        return *this;
    }
    Vertex operator*(float rhs) const
    {
        return Vertex(*this) *= rhs;
    }
    Vertex& operator/=(float rhs)
    {
        pos = pos / rhs;
        color = color / rhs;
        return *this;
    }
    Vertex operator/(float rhs) const
    {
        return Vertex(*this) /= rhs;
    }
};