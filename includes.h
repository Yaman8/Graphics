#include<gl/glut.h>
#include<cmath>
#include"math.h"
#include"transform.h"

int width = 800, height = 800;

void reshape(int w, int h);
void display();
void putpixel(int x, int y, const vec3& col);
void Line(int x1, int y1, int x2, int y2, const vec3& color);
void triangle(vec3i v1, vec3i v2, vec3i v3, const vec3& color);
void fillTriangle(vec3i v1, vec3i v2, vec3i v3, const vec3& color);
void cube(vec3& v0, vec3& v1, vec3& v2, vec3& v3, vec3& v4, vec3& v5, vec3& v6, vec3& v7, const vec3& color);
void getProjection(vec3& v);
//void rotateCube(vec3& v0, vec3& v1, vec3& v2, vec3& v3, vec3& v4, vec3& v5, vec3& v6, vec3& v7, const vec3& color);

void putpixel(int x, int y, const vec3& col) {
    glColor3f(col.x,col.y,col.z);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void Line(int x1, int y1, int x2, int y2, const vec3& color)
{
    int dx, dy;
    int steps, k;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    //Sets increment/decrement : stepsize
    int lx, ly;

    if (x2 > x1) { lx = 1; }
    else { lx = -1; }

    if (y2 > y1) { ly = 1; }
    else { ly = -1; }
    //initialize
    int x = x1, y = y1;
    //slope<1
    if (dx > dy) {
        int p = 2 * dy - dx;
        for (int k = 0; k <= dx; k++) {
            putpixel(x, y, color);
            if (p < 0) {
                x += lx;
                p += 2 * dy;
            }
            else {
                x += lx;
                y += ly;
                p += 2 * dy - 2 * dx;
            }
        }
    }
    //if slope>=1
    else {
        int p = 2 * dx - dy;
        for (int k = 0; k <= dy; k++) {
            putpixel(x, y,color);
            if (p < 0) {
                y += ly;
                p += 2 * dx;
            }
            else {
                x += lx;
                y += ly;
                p += 2 * dx - 2 * dy;
            }
        }
    }
    putpixel(x, y,color);
}

void triangle(vec2i v1, vec2i v2, vec2i v3, const vec3& color) {
    //fillTriangle(v1, v2, v3, color);
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v1.x, v1.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v2.x, v2.y, color);
}

void fillTriangle(vec2i v1, vec2i v2, vec2i v3, const vec3& color) {
    if (v1.y == v2.y && v2.y == v3.y) return;
    //Bubble sort on y-position
    if (v1.y > v2.y) { std::swap(v1, v2); }
    if (v1.y > v3.y) { std::swap(v1, v3); }
    if (v2.y > v3.y) { std::swap(v3, v2); }

    //divide triangle into two halves

    int height = v3.y - v1.y;

    for (int y = v1.y; y <= v2.y; y++)
    {
        int partialHeight = v2.y - v1.y + 1; // +1 because both upper and lower limit is included

        float alpha = (float)(y - v1.y) / height;// be careful with divisions by zero 
        if (partialHeight != 0)
        {
            float beta = (float)(y - v1.y) / partialHeight;
            int Ax = (v1.x + (v3.x - v1.x) * alpha), Ay = v1.y + (v3.y - v1.y) * alpha;
            int Bx = v1.x + (v2.x - v1.x) * beta, By = v1.y + (v2.y - v1.y) * beta;
            if (Ax > Bx) { std::swap(Ax, Bx); }
            for (int j = Ax; j <= Bx; j++)
                putpixel(j, y, color);
        }

    }

    for (int y = v2.y; y <= v3.y; y++)
    {
        int partialHeight = v3.y - v2.y + 1; // +1 because both upper and lower limit is included

        float alpha = (float)(y - v1.y) / height;
        if (partialHeight != 0)
        {
            float beta = (float)(y - v2.y) / partialHeight; // be careful with divisions by zero 

            int Ax = v1.x + (v3.x - v1.x) * alpha, Ay = v1.y + (v3.y - v1.y) * alpha;
            int Bx = v2.x + (v3.x - v2.x) * beta, By = v2.y + (v3.y - v2.y) * beta;
            if (Ax > Bx) { std::swap(Ax, Bx); }
            for (int j = Ax; j <= Bx; j++)
                putpixel(j, y, color);
        }

    }
}

void cube(vec3& v0, vec3& v1, vec3& v2, vec3& v3, vec3& v4, vec3& v5, vec3& v6, vec3& v7, const vec3& color) {
    getProjection(v0);
    getProjection(v1);
    getProjection(v2);
    getProjection(v3);
    getProjection(v4);
    getProjection(v5);
    getProjection(v6);
    getProjection(v7);

    Line(v0.x, v0.y, v1.x, v1.y,color);
    Line(v1.x, v1.y, v2.x, v2.y,color);
    Line(v2.x, v2.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v0.x, v0.y, color);
    Line(v4.x, v4.y, v5.x, v5.y, color);
    Line(v5.x, v5.y, v6.x, v6.y, color);
    Line(v6.x, v6.y, v7.x, v7.y, color);
    Line(v7.x, v7.y, v4.x, v4.y, color);
    Line(v0.x, v0.y, v4.x, v4.y, color);
    Line(v1.x, v1.y, v5.x, v5.y, color);
    Line(v2.x, v2.y, v6.x, v6.y, color);
    Line(v3.x, v3.y, v7.x, v7.y, color);

    /*fillTriangle(v0,v3,v2, color);
    fillTriangle(v0, v1, v2, color);
    fillTriangle(v0, v4, v7, color);
    fillTriangle(v0, v1, v4, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);*/


}

void getProjection(vec3& v) {
    float xv, yv, zv, zvp = 0, xp, yp, zp;
    float xprp = 450, yprp =450, zprp = 450;
    zp = zvp;
    float u = (zvp - v.z) / (zprp - v.z);
    xp = v.x - ((zvp - v.z) / (zprp - v.z)) * (v.x - xprp);
    yp = v.y - ((zvp - v.z) / (zprp - v.z)) * (v.y - yprp);
    v.x = xp;
    v.y = yp;
    v.z = zp;
    //std::cout << v.x << " " << v.y << " " << std::endl;
}

void rotateCube(vec3& v0, vec3& v1, vec3& v2, vec3& v3, vec3& v4, vec3& v5, vec3& v6, vec3& v7, const vec3& color) {
    float val = 45;
    rotateY(v0, val);
    rotateY(v1, val);
    rotateY(v2, val);
    rotateY(v3, val);
    rotateY(v4, val);
    rotateY(v5, val);
    rotateY(v6, val);
    rotateY(v7, val);

    getProjection(v0);
    getProjection(v1);
    getProjection(v2);
    getProjection(v3);
    getProjection(v4);
    getProjection(v5);
    getProjection(v6);
    getProjection(v7);

    Line(v0.x, v0.y, v1.x, v1.y, color);
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v2.x, v2.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v0.x, v0.y, color);
    Line(v4.x, v4.y, v5.x, v5.y, color);
    Line(v5.x, v5.y, v6.x, v6.y, color);
    Line(v6.x, v6.y, v7.x, v7.y, color);
    Line(v7.x, v7.y, v4.x, v4.y, color);
    Line(v0.x, v0.y, v4.x, v4.y, color);
    Line(v1.x, v1.y, v5.x, v5.y, color);
    Line(v2.x, v2.y, v6.x, v6.y, color);
    Line(v3.x, v3.y, v7.x, v7.y, color);
}