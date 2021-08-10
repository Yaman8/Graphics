#include <GL/glut.h>

#include "transform.h"
#include"Coord.h"
#include"math.h"

mat4f lookAt(vect4 eye, vect4 target, vect4 vUp);

class Camera
{
public:
    Camera();
    void processKeyboard(unsigned char key, float);
    void processMouse(int x, int y);
    mat4f getViewMatrix();

    float zoom;
    float deltaTime;
    vect4 m_pos;
    vect4 m_front;
    vect4 m_up;
    vect4 m_right;
    float m_speed;
    vec2i m_mousePos;
    float yaw, pitch, roll;
};


Camera::Camera()
{
    m_pos = { 0.0f, 10.0f, 20.0f };
    m_front = { 0.0f, 0.0f, 1.0f };
    m_up = { 0.0f, 1.0f, 0.0f };
    m_right = (m_front.crossProduct(m_up)).normalize();
    yaw = 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
    zoom = 20.0f;
    m_speed = 5.0f;
}

void Camera::processKeyboard(unsigned char key, float dt)
{
    float m_velocity = m_speed * dt;
    switch (key)
    {

    case 's':
        m_pos = m_pos + m_up * m_velocity;
        break;

    case 'w':
        m_pos = m_pos.inverse() + m_up * m_velocity;
        break;

    case 'a':
        m_pos = m_pos + m_right * m_velocity;
        break;

    case 'd':
        m_pos = m_pos.inverse() + m_right * m_velocity;
        break;

    case 'r':
        m_pos = m_pos + m_front * m_velocity;
        break;

    case 'f':
        m_pos = m_pos.inverse() + m_front * m_velocity;
        break;

    case 'z':
        zoom += 10 * dt;
        if (zoom > 200.0f)
            zoom = 200.0f;
        break;

    case 'x':
        zoom -= 10 * dt;
        if (zoom < 0.05f)
            zoom = 0.05f;
        break;

    case 'q':
        exit(0);
    }
}

void Camera::processMouse(int xoffset, int yoffset)
{
    float mouseSensitivity = 0.00001f;
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    // pitch = x-axis , yaw = y-axis , roll = z-axis rotation
    if (xoffset > 0 && yoffset < 0)
    {
        yaw -= xoffset;
        pitch += yoffset;
    }

    else if (xoffset < 0 && yoffset > 0)
    {
        yaw += xoffset;
        pitch -= yoffset;
    }

    else
    {
        yaw += xoffset;
        pitch += yoffset;
    }

    // Point front;
    // front.x = cos(radians(yaw)) * cos(radians(pitch));
    // front.y = sin(radians(pitch));
    // front.z = sin(radians(yaw)) * cos(radians(pitch));

    rotateY(m_front, yaw);
    rotateX(m_front, pitch);
    m_front.normalize();
    m_right = m_front.crossProduct(m_up).normalize();
    m_up = m_right.crossProduct(m_front).normalize();
}

mat4f Camera::getViewMatrix()
{
    mat4f view;
    view = lookAt(m_pos, m_pos + m_front, m_up);
    return view;
}

//-------------------------------- lookAt matrix ---------------------------------------------------
mat4f lookAt(vect4 eye, vect4 target, vect4 vUp = { 0, 1, 0 })
{
    // Calculate new forward direction
    vect4 forward = (eye - target).normalize();
    vect4 right = (vUp.crossProduct(forward)).normalize();
    // Point right = vUp.normalize().crossProduct(forward);
    // Calculate new Up direction
    vect4 up = forward.crossProduct(right);
    // Point c = target.inverse();

    mat4f view = { {{right.x, right.y, right.z, -dotProduct(right, eye)},
                   {up.x, up.y, up.z, -dotProduct(up, eye)},
                   {forward.x, forward.y, forward.z, -dotProduct(forward, eye)},
                   {0, 0, 0, 1}} };
    // mat4f view = {{{right.x, up.x, forward.x, 0},
    //                {right.y, up.y, forward.y, 0},
    //                {right.z, up.z, forward.z, 0},
    //                {-dotProduct(right, eye), -dotProduct(up, eye), -dotProduct(forward, eye), 1}}};
    // Construct Dimensioning and Translation Matrix
    return view;
}