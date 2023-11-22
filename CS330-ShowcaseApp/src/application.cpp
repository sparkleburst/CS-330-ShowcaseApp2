#include <application.h>
#include <iostream>
#include <types.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

// constructor
Application::Application(std::string WindowTitle, int width, int height)
    : _applicationName{std::move( WindowTitle )}, _width{ width }, _height{ height },
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
    setupScene();

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

	    /*
	     * ??? does this need to be here ???
		// makes the background of the main window red
		glClearColor(1.0f, 1.0f, 1.0f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
	     */

        // adding vertices
        // update
        update(deltaTime);

        // draw
        draw();
	}

	glfwTerminate();
}

bool Application::openWindow()
{
	// initialize a window with glfwInit();
	glfwInit();

	// this is so we can be compatible with older versions
	// our version is 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

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
            app->_width = width;
            app->_height = height;

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
        app->_camera.IncrementZoom(yOffset * 2);
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

    auto& bedCube = _meshes.emplace_back(Shapes::cubeVertices, Shapes::cubeElements);

    /*
    // move the cube over
    bedCube.Transform = glm::translate(bedCube.Transform, glm::vec3(1.5f, 0.0f, 0.0f));
     */

    // get to shaders file info
    Path shaderPath = std::filesystem::current_path() / "shaders";
    _shader = Shader(shaderPath / "basic_shader.vert", shaderPath / "basic_shader.frag");

/*
    //this is the pyramid
    auto& pyramid = _meshes.emplace_back(Shapes::pyramidVertices, Shapes::pyramidElements);

    // don't have to call the file twice so no "Path shaderPath ="
    _shader = Shader(shaderPath / "basic_shader.vert", shaderPath / "basic_shader.frag");
*/

    // this is the plane or floor
    auto& catAreaFloor = _meshes.emplace_back(Shapes::planeVertices, Shapes::planeElements);

    catAreaFloor.Transform = glm::translate(catAreaFloor.Transform, glm::vec3(0.f, -0.001f, 0.0f));

    // this is the left side bedCylinder
    auto& leftBedCylinder = _meshes.emplace_back(Shapes::someCylinderVertices, Shapes::someCylinderElements);

    leftBedCylinder.Transform = glm::translate(leftBedCylinder.Transform, glm::vec3(0.5f, 0.2f, 0.0f));
    leftBedCylinder.Transform = glm::rotate(leftBedCylinder.Transform, glm::radians(90.f), glm::vec3(1, 0, 0));

    // this is the right side bedCylinder
    auto& rightBedCylinder = _meshes.emplace_back(Shapes::someCylinderVertices, Shapes::someCylinderElements);

    rightBedCylinder.Transform = glm::translate(rightBedCylinder.Transform, glm::vec3(-0.5f, 0.2f, 0.0f));
    rightBedCylinder.Transform = glm::rotate(rightBedCylinder.Transform, glm::radians(270.f), glm::vec3(1, 0, 0));

    // this is the back side bedCylinder
    auto& backBedCylinder = _meshes.emplace_back(Shapes::someCylinderVertices, Shapes::someCylinderElements);

    backBedCylinder.Transform = glm::translate(backBedCylinder.Transform, glm::vec3(0.f, 0.2f, 0.5f));
    backBedCylinder.Transform = glm::rotate(backBedCylinder.Transform, glm::radians(90.f), glm::vec3(0, 0, 1));

    // this is the front side bedCylinder
    auto& frontBedCylinder = _meshes.emplace_back(Shapes::someCylinderVertices, Shapes::someCylinderElements);

    frontBedCylinder.Transform = glm::translate(frontBedCylinder.Transform, glm::vec3(0.f, 0.2f, -0.5f));
    frontBedCylinder.Transform = glm::rotate(frontBedCylinder.Transform, glm::radians(270.f), glm::vec3(0, 0, 1));
}

bool Application::update(float deltaTime) {
    // poll events needs to be in update at the top of the update loop
    glfwPollEvents();

    handleInput(deltaTime);

    return false;
}

bool Application::draw() {
    // makes the background of the main window lilac
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // camera
    glm::mat4 view = _camera.GetViewMatrix();

    // 75 degree field of view
    glm::mat4 projection = _camera.GetProjectionMatrix();

    // bind shaders before drawing meshes
    _shader.Bind();

    _shader.SetMat4("projection", projection);
    _shader.SetMat4("view", view);



    for (auto& mesh : _meshes) {

        /*
        // rotate objects
        mesh.Transform = glm::rotate(mesh.Transform, glm::radians(0.3f), glm::vec3(1, 1, 1));
        */

        /*
        if (mesh.Type == Cylinder) {
            // Rotate the cylinder
            mesh.Transform = glm::rotate(mesh.Transform, glm::radians(0.f), glm::vec3(1, 1, 1));
        }
        */

        _shader.SetMat4("model", mesh.Transform);
        mesh.Draw();
    }

    glfwSwapBuffers(_window);

    return false;
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








