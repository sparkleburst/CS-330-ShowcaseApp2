//
// Created by maxan on 11/21/2023.
//

#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(int width, int height, glm::vec3 initialPosition, bool isPerspective)
    : _isPerspective { isPerspective },
    _position { initialPosition }, _lookDirection{ 0.f, 0.2f, 1.f},
    _width { width }, _height { height } {

    recalculateVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(_position, _position + _lookDirection, _upDirection);
}

glm::mat4 Camera::GetProjectionMatrix() const {

    if (_isPerspective) {
        return glm::perspective(glm::radians(_fieldOfView),
                                (float)_width / (float)_height,_nearClip,
                                _farClip);
    }

    // else returns the orthographic matrix
    return glm::ortho(-static_cast<float>(_width) / _fieldOfView, static_cast<float>(_width) / _fieldOfView,
                      -static_cast<float>(_height) / _fieldOfView, static_cast<float>(_height) / _fieldOfView,
                      _orthoNearClip, _orthoFarClip);
}


void Camera::MoveCamera(MoveDirection direction, float moveAmount)
{
    glm::vec3 moveDirection {};

    switch (direction) {
        case MoveDirection::Forward: {
            moveDirection = _lookDirection;
            break;
        }
        case MoveDirection::Backward: {
            moveDirection = -_lookDirection;
            break;
        }
        case MoveDirection::Left: {
            moveDirection = -glm::normalize(glm::cross(_lookDirection, _upDirection));
            break;
        }
        case MoveDirection::Right: {
            moveDirection = glm::normalize(glm::cross(_lookDirection, _upDirection));
            break;
        }
    }

    _position += moveDirection * moveAmount;
}

void Camera::RotateBy(float yaw, float pitch) {
    _yaw += yaw;
    _pitch += pitch;

    _pitch = std::clamp(_pitch, -89.f, 89.f);

    recalculateVectors();
}

void Camera::recalculateVectors() {
    _lookDirection = glm::normalize(
            glm::vec3 {
                std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch)),
                std::sin(glm::radians(_pitch)),
                std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch))
            }
    );

    auto rightDirection = glm::normalize(glm::cross(_lookDirection,glm::vec3(0.f, 1.f, 0.f)));

    _upDirection = glm::normalize(glm::cross(rightDirection, _lookDirection));
}

void Camera::IncrementZoom(float amount) {
    _fieldOfView -= amount;

    _fieldOfView = std::clamp(_fieldOfView, 5.f, 100.f);
}