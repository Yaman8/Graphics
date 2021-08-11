

#include "model.h"


// std::vector<Triangle> model = load("../resources/models/cube.obj");
// //final drawing model initialized
// std::vector<Triangle> final_model = {Triangle{0}};

// //for camera
// Camera camera = Camera(Point{0.0f, 0.0f, 3.0f});
// bool firstMouse = true;
// bool mouseLeftDown = false;
// // int fps = 60;

// //for model
// Model *model;

// float lastX = SCR_WIDTH / 2;
// float lastY = SCR_HEIGHT / 2;

// //movement speed
// float deltaTime = 0.0f;
// float lastFrame = 0.0f;

float lastX = 800;
float lastY = 800;
bool mouseLeftDown = false;

Camera* camera;
Model* model;

// bool firstMouse = true;
// bool mouseLeftDown = false;

float deltaTime = 0.0f;

void drawModel();

void processKeys(unsigned char key, float x, float y);
void processMouse(int xpos, int ypos);
void updateFunction(int val);

void processArrows(unsigned char key, int x, int y)
{

}

// void processKeys(unsigned char key, int x, int y)
// {
//     std::cout << "Key Pressed" << std::endl;

//     if (key == 27)
//     {
//         glutDestroyWindow(0);
//         exit(0);
//     }
//     if (key == 's')
//         camera->processKeyboard(FORWARD, deltaTime);
//     if (key == 'w')
//         camera->processKeyboard(BACKWARD, deltaTime);
//     if (key == 'd')
//         camera->processKeyboard(LEFT, deltaTime);
//     if (key == 'a')
//         camera->processKeyboard(RIGHT, deltaTime);
//     if (key == 'z')
//         camera->processKeyboard(ZOOMIN, deltaTime);
//     if (key == 'x')
//         camera->processKeyboard(ZOOMOUT, deltaTime);
//     glutPostRedisplay();
// }

void specialKeyboard(int key, int x, int y)
{
    std::cout << "Key Pressed" << std::endl;

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
    glutPostRedisplay(); //Window redraw
}

void keyboard(unsigned char key, int x, int y)
{
    std::cout << "Key Pressed" << std::endl;

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
    case 27: //ESC key
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay(); //Window redraw
}


void myinit(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT); //sets the width and height of the window in pixels
    glutInitWindowPosition(0, 0);              //sets the position of the window in pixels from top left corner
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //creates a single frame buffer of RGB color capacity.
    glutCreateWindow("Rani Pokhari");

    glClearColor(0.1, 0.1, 0.1, 0.0);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    // glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCR_WIDTH, 0, SCR_HEIGHT);

    // glutPostRedisplay();
}

void draw_model()
{
    static float lastFrame = 0;
    float currentFrame = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (currentFrame - lastFrame) / 10;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT);

    mat4f view = camera->getViewMatrix();
    mat4f projection = newPerspective(90.0f, (float)SCR_HEIGHT / SCR_WIDTH);

    // mat4f perspec = perspectiveMatrix();


    // mat4f view_projection = mul(perspec, view);

    // model->applyTransform(view, projection);
    model->applyTransform(view, projection);
    model->draw();

    //-------------- always put this here----------------------------
    glutSwapBuffers();
    glFlush(); // flushes the frame buffer to the screen

    // glutPostRedisplay();
    updateFunction(0);

}

void updateFunction(int val)
{
    int fps = 60;
    glutPostRedisplay();
    glutTimerFunc(1000 / fps, updateFunction, 0);
}

int main(int argc, char** argv)
{
    myinit(argc, argv);

    camera = new Camera();
    model = new Model;

    // model->load("../resources/models/videoship.obj");
    model->newLoad("../obj/zahaf1.obj");

    model->camera = camera;
    model->convertToScreen_model();

    model->scale_model(0.15);
    model->translate_model({ SCR_WIDTH / 2, SCR_HEIGHT / 2, 0 });


    glutDisplayFunc(draw_model);

    glutSpecialFunc(specialKeyboard);
    glutKeyboardFunc(keyboard);
    // glutMotionFunc(processMouse);

    // glutMouseFunc(mouseCB);
    // glutMotionFunc(mouseMotionCB);

    glutMainLoop(); //loops the current event
}