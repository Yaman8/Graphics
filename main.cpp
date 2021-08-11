#include<iostream>
#include"includes.h"

int main(int argc, char** argv) {

    myinit(argc, argv);

    //model = new Model;
    //model->newLoad("obj/Temple.obj");
    //model->camera = camera;
    //model->convertToScreen_model();
    //model->scale_model(0.1);
    //model->translate_model({ (wid /4),hei / 4,0 });

    model = new Model;
    model->newLoad("obj/zahaf1.obj");
    model->camera = camera;
    model->convertToScreen_model();
    model->scale_model(0.1);
    //model->rotate_model(90);
    model->translate_model({ (wid /4),hei/4,0 });

    glutKeyboardFunc(processKeyboard);
    glutPassiveMotionFunc(processMouse);
    glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    //glutReshapeFunc(reshape);
    //glutIdleFunc(display);
    glutDisplayFunc(drawModel);
    glutMainLoop();

    return 0;
}

//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glLoadIdentity();
//
//    draw();
//    //ob();
//
//    glFlush();
//    glutSwapBuffers();
//}

void myinit(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(width, height); //sets the width and height of the window in pixels
    glutInitWindowPosition(0, 0);              //sets the position of the window in pixels from top left corner
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //creates a single frame buffer of RGB color capacity.
    glutCreateWindow("Project");

    glClearColor(0.39, 0.6, 0.69, 0.0);
    glViewport(0, 0, width, height);
    // glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

void updateFunction(int val) {
    int fps = 60;
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, updateFunction, 0);
}

void mouseMotionCB(int xpos, int ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void mouseCB(int button, int state, int xpos, int ypos) {
    if ((button == GLUT_LEFT_BUTTON))
    {
        if (state == GLUT_DOWN)
        {

            mouseLeftDown = true;
        }
        else
        {
            mouseLeftDown = false;
        }
    }
}

void drawModel() {
    static float lastFrame = 0;
    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentFrame - lastFrame) / 1000;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    mat4f view = camera->GetViewMatrix();
    mat4f projection = newPerspective(camera->Zoom,(float)width/height);


    model->applyTransform(view,projection);
    model->draw();

    glutSwapBuffers();
    glFlush();

    // glutPostRedisplay();
    updateFunction(0);
}


//void reshape(int w, int h) {
//    width = w;
//    height = h;
//
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, width, 0.0, height);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glutPostRedisplay();
//}

void processMouse(int xpos, int ypos)
{
    static float lastX = 800;
    static float lastY = 800;
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xoffset, yoffset);
}

void processKeyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        glutDestroyWindow(0);
        exit(0);
    }
    if (key == 's')
        camera->processKeyboard(FORWARD, deltaTime);
    if (key == 'w')
        camera->processKeyboard(BACKWARD, deltaTime);
    if (key == 'd')
        camera->processKeyboard(LEFT, deltaTime);
    if (key == 'a')
        camera->processKeyboard(RIGHT, deltaTime);
    if (key == 'z')
        camera->processKeyboard(ZOOMIN, deltaTime);
    if (key == 'x')
        camera->processKeyboard(ZOOMOUT, deltaTime);
    glutPostRedisplay();
}