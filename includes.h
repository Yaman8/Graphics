#include<gl/glut.h>
#include<cmath>
#include"math.h"
#include"transform.h"
#include"matrix.h"
#include"camera.h"
#include"model.h"
#include<vector>

Camera camera = Camera(Point{ 0.0f,0.0f,3.0f });

int width = 800, height = 800;
const float l = 1.6;
bool perspective = false, firstMouse=true;
float val = 0;
vec3 cv = {300,600,150 };
float lastX = width / 2;
float lastY = height / 2;
const unsigned int cubeH = 300;
float xfactor = width/ 8.0f;
float yfactor = height / 8.0f;

void processKeys(unsigned char key, int x, int y);
void processMouse(int xpos, int ypos);

vec3 red = { 1.0,0.0,0.0 };
vec3 green = { 0.0,1.0,0.0 };
vec3 blue = { 0.0,0.0,1.0 };
vec3 white = { 1,1,1 };
vec3 yello = { 1,1,0 };
vec3 unk = { 0,1,1 };

void reshape(int w, int h);
void display();
void putpixel(int x, int y, const vec3& col);
void Line(int x1, int y1, int x2, int y2, const vec3& color);
void triangle(Point v1, Point v2, Point v3, const vec3& color);
void fillTriangle(Point v1, Point v2, Point v3, const vec3& color);
void cube(Point& v0, Point& v1, Point& v2, Point& v3, Point& v4, Point& v5, Point& v6, Point& v7, const vec3& color, bool perspective);
void getProjection(Point& v, bool perspective);
void rotateCube(Point& v0, Point& v1, Point& v2, Point& v3, Point& v4, Point& v5, Point& v6, Point& v7, const vec3& color, bool perspective);
void draw();
void fillBottomFlatTriangle(Point v1, Point v2, Point v3, const vec3& color);
void fillTopFlatTriangle(Point v1, Point v2, Point v3, const vec3& color);

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

void triangle(Point v1, Point v2, Point v3, const vec3& color) {
    //fillTriangle(v1, v2, v3, color);
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v1.x, v1.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v2.x, v2.y, color);
}

void fillTriangle(Point v1, Point v2, Point v3, const vec3& color) {
    if (v1.y > v2.y) { std::swap(v2, v1); }
    if (v1.y > v3.y) { std::swap(v3, v1); }
    if (v2.y > v3.y) { std::swap(v3, v2); }

    if (int(v2.y) == int(v3.y)) { fillBottomFlatTriangle(v1, v2, v3, color); }
    else if (int(v1.y) == int(v2.y)) { fillTopFlatTriangle(v1, v2, v3, color); }
    else
    {
        // general case - split the triangle in a topflat and bottom-flat one
        Point* v4 = new Point({
            (v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)),v2.y, 0
            });
        fillBottomFlatTriangle(v1, v2, *v4, color);
        fillTopFlatTriangle(v2, *v4, v3, color);
    }
}

void cube(Point& v0, Point& v1, Point& v2, Point& v3, Point& v4, Point& v5, Point& v6, Point& v7, const vec3& color, bool perspective) {
    getProjection(v0, perspective);
    getProjection(v1, perspective);
    getProjection(v2, perspective);
    getProjection(v3, perspective);
    getProjection(v4, perspective);
    getProjection(v5, perspective);
    getProjection(v6, perspective);
    getProjection(v7, perspective);


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

void getProjection(Point& v,bool perspective) {
    if (perspective) {
        float xv, yv, zv, zvp = 0, xp, yp, zp;
        float xprp = 450, yprp = 450, zprp = 450;
        zp = zvp;
        float u = (zvp - v.z) / (zprp - v.z);
        xp = v.x - ((zvp - v.z) / (zprp - v.z)) * (v.x - xprp);
        yp = v.y - ((zvp - v.z) / (zprp - v.z)) * (v.y - yprp);
        v.x = xp;
        v.y = yp;
        v.z = zp;
    }
    else {
        float xv, yv, zv, zvp = 0, xp, yp, zp, phi = 45, alpha = 45;
        float xprp, yprp, zprp;
        xp = v.x + l * cos(phi);
        yp = v.y + l * sin(phi);
        float l1 = 0;
        xp = v.x + l1 * (zvp - v.z) * cos(phi);
        yp = v.y + l1 * (zvp - v.z) * sin(phi);
        v.x = xp;
        v.y = yp;
    }
    //std::cout << v.x << " " << v.y << " " << std::endl;
}

void rotateCube(Point& v0, Point& v1, Point& v2, Point& v3, Point& v4, Point& v5, Point& v6, Point& v7, const vec3& color, bool perspective) {
    Point camera;
    Point v = { 300,600,80 };
    camera.x = v.x - cv.x;
    camera.y = v.y - cv.y;
    camera.z = v.z - cv.z;

    getProjection(v0, perspective);
    getProjection(v1, perspective);
    getProjection(v2, perspective);
    getProjection(v3, perspective);
    getProjection(v4, perspective);
    getProjection(v5, perspective);
    getProjection(v6, perspective);
    getProjection(v7, perspective);

    Point t = { -450,-450,150 };
    Point r = { 450,450,-150 };

    if (val > 360) {
        val = 0;
    }
    else {
        val = val + 1.5;
    }
    translate(v0, t);
    translate(v1, t);
    translate(v2, t);
    translate(v3, t);
    translate(v4, t);
    translate(v5, t);
    translate(v6, t);
    translate(v7, t);

    //rotateX(v0, val);
    //rotateX(v1, val);
    //rotateX(v2, val);
    //rotateX(v3, val);
    //rotateX(v4, val);
    //rotateX(v5, val);
    //rotateX(v6, val);
    //rotateX(v7, val);

    rotateY(v0, val);
    rotateY(v1, val);
    rotateY(v2, val);
    rotateY(v3, val);
    rotateY(v4, val);
    rotateY(v5, val);
    rotateY(v6, val);
    rotateY(v7, val);

    translate(v0, r);
    translate(v1, r);
    translate(v2, r);
    translate(v3, r);
    translate(v4, r);
    translate(v5, r);
    translate(v6, r);
    translate(v7, r);

    

    Point normal0 = GetNormal(v0, v1, v2);
    Point normal1 = GetNormal(v1, v5, v6);
    Point normal2 = GetNormal(v4, v0, v3);
    Point normal3 = GetNormal(v5, v4, v7);
    Point normal4 = GetNormal(v0, v4, v5);
    Point normal5 = GetNormal(v3, v2, v7);

    if (dot(camera, normal0) < 0) {
        std::cout<<"Not drawn0"<<std::endl;
    }
    else {
        fillTriangle(v0, v3, v2, red);
        fillTriangle(v0, v1, v2, blue);
    }

    if (dot(camera, normal1) < 0) {
        std::cout << "Not drawn1" << std::endl;
    }
    else {
        fillTriangle(v1, v5, v2, green);
        fillTriangle(v5, v6, v2, yello);
    }

    if (dot(camera, normal2) < 0) {
        std::cout << "Not drawn2" << std::endl;
    }
    else {
        fillTriangle(v0, v7, v3, white);
        fillTriangle(v0, v7, v4, unk);
    }

    if (dot(camera, normal3) < 0) {
        std::cout << "Not drawn3" << std::endl;
    }
    else {
        fillTriangle(v4, v5, v6, green);
        fillTriangle(v4, v7, v6, red);

    }

    //if (dot(camera, normal4) < 0) {
    //    std::cout << "Not drawn4" << std::endl;
    //}
    //else {
    //    fillTriangle(v0, v7, v4, unk);
    //    fillTriangle(v4, v7, v5, unk);

    //}

    //if (dot(camera, normal5) < 0) {
    //    std::cout << "Not drawn5" << std::endl;
    //}
    //else {
    //    fillTriangle(v7, v3, v2, green);
    //    fillTriangle(v7, v2, v6, green);

    //}
  /*  fillTriangle(v0, v3, v2, red);
    fillTriangle(v0, v1, v2, red);
    fillTriangle(v0, v7, v3, white);
    fillTriangle(v3, v7, v4, white);
    fillTriangle(v1, v5, v2, blue);
    fillTriangle(v5, v6, v2, blue);
    fillTriangle(v4, v5, v6, green);
    fillTriangle(v4, v7, v6, green);
    fillTriangle(v0, v7, v4, color);
    fillTriangle(v0, v3, v2, color);
    fillTriangle(v0, v3, v2, color);*/


    //Line(v0.x, v0.y, v1.x, v1.y, color);
    //Line(v1.x, v1.y, v2.x, v2.y, color);
    //Line(v2.x, v2.y, v3.x, v3.y, color);
    //Line(v3.x, v3.y, v0.x, v0.y, color);
    //Line(v4.x, v4.y, v5.x, v5.y, color);
    //Line(v5.x, v5.y, v6.x, v6.y, color);
    //Line(v6.x, v6.y, v7.x, v7.y, color);
    //Line(v7.x, v7.y, v4.x, v4.y, color);
    //Line(v0.x, v0.y, v4.x, v4.y, color);
    //Line(v1.x, v1.y, v5.x, v5.y, color);
    //Line(v2.x, v2.y, v6.x, v6.y, color);
    //Line(v3.x, v3.y, v7.x, v7.y, color);

}

//vec3 Convert_to_Screen(vec3& pt)
//{
//    pt.x = (pt.x + 1.0f) * xfactor;
//    pt.y = (pt.y + 1.0f) * yfactor;
//    // pt.x = (pt.x) * xfactor;
//    // pt.y = (pt.y) * yfactor;
//    pt.z = (pt.z) * cubeH;
//    return pt;
//}

void fillBottomFlatTriangle(Point v1, Point v2, Point v3, const vec3& color)
{
    float invslope1 = (v2.x - v1.x) / (v2.y - v1.y);
    // cout <<"a"<< (v2.x - v1.x) / (v2.y - v1.y)<<endl;
    float invslope2 = (v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v2.x, v2.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v1.x, v1.y, color);

    for (int scanlineY = v1.y; scanlineY < v2.y - 0.5f; scanlineY++)
    {
        // if (scanlineY == v2.y)
        // {
        //     std::cout << "x" << curx1 << "," << curx2 << std::endl;
        //     std::cout << v2.y << endl;
        // }
        Line(curx1, scanlineY, curx2, scanlineY, color);
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

void fillTopFlatTriangle(Point v1, Point v2, Point v3, const vec3& color)
{
    float invslope1 = (v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;
    Line(v1.x, v1.y, v2.x, v2.y, color);
    Line(v2.x, v2.y, v3.x, v3.y, color);
    Line(v3.x, v3.y, v1.x, v1.y, color);

    for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
    {
        Line(curx1, scanlineY, curx2, scanlineY, color);
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}