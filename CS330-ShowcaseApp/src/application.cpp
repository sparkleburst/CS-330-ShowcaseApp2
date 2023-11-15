#include <application.h>
#include <iostream>
#include <types.h>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

// constructor
Application::Application(std::string windowTitle, int width, int height) : _applicationName{ windowTitle },
_width{ width }, _height{ height } {};

// run function
void Application::Run()
{
	// open the window
	if (!openWindow()) {
		return;
	}

	_running = true;

    // set up the scene
    setupScene();

	// run application

	while (_running) {
		if (glfwWindowShouldClose(_window)) {
			_running = false;
			break;
		}


	
		// makes the background of the main window red
		glClearColor(1.0f, 1.0f, 1.0f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

        // adding vertices
        // update
        update();
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
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow*
    window, int width, int height)
		{
			// this gets called whenever the window is resized
			// std::cout << "window has resized!" << std::endl;
			glViewport(0, 0, width, height);

            auto app = reinterpret_cast<Application*>(glfwGetWindowUserPointer(window));
            app->_width = width;
            app->_height = height;
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

void Application::setupScene() {

    _meshes.emplace_back(Shapes::cubeVertices, Shapes::cubeElements);

    // get to shaders file info
    Path shaderPath = std::filesystem::current_path() / "shaders";
    _shader = Shader(shaderPath / "basic_shader.vert", shaderPath / "basic_shader.frag");


}

bool Application::update() {
    return false;
}

bool Application::draw() {
    // makes the background of the main window lilac
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // basic camera
    glm::mat4 view = glm::lookAt(glm::vec3(-1.f, 2.0f, -2.f),
                                 glm::vec3(0.f,0.f,0.f),
                                 glm::vec3(0.f, 1.f, 0.f));

    // 75 degree field of view
    glm::mat4 projection = glm::perspective(glm::radians(75.f), (float)_width / (float)_height,
                                            0.1f, 100.f);



    // bind shaders before drawing meshes
    _shader.Bind();
    _shader.SetMat4("projection", projection);
    _shader.SetMat4("view", view);


    for (auto& mesh : _meshes) {
        // rotate objects
        mesh.Transform = glm::rotate(mesh.Transform, glm::radians(0.1f),
                                     glm::vec3(1, 1, 0));

        _shader.SetMat4("model", mesh.Transform);
        mesh.Draw();
    }

    glfwSwapBuffers(_window);
    glfwPollEvents();

    return false;
}





