#pragma once

#include "Coord.h"
#include "colorOptions.h"

void SketchLine(float, float, float, float, vec3);
void putpixel(int, int, vec3);


float x, y, dx, dy;
int steps, k, ptX1, ptY1, ptX2, ptY2;

void SketchLine(float x1, float yy, float x2, float y2, vec3 color)
{
    float dx, dy;
    float steps, k;

    dx = abs(x2 - x1);
    dy = abs(y2 - yy);

    float lx, ly;
    if (x2 > x1)
        lx = 1;
    else
        lx = -1;

    if (y2 > yy)
        ly = 1;
    else
        ly = -1;

    float x = x1, y = yy;
    // slope < 1
    if (dx > dy)
    {
        float p = 2 * dy - dx;
        for (float k = 0; k <= dx; k++)
        {
            putpixel(x, y, color);
            if (p < 0)
            {
                x += lx;
                p += 2 * dy;
            }
            else
            {
                x += lx;
                y += ly;
                p += 2 * dy - 2 * dx;
            }
        }
    }
    else
    { //slope > 1
        float p = 2 * dx - dy;
        for (float k = 0; k <= dy; k++)
        {
            putpixel(x, y, color);
            if (p < 0)
            {
                y += ly;
                p += 2 * dx;
            }
            else
            {
                x += lx;
                y += ly;
                p += 2 * dx - 2 * dy;
            }
        }
    }
}

void putpixel(int x, int y, vec3 color)
{
    glColor3f(color.x, color.y, color.z);
    glPointSize(2);     
    glBegin(GL_POINTS); 
    glLoadIdentity();
    glVertex2i(x, y); 
    glEnd();
}