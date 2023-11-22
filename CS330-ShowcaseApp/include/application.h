#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mesh.h>
#include <shader.h>
#include <camera.h>

class Application {
public:
	Application(std::string windowTitle, int width, int height);

	void Run();
private:
	//these are private functions so will start with lowercase for readability
	bool openWindow();
    void setupInputs();

    void setupScene();
    bool update(float deltaTime);
    bool draw();

    void handleInput(float deltaTime);
    void mousePositionCallBack(double xpos, double ypos);

private:
	//to make it clear all private variables will have an underscore
	std::string _applicationName {};
	int _width {};
	int _height {};
	GLFWwindow* _window { nullptr };

    float _moveSpeed = 5.f;
    Camera _camera;
    std::vector<Mesh> _meshes;
    Shader _shader;
	bool _running{ false };

    bool _firstMouse { false };
    glm::vec2 _lastMousePosition {};
    glm::vec2 _cameraLookSpeed {};

    float _lastFrameTime { -1.f };
};