
#include"includes.h"

int main(int argc, char** argv)
{
    myinit(argc, argv);

    camera = new Camera();
    model = new Model;

    //model->Load("../obj/cube.obj");
    //model->camera = camera;
    //model->modelToScreen();
    //model->scale_model(0.5);
    //model->translate_model({ SWIDTH / 2, SHEIGHT / 2, 0 });

    model->Load("../obj/zahaf1.obj");
    model->camera = camera;
    model->modelToScreen();
    model->scale_model(0.15);
    model->translate_model({ SWIDTH / 2, SHEIGHT / 2, 0 });


    glutDisplayFunc(drawModel);

    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    // glutMotionFunc(processMouse);

    // glutMouseFunc(mouseCB);
    // glutMotionFunc(mouseMotionCB);

    glutMainLoop();
}


void myinit(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Heydar Aliyev");

    glClearColor(0.39, 0.6, 0.69, 0.0);
    glViewport(0, 0, SWIDTH, SHEIGHT);
    glLoadIdentity();
    gluOrtho2D(0, SWIDTH, 0, SHEIGHT);
}

void drawModel()
{
    static float lastFrame = 0;
    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentFrame - lastFrame) / 10;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    mat4f view = camera->getViewMatrix();
    mat4f projection = Perspective(90.0f, (float)SHEIGHT / SWIDTH);

    model->transformModel(view, projection);
    model->draw();

    glutSwapBuffers();
    glFlush();

    updateFunction(0);

}

void updateFunction(int val)
{
    int fps = 60;
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, updateFunction, 0);
}


void specialKeyboard(int key, int x, int y)
{
    //std::cout << "Key Pressed" << std::endl;

    switch (key)
    {
    case GLUT_KEY_UP:
        camera->processKeyboard(Camera_Movement::UP, deltaTime);
        break;
    case GLUT_KEY_DOWN:
        camera->processKeyboard(Camera_Movement::DOWN, deltaTime);
        break;
    case GLUT_KEY_LEFT:
        camera->processKeyboard(Camera_Movement::LEFT, deltaTime);
        break;
    case GLUT_KEY_RIGHT:
        camera->processKeyboard(Camera_Movement::RIGHT, deltaTime);
        break;
    default:
        break;
    }
    glutPostRedisplay(); 
}

void keyboard(unsigned char key, int x, int y)
{
    //std::cout << "Key Pressed" << std::endl;

    switch (key)
    {
    case 'W':
        camera->processKeyboard(Camera_Movement::WKEY, deltaTime);
        break;
    case 'S':
        camera->processKeyboard(Camera_Movement::SKEY, deltaTime);
        break;
    case 'A':
        camera->processKeyboard(Camera_Movement::AKEY, deltaTime);
        break;
    case 'D':
        camera->processKeyboard(Camera_Movement::DKEY, deltaTime);
        break;
    case 27: 
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay(); 
}


