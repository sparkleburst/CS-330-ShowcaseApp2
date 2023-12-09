#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mesh.h>
#include <shader.h>
#include <camera.h>
#include <texture.h>
#include "game_object.h"

class Application {
public:
	Application(std::string windowTitle, int width, int height);
	void Run();

private:
	//these are private functions so will start with lowercase for readability
	bool openWindow();
    void setupInputs();

    void setupScene();
    void update(float deltaTime);
    void draw();

    void handleInput(float deltaTime);
    void mousePositionCallBack(double xpos, double ypos);

private:
	//to make it clear all private variables will have an underscore
	std::string _applicationName {};
	GLFWwindow* _window { nullptr };

    float _moveSpeed = 5.f;
    Camera _camera;
    std::vector<std::unique_ptr<GameObject>> _objects;

	bool _running{ false };

    bool _firstMouse { false };
    glm::vec2 _lastMousePosition {};
    glm::vec2 _cameraLookSpeed {};

    float _lastFrameTime { -1.f };

    // lighting variables
    float _ambientStrength { 0.1f };
    glm::vec3 _ambientLightColor {1.f, 1.f,1.f};
};