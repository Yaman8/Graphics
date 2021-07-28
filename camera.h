#pragma once

#include"transform.h"
#include"math.h"

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


mat4f lookAt(Point eye, Point target, Point vUp);
// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera
{
public:
    // camera Attributes
    Point Position;
    Point Front;
    Point Up;
    Point Right;
    Point WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    Camera(Point position = Point{ 0.0f, 0.0f, 0.0f }, Point up = Point{ 0.0f, 1.0f, 0.0f }, float yaw = YAW, float pitch = PITCH);
    // constructor with vectors
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    mat4f GetViewMatrix();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};



Camera::Camera(Point position, Point up, float yaw, float pitch) : Front(Point{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    std::cout << "camera";
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Point{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    std::cout << "camera camera";
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

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
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

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch /*= true*/)
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

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    Point front;
    front.x = cos(deg_to_radians(Yaw)) * cos(deg_to_radians(Pitch));
    front.y = sin(deg_to_radians(Pitch));
    front.z = sin(deg_to_radians(Yaw)) * cos(deg_to_radians(Pitch));
    Front = normalize(front);
    // also re-calculate the Right and Up vector
    Right = normalize(cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = normalize(cross(Right, Front));
}

mat4f lookAt(Point eye, Point target, Point vUp = { 0, 1, 0 })
{
    // Calculate new forward direction
    Point temp = eye - target;
    Point forward = normalize(temp);
    temp = cross(vUp,target);
    Point left =normalize(temp);
    // Calculate new Up direction
    Point up = cross(forward,left);

    mat4f view = { {{left.x, left.y, left.z, -dot(left, eye)},
                   {up.x, up.y, up.z, -dot(up, eye)},
                   {forward.x, forward.y, forward.z, -dot(forward, eye)},
                   {0, 0, 0, 1}} };
    // Construct Dimensioning and Translation Matrix
    return view;
}