#pragma once

#include"transform.h"
#include"math.h"

#include <vector>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;

mat4f lookAt(Point eye, Point target, Point vUp);

class Camera
{
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();

public:
    // camera Attributes
    Point Position;
    Point Front;
    Point Up;
    Point Right;
    Point WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(Point position = Point{ 0.0f, 0.0f, 0.0f }, Point up = Point{ 0.0f, 1.0f, 0.0f }, float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    mat4f GetViewMatrix();

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);


};

Camera::Camera(Point position, Point up, float yaw, float pitch) : Front(Point{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    std::cout << "Hello Camera 1\n";
    Position = position;
    
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Point{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    std::cout << "Hello Camera 2\n";

    Position = Point{ posX, posY, posZ };
    WorldUp = Point{ upX, upY, upZ };
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

mat4f Camera::GetViewMatrix()
{
    return lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{

    float velocity = MovementSpeed * deltaTime;
    Point temp1 = Up * velocity;
    Point temp2 = Right * velocity;
    if (direction == FORWARD)
        Position = Position + temp1;
    if (direction == BACKWARD)
        Position = Position - temp1;
    if (direction == LEFT)
        Position = Position - temp2;
    if (direction == RIGHT)
        Position = Position + temp2;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch /*= true*/)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    Point front;
    front.x = cos(deg_to_radians(Yaw)) * cos(deg_to_radians(Pitch));
    front.y = sin(deg_to_radians(Pitch));
    front.z = sin(deg_to_radians(Yaw)) * cos(deg_to_radians(Pitch));
    Front = front.normalize();


    Point temp1 = Front.crossProduct(WorldUp);
    Right = temp1.normalize();
    //std::cout << "Right " << Right.x << " " << Right.y << " " << Right.z;
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Point temp2 = Right.crossProduct(Front);
    Up = temp2.normalize();
}

//-------------------------------- lookAt matrix ---------------------------------------------------
mat4f lookAt(Point eye, Point target, Point vUp = { 0, 1, 0 })
{
    // Calculate new forward direction
    Point temp = eye - target;

    Point forward = temp.normalize();
    temp = vUp.crossProduct(target);
    Point left = temp.normalize();
    // Calculate new Up direction
    Point up = forward.crossProduct(left);

    mat4f view = { {{left.x, left.y, left.z, -dotProduct(left, eye)},
                   {up.x, up.y, up.z, -dotProduct(up, eye)},
                   {forward.x, forward.y, forward.z, -dotProduct(forward, eye)},
                   {0, 0, 0, 1}} };
    //std::cout << "l " << left.x << " " << left.y << " " << left.z << std::endl;
    //std::cout << "u " << up.x << " " << up.y << " " << up.z << std::endl;
    //std::cout << "f " << forward.x << " " << forward.y << " " << forward.z << std::endl;
    float one = dotProduct(left, eye);
    float two = -dotProduct(up, eye);
    float three = -dotProduct(forward, eye);
/*    std::cout << one << std::end;
    std::cout << two << std::end;
    std::cout << three << std::end*/;
    // Construct Dimensioning and Translation Matrix
    return view;
}