#pragma once

#include "Coord.h"

//transformation functions
void transate_polygon(vect4& pt, vect4 translate);
void scale_polygon(vect4& pt, vect4 scale);
void rotateX(vect4& pt, float angle);
void rotateY(vect4& pt, float angle);
void rotateZ(vect4& pt, float angle);
void matrix_product(vect4& p, float matrix[m][m]);

///////////////////            3D transformation        ///////////////////

void matrix_product(vect4& p, float matrix[m][m])
{
    vect4 temp;
    temp.x = matrix[0][0] * p.x + matrix[0][1] * p.y + matrix[0][2] * p.z + matrix[0][3];
    temp.y = matrix[1][0] * p.x + matrix[1][1] * p.y + matrix[1][2] * p.z + matrix[1][3];
    temp.z = matrix[2][0] * p.x + matrix[2][1] * p.y + matrix[2][2] * p.z + matrix[2][3];
    p = std::move(temp);
}

void transate_polygon(vect4& pt, vect4 translate)
{
    pt = pt + translate;
}

void scale_polygon(vect4& pt, float scale)
{

    pt = pt.scaleProduct(scale);
}

void rotateX(vect4& pt, float angle)
{
    angle = deg_to_rad(angle);
    float composite[m][m] = { {1, 0, 0, 0},
                             {0, cos(angle), -sin(angle), 0},
                             {0, sin(angle), cos(angle), 0},
                             {0, 0, 0, 1} };
    matrix_product(pt, composite);
}

void rotateY(vect4& pt, float angle)
{
    angle = deg_to_rad(angle);
    float composite[m][m] = { {cos(angle), 0, sin(angle), 0},
                             {0, 1, 0, 0},
                             {-sin(angle),0 , cos(angle), 0},
                             {0, 0, 0, 1} };
    matrix_product(pt, composite);
}

void rotateZ(vect4& pt, float angle)
{
    angle = deg_to_rad(angle);
    float composite[m][m] = { {cos(angle), -sin(angle), 0, 0},
                             {sin(angle), cos(angle), 0, 0},
                             {0, 0, 1, 0},
                             {0, 0, 0, 1} };
    matrix_product(pt, composite);
}