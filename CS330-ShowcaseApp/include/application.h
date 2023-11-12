#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mesh.h>
#include <shader.h>

class Application {
public:
	Application(std::string windowTitle, int width, int height);

	void Run();
private:
	//these are private functions so will start with lowercase for readability
	bool openWindow();

    void setupScene();
    bool update();
    bool draw();

private:
	//to make it clear all private variables will have an underscore
	std::string _applicationName {};
	int _width {};
	int _height {};
	GLFWwindow* _window { nullptr };

    std::vector<Mesh> _meshes;
    Shader _shader;

	bool _running{ false };
};