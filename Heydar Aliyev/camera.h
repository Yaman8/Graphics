#pragma once

#include "Coord.h"
#include "matrix.h"

mat4f calculateLookAt(vect4& pos, vect4& target, vect4& up);

enum Camera_Movement {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    WKEY,
    AKEY,
    SKEY,
    DKEY,
};

class Camera
{
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

public:
    // camera Attributes
    float zoom;
    float deltaTime;
    vect4 Position;
    vect4 Front;
    vect4 Target;
    vect4 Up;
    vect4 Right;
    float Speed;
    vec2i  MousePos;
    float yaw, pitch, roll;
    float thetaX, thetaY, thetaZ;

    Camera();
    mat4f getViewMatrix();
    void processKeyboard(Camera_Movement direction, float deltaTime);
};

Camera::Camera()
{
    thetaX = 0.0;
    thetaY = 0.0;
    thetaZ = 0.0;
    Position = { 0.0f, 0.0f, -100.0f };
    Target = { 0.0f, 0.0f, 1.0f };
    Front = { 0.0f, 0.0f, 1.0f };
    Up = { 0.0f, 1.0f, 0.0f };
    // m_right = maths::normalize(maths::cross(m_front, m_up));
    yaw = 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
    zoom = 20.0f;
    Speed = 5.0f;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    vect4 vForward = Front * (2.0f * deltaTime);
    if (direction == Camera_Movement::UP)
        Position.y += 1.0f * deltaTime;
    if (direction == Camera_Movement::DOWN)
        Position.y -= 1.0f * deltaTime;
    if (direction == Camera_Movement::LEFT)
        Position.x -= 1.0f * deltaTime;
    if (direction == Camera_Movement::RIGHT)
        Position.x += 1.0f * deltaTime;

    if (direction == Camera_Movement::WKEY)
        Position = Position + vForward;
    if (direction == Camera_Movement::SKEY)
        Position = Position - vForward;
    if (direction == Camera_Movement::AKEY)
        yaw -= 0.1f * deltaTime;
    if (direction == Camera_Movement::DKEY)
        yaw += 0.1f * deltaTime;
}

mat4f Camera::getViewMatrix()
{
    Target = { 0.0f, 0.0f, 1.0f };
    Up = { 0.0f, 1.0f, 0.0f };
    // return lookAt(Position, Position + Front, Up);
    mat4f matCameraRot = Matrix_MakeRotationY(yaw);
    Front = mul(matCameraRot, Target);

    Target = Position + Front;

    // mat4f matCamera = Matrix_vect4At(Position, Target, Up);

    // // Make view matrix from camera
    // return Matrix_QuickInverse(matCamera);
    return calculateLookAt(Position, Target, Up);
}

mat4f calculateLookAt(vect4& pos, vect4& target, vect4& up)
{
    // Calculate new forward direction
    vect4 newForward = target - pos;
    newForward = newForward.normalize();

    // Calculate new Up direction
    vect4 a = newForward * dotProduct(up, newForward);
    vect4 newUp = up - a;
    newUp = newUp.normalize();

    // New Right direction is easy, its just cross product
    vect4 newRight = newUp.crossProduct(newForward);

    mat4f lookAt = mul(RotView(newRight, newUp, newForward), TranslateView(pos));
    return lookAt;
}
