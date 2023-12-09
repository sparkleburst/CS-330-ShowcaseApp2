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
/*
    // this is the pyramid
    auto& pyramid = _meshes.emplace_back(Shapes::pyramidVertices, Shapes::pyramidElements,
                                         glm::vec3(0.5f, 0.5f, 0.5f));

    // this is the cat bed base rectangle (square atm)
    auto& bedCube = _meshes.emplace_back(Shapes::cubeVertices, Shapes::cubeElements);

    // move the cube over
    // bedCube.Transform = glm::translate(bedCube.Transform, glm::vec3(1.5f, 0.0f, 0.0f));

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

    // this is a ball
    auto& aBall = _meshes.emplace_back(Shapes::someSphereVertices, Shapes::someSphereIndices);
    aBall.Transform = glm::translate(aBall.Transform, glm::vec3(1.5f, 0.4f, 1.5f));

    // get to shaders file info
    Path shaderPath = std::filesystem::current_path() / "assets" / "shaders";
    _basicLitShader = Shader(shaderPath / "basic_lit.vert", shaderPath / "basic_lit.frag");

    auto texturePath = std::filesystem::current_path() / "assets" / "textures";
    _textures.emplace_back(texturePath / "grey_fur.jpg");  // cube
    _textures.emplace_back(texturePath / "wood_planks.jpg");    // plane
    _textures.emplace_back(texturePath / "reddish_fluff.png");  // cylinder
    _textures.emplace_back(texturePath / "reddish_fluff.png");  // cylinder
    _textures.emplace_back(texturePath / "reddish_fluff.png");  // cylinder
    _textures.emplace_back(texturePath / "reddish_fluff.png");  // cylinder
    _textures.emplace_back(texturePath / "rain_on_glass.jpg");  //
*/

    // check week 6 from 32:46
    _objects.push_back(std::make_unique<CatArea>());
    auto &light = _objects.emplace_back(std::make_unique<Light>());

    light->Transform = glm::translate(light->Transform, glm::vec3(1.f, 1.f, 1.f));
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
        .ViewMatrix = view
    };



    for (auto& model : _objects) {
        model->ProcessLighting(sceneParams);
    }

    // draw all models in the scene
    for (auto& model : _objects) {
        model->Draw(sceneParams);
    }

    glfwSwapBuffers(_window);

    /*

    // bind shaders before drawing meshes
    _basicLitShader.Bind();
    _basicLitShader.SetMat4("projection", projection);
    _basicLitShader.SetMat4("view", view);

    // for each texture do below
    _basicLitShader.SetInt("tex0", 0);
    _basicLitShader.SetInt("tex1", 1);
    _basicLitShader.SetInt("tex2", 2);
    _basicLitShader.SetInt("tex3", 3);

    // adding textures
    // glActiveTexture(GL_TEXTURE0);
    // bind textures after binding shaders but before drawing the mesh
    // glBindTexture(GL_TEXTURE_2D, _woodFloorTexture);


    // for when you want to do multiple textures
    for (auto i = 0; i < _textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        _textures[i].Bind();
    }


    int meshIndex = 0;

    for (auto& mesh : _meshes) {


        // rotate objects
        mesh.Transform = glm::rotate(mesh.Transform, glm::radians(0.3f), glm::vec3(1, 1, 1));



        if (mesh.Type == Cylinder) {
            // Rotate the cylinder
            mesh.Transform = glm::rotate(mesh.Transform, glm::radians(0.f), glm::vec3(1, 1, 1));
        }

        _textures[meshIndex++].Bind();

        _basicLitShader.SetMat4("model", mesh.Transform);
        mesh.Draw();
    }

    */
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








