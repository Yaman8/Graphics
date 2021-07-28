#pragma once
#include"math.h"
#include"transform.h"

enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

float deg_to_rad(float degree) {
    return (degree * 3.14 / 180);
}

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 45.0f;

mat4f lookAt(vec3 eye, vec3 target, vec3 vUp);

class Camera {
private:
	void updateCameraVectors();
public:
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    Camera(vec3 position = vec3{ 0.0f, 0.0f, 0.0f }, vec3 up = vec3{ 0.0f, 1.0f, 0.0f }, float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    mat4f getViewMatrix();

    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);

};

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch) : Front(vec3{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    std::cout << "Hello Camera 1\n";
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(vec3{ 0.0f, 0.0f, -1.0f }), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    std::cout << "Hello Camera 2\n";

    Position = vec3{ posX, posY, posZ };
    WorldUp = vec3{ upX, upY, upZ };
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

mat4f Camera::getViewMatrix()
{
    return lookAt(Position, Position + Front, Up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{

    float velocity = MovementSpeed * deltaTime;
    vec3 temp1 = Up * velocity;
    vec3 temp2 = Right * velocity;
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
    vec3 front;
    front.x = cos(deg_to_rad(Yaw)) * cos(deg_to_rad(Pitch));
    front.y = sin(deg_to_rad(Pitch));
    front.z = sin(deg_to_rad(Yaw)) * cos(deg_to_rad(Pitch));
    Front = normalize(front);

    vec3 temp1 = cross(Front,WorldUp);
    Right = normalize(temp1);
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    vec3 temp2 = cross(Right,Front);
    Up = normalize(temp2);
}

//-------------------------------- lookAt matrix ---------------------------------------------------
mat4f lookAt(vec3 eye, vec3 target, vec3 vUp = { 0, 1, 0 })
{
    // Calculate new forward direction
    vec3 temp = eye - target;
    vec3 forward = normalize(temp);
    temp = cross(vUp, target);
    vec3 left = normalize(temp);
    // Calculate new Up direction
    vec3 up = cross(forward,left);

    mat4f view = { {{left.x, left.y, left.z, -dot(left, eye)},
                   {up.x, up.y, up.z, -dot(up, eye)},
                   {forward.x, forward.y, forward.z, -dot(forward, eye)},
                   {0, 0, 0, 1}} };
    // Construct Dimensioning and Translation Matrix
    return view;
}