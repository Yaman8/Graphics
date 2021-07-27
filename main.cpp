#include<iostream>
#include"includes.h"


int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Project");

    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutDisplayFunc(draw);
    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    draw();

    glFlush();
    glutSwapBuffers();
}

void draw() {

    /*triangle(vec2i{ 100,100 }, vec2i{ 100,500 }, vec2i{ 500, 100 }, col1);
    triangle(vec2i{ 100,500 }, vec2i{ 500,100 }, vec2i{ 500, 500 }, col2);*/

    vec3 v0 = { 300,600,0 };
    vec3 v1 = { 600,600,0 };
    vec3 v2 = { 600,300,0 };
    vec3 v3 = { 300,300,0 };
    vec3 v4 = { 300,600,-300 };
    vec3 v5 = { 600,600,-300 };
    vec3 v6 = { 600,300,-300 };
    vec3 v7 = { 300,300,-300 };
    //cube(v0,v1,v2,v3,v4,v5,v6,v7,col1,perspective);
    rotateCube(v0, v1, v2, v3, v4, v5, v6, v7, red, perspective);
}

void reshape(int w, int h) {
    width = w;
    height = h;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

