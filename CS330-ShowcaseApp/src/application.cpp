#include <application.h>
#include <iostream>
#include <types.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <light.h>
#include "cat_area.h"
#include "shapes.h"

// constructor
Application::Application(std::string WindowTitle, int width, int height)
    : _applicationName{std::move( WindowTitle )},
    _camera { width, height, {0.0f, 1.5f, 5.f}, true},
    _cameraLookSpeed {0.15f, 0.15f} // sensitivity of mouse movement
    {}

// run function
void Application::Run() {
	// open the window
	if (!openWindow()) {
		return;
	}

    setupInputs();

	_running = true;

    // set up the scene
    //std::cerr << "it's setup crashing" << std::endl;
    setupScene();
    //std::cerr << "the end setup" << std::endl;

	// run application

	while (_running) {
        float currentTime = glfwGetTime();

        if (_lastFrameTime == -1.f) {
            _lastFrameTime = currentTime;
        }

        auto deltaTime = currentTime - _lastFrameTime;
        _lastFrameTime = currentTime;

		if (glfwWindowShouldClose(_window)) {
			_running = false;
            continue;
		}

        // adding vertices
        // update
        //std::cerr << "it's update crashing" << std::endl;
        update(deltaTime);

        // draw
        //std::cerr << "it's draw crashing" << std::endl;
        draw();
        //std::cerr << "it's end draw" << std::endl;
	}

	glfwTerminate();
}

bool Application::openWindow()
{
	// initialize a window with glfwInit();
	glfwInit();

	// this is so we can be compatible with older versions
	// our version is 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// above is things needed for glfw and glad
	// below - now we open a window

	_window = glfwCreateWindow(800, 600, "MaxsOpenGL", nullptr, nullptr);
	/* (size(x, y), title, (not sure what nullptrs are about yet but using them instead
	   of NULL because NUll is C content while we are using C++) */

	if (!_window) {
		std::cerr << "failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}
	// !window is the same as window == nullptr
	// cerr is console error 

	glfwMakeContextCurrent(_window);

    glfwSetWindowUserPointer(_window, (void*)this);

	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow* window, int width, int height) {
			// this gets called whenever the window is resized
			glViewport(0, 0, width, height);

            auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

            //app->_width = width;
            //app->_height = height;

            app->_camera.SetSize(width, height);
		});

	// below - now we load all the OpenGl functions

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

    // enable depth
    glEnable(GL_DEPTH_TEST);

    // cull back face
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    return true;
}

void Application::setupInputs() {

    // hide the cursor
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback( _window, []
    (GLFWwindow* window, int key, int scancode, int action, int mods){
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

        switch (key) {
            case GLFW_KEY_ESCAPE: {
                if (action == GLFW_PRESS) {
                    app->_running = false;
                }
                break;
            }
            case GLFW_KEY_F11: {
                if (action == GLFW_PRESS) {
                    app->_camera.SetIsPerspective(!app->_camera.IsPerspective());
                }
                break;
            }
            default: {}
        }

    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos) {
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));

//        app->mousePositionCallBack(xpos, ypos);
    });

    glfwSetScrollCallback(_window, [](GLFWwindow* window, double xOffset, double yOffset) {
        // std::cout << "mouse wheel (" << xOffset << ", " << yOffset << ")" << std::endl;
        auto* app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
        // app->_camera.IncrementZoom(yOffset * 2); // makes scroll zoom
        app->_moveSpeed *= pow(1.1, yOffset); // makes scroll speed camera up or down
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {
        switch (button) {
            case GLFW_MOUSE_BUTTON_LEFT: {
                if (action == GLFW_PRESS) {
                    std::cout << "Mouse button left pressed" << std::endl;
                } else {

                }
                break;
            }
            case GLFW_MOUSE_BUTTON_MIDDLE: {
                if (action == GLFW_PRESS) {

                } else {

                }
                break;
            }
            case GLFW_MOUSE_BUTTON_RIGHT: {
                if (action == GLFW_PRESS) {

                } else {

                }
                break;
            }
            default:
                std::cout << "Unhandled mouse button event" << std::endl;
        }
    });
}

void Application::setupScene() {

    // place the objects in catArea.cpp
    // move the light to their positions
    _objects.push_back(std::make_unique<CatArea>());

    auto& light0 = _objects.emplace_back(std::make_unique<Light>());
    light0->Transform = glm::translate(light0->Transform, glm::vec3(-2.f, 1.f, 2.f));

    auto& light1 = _objects.emplace_back(std::make_unique<Light>());
    light1->Transform = glm::translate(light1->Transform, glm::vec3(2.f, 1.f, -2.f));

}

void Application::update(float deltaTime) {
    // poll events needs to be in update at the top of the update loop
    glfwPollEvents();

    // handle all input events
    handleInput(deltaTime);

    // there's only a cat area?
    for (auto& object : _objects) {
        object->Update(deltaTime);
    }
}

void Application::draw() {
    // below makes the background of the main window purple
    glClearColor(0.2f, 0.1f, 0.5f, 1.0f); // purple
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera
    glm::mat4 view = _camera.GetViewMatrix();

    // 75 degree field of view
    glm::mat4 projection = _camera.GetProjectionMatrix();

    SceneParameters sceneParams {
        .ProjectionMatrix = projection,
        .ViewMatrix = view,
        .CameraPosition = _camera.GetPosition()
    };



    for (auto& model : _objects) {
        //std::cerr << "it's crashing" << std::endl;
        model->ProcessLighting(sceneParams);
        //std::cerr << "the end it's crashing" << std::endl;
    }

    // draw all models in the scene
    for (auto& model : _objects) {
        //std::cerr << "it's modelly crashing" << std::endl;
        model->Draw(sceneParams);
        //std::cerr << "the end it's modelly crashing" << std::endl;
    }

    glfwSwapBuffers(_window);


}

void Application::handleInput(float deltaTime) {

    auto moveAmount = _moveSpeed * deltaTime;

    if (glfwGetKey(_window, GLFW_KEY_W)) {
        _camera.MoveCamera(Camera::MoveDirection::Forward, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_A)) {
        _camera.MoveCamera(Camera::MoveDirection::Left, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_S)) {
        _camera.MoveCamera(Camera::MoveDirection::Backward, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_D)) {
        _camera.MoveCamera(Camera::MoveDirection::Right, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_Q)) {
        _camera.MoveCamera(Camera::MoveDirection::Up, moveAmount);
    }
    if (glfwGetKey(_window, GLFW_KEY_E)) {
        _camera.MoveCamera(Camera::MoveDirection::Down, moveAmount);
    }

    double xpos, ypos;
    glfwGetCursorPos(_window, &xpos, &ypos);

    mousePositionCallBack(xpos, ypos);

}

void Application::mousePositionCallBack(double xpos, double ypos) {

    if (!_firstMouse) {
        _lastMousePosition.x = static_cast<float>(xpos);
        _lastMousePosition.y = static_cast<float>(ypos);
        _firstMouse = true;
    }

    glm::vec2 moveAmount {
            xpos - _lastMousePosition.x,
            _lastMousePosition.y - ypos,
    };

    _lastMousePosition.x = 400;
    _lastMousePosition.y = 300;

    glfwSetCursorPos(_window, 400.0, 300.0);

    _camera.RotateBy(moveAmount.x * _cameraLookSpeed.x, moveAmount.y * _cameraLookSpeed.y);
}








