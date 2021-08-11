
#include "model.h"

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

void specialKeyboard(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void myinit(int argc, char** argv);