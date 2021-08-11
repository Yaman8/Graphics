#pragma once

#include "transform.h"

// functions
void viewc(vect4& pt, vect4 viewp);
void oblique(vect4& pt, int zvp, float alpha, float phi);
void perspective(vect4& pt, int zvp, vect4& prp);

float idenity_matrix[4][4] = { {1, 0, 0, 0},
                              {0, 1, 0, 0},
                              {0, 0, 1, 0},
                              {0, 0, 0, 1} };

void viewc(vect4& pt, vect4 viewp)
{
    pt = pt - viewp;
    matrix_product(pt, idenity_matrix);
}

void oblique(vect4& pt, int zvp, float alpha, float phi) {
    alpha = deg_to_radians(alpha);
    phi = deg_to_radians(phi);
    vect4 temp;
    float L1 = 1.0 / tan(alpha);
    temp.x = pt.x + L1 * (zvp - pt.z) * cos(phi);
    temp.y = pt.y + L1 * (zvp - pt.z) * sin(phi);
    temp.z = zvp;
    pt = std::move(temp);
}

void perspective(vect4& pt, int zvp, vect4& prp) {
    float u = (zvp - pt.z) / (prp.z - pt.z);
    vect4 temp;
    temp.x = pt.x - u * (pt.x - prp.x);
    temp.y = pt.y - u * (pt.y - prp.y);
    temp.z = zvp;
    pt = std::move(temp);
}