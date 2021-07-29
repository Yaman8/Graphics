#include<iostream>
#include"includes.h"

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Project");


    //glutKeyboardFunc(processKeys);
    //glutMotionFunc(processMouse);
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
    //ob();

    glFlush();
    glutSwapBuffers();
}


void draw() {
    mat4f mat = { {{1, 2, 3, 4},{2, 3, 4, 5},{1, 3, 2, 4},{ 1, 3, 2, 2}} };
    mat4f val = mul(mat, mat);

    mat4f view = camera.GetViewMatrix();
    mat4f perspec = perspectiveMatrix();
    mat4f view_projection = mul(perspec, view);

    std::vector<Triangle> model = load("videoship.obj");

    applyTransform(view_projection, model);

    convertToScreen_model(model);
    translate_model(model, { wid / 4, hei / 4, 0, 0 }); // translate the cube back to its original position
    //scale_model(model, {0.25, 0.25, 0.25});
    drawWireframe_model(model);
    //draw_model(model);


    //mat4f view = camera.GetViewMatrix();
    //mat4f perspec = perspectiveMatrix();


    //mat4f view_projection = mul(perspec, view);
    ////for (int i = 0; i < 4; i++) {
    ////    for (int j = 0; j < 4; j++) {
    ////        std::cout << "viewp" << "[" << i << "]" << "[" << j << "]" << view_projection.matrix4[i][j] << std::endl;
    ////    }
    ////}

    //std::vector<Triangle> model = load("videoship.obj");

    //applyTransform(view_projection, model);
    //for (int i = 0; i < model.size(); i++)
    //{
    //    for (int j = 0; j < 3; j++)
    //    {
    //        //std::cout << "inside";
    //        model[i].vertices[j] = model[i].vertices[j].Convert_to_Screen(model[i].vertices[j]);
    //        //std::cout << model[i].vertices[0];
    //        //std::cout << model[i].vertices[1];
    //        //std::cout << model[i].vertices[2];
    //        transate_polygon(model[i].vertices[j], { wid , hei / 1.5, 0, 0 }); // translate the cube back to its original position
    //        scale_polygon(model[i].vertices[j], { 0.3,0.3,0.3 });
    //    }
    //    wireFrame(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], white);
    //    //fillTriangle(model[i].vertices[0], model[i].vertices[1], model[i].vertices[2], red);

    //}



    //Point v0 = { 300,600,0 };
    //Point v1 = { 600,600,0 };
    //Point v2 = { 600,300,0 };
    //Point v3 = { 300,300,0 };
    //Point v4 = { 300,600,-300 };
    //Point v5 = { 600,600,-300 };
    //Point v6 = { 600,300,-300 };
    //Point v7 = { 300,300,-300 };
    ////cube(v0,v1,v2,v3,v4,v5,v6,v7,col1,perspective);
    //rotateCube(v0, v1, v2, v3, v4, v5, v6, v7, red, perspect);
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
//
//void processMouse(int xpos, int ypos)
//{
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void processKeys(unsigned char key, int x, int y)
//{
//    // const float dt = 1.0f / 60; //fps
//    // switch (key)
//    // {
//    // case 27:
//    //     glutDestroyWindow(0);
//    //     exit(0);
//    // case 120:
//    //     theta_x += wrap_angle(deltaTime * dTheta * dt);
//    // case 121:
//    //     theta_y += wrap_angle(deltaTime * dTheta * dt);
//    // case 122:
//    //     theta_z += wrap_angle(deltaTime * dTheta * dt);
//
//    // }
//    std::cout << "Key Pressed" << std::endl;
//    static float lastFrame = 0;
//    static float deltaTime = 0;
//    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
//    deltaTime = (currentFrame - lastFrame) / 1000;
//    lastFrame = currentFrame;
//    if (key == 27)
//    {
//        glutDestroyWindow(0);
//        exit(0);
//    }
//    if (key == 's')
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (key == 'w')
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (key == 'd')
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (key == 'a')
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//    glutPostRedisplay();
//}