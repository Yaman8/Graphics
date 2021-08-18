#pragma once

#include "Coord.h"
#include "matrixFunc.h"

mat4f calculateLookAt(vect4& pos, vect4& target, vect4& up);

enum Camera_Movement
{
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
    vec2i MousePos;
    float yaw, pitch, roll;

    Camera();
    mat4f getViewMatrix();
    void processKeyboard(Camera_Movement direction, float deltaTime);
};

Camera::Camera()
{
    Position = { 0.0f, 0.0f, 100.0f };
    Target = { 0.0f, 0.0f, 1.0f };
    Front = { 0.0f, 0.0f, 1.0f };
    Up = { 0.0f, 1.0f, 0.0f };
    // Right = Front.crossProduct(Up).normalize();
    yaw = 0.0f;
    pitch = 0.0f;
    roll = 0.0f;
    zoom = 20.0f;
    Speed = 1.0f;
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
{
    vect4 vForward = Front * (0.002f * deltaTime);
    if (direction == Camera_Movement::UP)
        Position.y += 0.1f * deltaTime;
    if (direction == Camera_Movement::DOWN)
        Position.y -= 0.1f * deltaTime;
    if (direction == Camera_Movement::LEFT)
        Position.x -= 0.1f * deltaTime;
    if (direction == Camera_Movement::RIGHT)
        Position.x += 0.1f * deltaTime;

    if (direction == Camera_Movement::WKEY)
        Position = Position + vForward;
    if (direction == Camera_Movement::SKEY)
        Position = Position - vForward;
    if (direction == Camera_Movement::AKEY)
        yaw -= 0.01f * deltaTime;
    if (direction == Camera_Movement::DKEY)
        yaw += 0.01f * deltaTime;

    std::cout << Position << std::endl;
}

// void Camera::processKeyboard(Camera_Movement direction, float deltaTime)
// {
//     float velocity = Speed * deltaTime;
//     if (direction == Camera_Movement::UP)
//         Position = Position - Up * velocity;
//     if (direction == Camera_Movement::DOWN)
//         Position = Position + Up * velocity;
//     if (direction == Camera_Movement::LEFT)
//         Position = Position + Right * velocity;
//     if (direction == Camera_Movement::RIGHT)
//         Position = Position - Right * velocity;

//     // if (direction == Camera_Movement::WKEY)
//     //     Position = Position + vForward;
//     // if (direction == Camera_Movement::SKEY)
//     //     Position = Position - vForward;
//     // if (direction == Camera_Movement::AKEY)
//     //     yaw -= 0.01f * deltaTime;
//     // if (direction == Camera_Movement::DKEY)
//     //     yaw += 0.01f * deltaTime;

//     std::cout << Position << std::endl;
// }

// mat4f Camera::getViewMatrix()
// {
//     //Look At Matrix
//     Point eye = Position;
//     Point target = Position + Front;

//     Point forward = (eye - target).normalize();
//     Point right = (Up.crossProduct(forward)).normalize();
//     Point up = (forward.crossProduct(right)).normalize();

//     mat4f view = {{{right.x, right.y, right.z, -dotProduct(right, eye)},
//                    {up.x, up.y, up.z, -dotProduct(up, eye)},
//                    {forward.x, forward.y, forward.z, -dotProduct(forward, eye)},
//                    {0, 0, 0, 1}}};

//     return view;
// }

mat4f Camera::getViewMatrix()
{
    // return lookAt(Position, Position + Front, Up);
    // mat4f objToOrigin = {{{1.0f,0.0f,0.0f,-SCR_WIDTH/2.0f},
    //                         {0.0f,1.0f,0.0f,-SCR_HEIGHT/2.0f},
    //                         {0.0f,0.0f,1.0f,-CUBE_HEIGHT/2.0f},
    //                         {0.0f,0.0f,0.0f,1.0f}}};
    // mat4f objToOriginal = {{{1.0f, 0.0f, 0.0f, SCR_WIDTH / 2.0f},
    //                        {0.0f, 1.0f, 0.0f, SCR_HEIGHT / 2.0f},
    //                        {0.0f, 0.0f, 1.0f, CUBE_HEIGHT / 2.0f},
    //                        {0.0f, 0.0f, 0.0f, 1.0f}}};

    // mat4f matCameraRot = mul(objToOriginal,mul(Matrix_MakeRotationY(yaw),objToOrigin));

    mat4f matCameraRot = Matrix_MakeRotationY(yaw);
    Front = mul(matCameraRot, Target);

    Target = Position + Front;

    // mat4f matCamera = Matrix_PointAt(Position, Target, Up);

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