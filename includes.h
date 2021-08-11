#include<gl/glew.h>
#include<gl/glut.h>
#include<cmath>
#include"math.h"
#include"transform.h"
#include"matrix.h"
#include"camera.h"
#include"model.h"
#include<vector>
#include"projections.h"
#include"lineFunc.h"
#include"triangleRaster.h"
#include"colorOptions.h"
//#include"modelDraw.h"
//#include"modelFuncs.h"

Camera* camera = new Camera(vect4{ 0.0f,0.0f,100.0f });
//Camera* camera = new Camera(vect4{ 100.0f,100.0f,50.0f });

int width = 800, height = 800;
const float l = 1.6;
bool perspect = false, firstMouse = true, mouseLeftDown = false;
float val = 0;
vec3 cv = { 300,600,150 };
float lastX = 800;
float lastY = 800;
const unsigned int cubeH = 300;
float xfactor = width / 8.0f;
float yfactor = height / 8.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Model* model;

void processKeyboard(unsigned char key, int x, int y);
void processMouse(int xpos, int ypos);
void mouseMotionCB(int xpos, int ypos);
void mouseCB(int button, int state, int xpos, int ypos);
void drawModel();
void myinit(int argc, char** argv);

void reshape(int w, int h);
void display();


void cube(vect4& v0, vect4& v1, vect4& v2, vect4& v3, vect4& v4, vect4& v5, vect4& v6, vect4& v7, const vec3& color, bool perspective);
void getProjection(vect4& v, bool perspective);
void rotateCube(vect4& v0, vect4& v1, vect4& v2, vect4& v3, vect4& v4, vect4& v5, vect4& v6, vect4& v7, const vec3& color, bool perspective);
void draw();





void cube(vect4& v0, vect4& v1, vect4& v2, vect4& v3, vect4& v4, vect4& v5, vect4& v6, vect4& v7, const vec3& color, bool perspective) {
    getProjection(v0, perspective);
    getProjection(v1, perspective);
    getProjection(v2, perspective);
    getProjection(v3, perspective);
    getProjection(v4, perspective);
    getProjection(v5, perspective);
    getProjection(v6, perspective);
    getProjection(v7, perspective);


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

void getProjection(vect4& v, bool perspective) {
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

void rotateCube(vect4& v0, vect4& v1, vect4& v2, vect4& v3, vect4& v4, vect4& v5, vect4& v6, vect4& v7, const vec3& color, bool perspective) {
    vect4 camera;
    vect4 v = { 300,600,80 };
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

    vect4 t = { -450,-450,150 };
    vect4 r = { 450,450,-150 };

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



    vect4 normal0 = GetNormal(v0, v1, v2);
    vect4 normal1 = GetNormal(v1, v5, v6);
    vect4 normal2 = GetNormal(v4, v0, v3);
    vect4 normal3 = GetNormal(v5, v4, v7);
    vect4 normal4 = GetNormal(v0, v4, v5);
    vect4 normal5 = GetNormal(v3, v2, v7);

    if (dot(camera, normal0) < 0) {
        std::cout << "Not drawn0" << std::endl;
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
    //fillTriangle(v0, v3, v2, red);
    //fillTriangle(v0, v1, v2, red);
    //fillTriangle(v0, v7, v3, white);
    //fillTriangle(v3, v7, v4, white);
    //fillTriangle(v1, v5, v2, blue);
    //fillTriangle(v5, v6, v2, blue);
    //fillTriangle(v4, v5, v6, green);
    //fillTriangle(v4, v7, v6, green);
    //fillTriangle(v0, v7, v4, color);
    //fillTriangle(v0, v3, v2, color);
    //fillTriangle(v0, v3, v2, color);


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

