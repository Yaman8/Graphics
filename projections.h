#pragma once

#include "transform.h"

// functions
void view(Point& pt, Point viewp);
void oblique(Point& pt, int zvp, float alpha, float phi);
void perspective(Point& pt, int zvp, Point& prp);

float idenity_matrix[4][4] = { {1, 0, 0, 0},
                              {0, 1, 0, 0},
                              {0, 0, 1, 0},
                              {0, 0, 0, 1} };

void view(Point& pt, Point viewp)
{
    //view = translate + rotate
    pt = pt - viewp;
    //rotate
    matrix_product(pt, idenity_matrix);
}

void oblique(Point& pt, int zvp, float alpha, float phi) {
    alpha = deg_to_radians(alpha);
    phi = deg_to_radians(phi);
    Point temp;
    float L1 = 1.0 / tan(alpha);
    temp.x = pt.x + L1 * (zvp - pt.z) * cos(phi);
    temp.y = pt.y + L1 * (zvp - pt.z) * sin(phi);
    temp.z = zvp;
    pt = std::move(temp);
}

void perspective(Point& pt, int zvp, Point& prp) {
    float u = (zvp - pt.z) / (prp.z - pt.z);
    Point temp;
    temp.x = pt.x - u * (pt.x - prp.x);
    temp.y = pt.y - u * (pt.y - prp.y);
    temp.z = zvp;
    pt = std::move(temp);
}
