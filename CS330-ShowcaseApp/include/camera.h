//
// Created by maxan on 11/21/2023.
//

#pragma once

#include <glm/glm.hpp>

class Camera {

public:
    enum class MoveDirection {
        Forward,
        Backward,
        Left,
        Right,
        Up,
        Down
    };

    // constructor
    explicit Camera(int width, int height, glm::vec3 initialPosition = glm::vec3 {}, bool _isPerspective = true);

    glm::mat4 GetViewMatrix();
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const;
    glm::vec3 GetPosition() const { return _position; }

    [[nodiscard]] bool IsPerspective() const { return _isPerspective; }
    void SetIsPerspective(bool isPerspective) { _isPerspective = isPerspective; }
    void SetSize(int width, int height) {
        _width = width;
        _height = height;
    }

    void MoveCamera(MoveDirection direction, float moveAmount);
    void RotateBy(float yaw, float pitch);
    void IncrementZoom(float amount);

private:
    void recalculateVectors();
private:
    bool _isPerspective { true };
    // if not perspective then it will be orthographic

    glm::vec3 _position {};
    glm::vec3 _lookDirection {};
    glm::vec3 _upDirection {0.f, 1.f, 0.f};

    float _yaw { -90.f }; // yaw is left-right movement
    float _pitch {};      // pitch is up-down movement

    float _fieldOfView { 75.f };
    int _width { 0 };
    int _height { 0 };
    float _nearClip { 0.01f }; // how close objects can be before it cuts stuff off
    float _farClip { 100.f }; // how far away objects can be before it cuts stuff off
    float _orthoNearClip { 1.1f }; // how close objects can be before it cuts stuff off
    float _orthoFarClip { 1000.f }; // how far away objects can be before it cuts stuff off
};



