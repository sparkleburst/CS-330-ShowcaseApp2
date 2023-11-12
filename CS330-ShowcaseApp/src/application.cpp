#include <application.h>
#include <iostream>
#include <types.h>
#include <glm/glm.hpp>
#include <vector>

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
	glfwSetFramebufferSizeCallback(_window, [](GLFWwindow*
    window, int width, int height)
		{
			// this gets called whenever the window is resized
			// std::cout << "window has resized!" << std::endl;
			glViewport(0, 0, width, height);
		});

	// below - now we load all the OpenGl functions

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return false;
	}

    return true;
}

void Application::setupScene() {

    std::vector<Vertex> vertices = {
            {
                    // this is 0
                    .Position = {-0.5f, 0.4f, 0.0f},
                    .Color = {1.f, 0.f, 0.f} // red
            },
            {
                    // this is 1
                    .Position = {-0.5f, -0.6f, 0.0f},
                    .Color = {0.f, 0.f, 1.f} // blue
            },
            {
                    // this is 2
                    .Position = {0.5f, -0.6f, 0.0f},
                    .Color = {0.f, 1.f, 0.f} // green
            },
            {
                    // this is 3
                    .Position = {-0.5f, 0.6f, 0.0f},
                    .Color = {1.f, 0.f, 0.f} // red
            },
            {
                    // this is 4
                    .Position = {0.5f, -0.4f, 0.0f},
                    .Color = {0.f, 1.f, 0.f} // green
            },
            {
                    // this is 5
                    .Position = {0.5f, 0.6f, 0.0f},
                    .Color = {1.f, 1.f, 1.f} // white
            }
    };

    // define the elements (remember element arrays are only indices)
    std::vector<uint32_t> elements {
        // this is telling the order in which each vertex should be drawn
        0, 1, 2,
        3, 4, 5
    };

    // we can create multiple meshes
    _meshes.emplace_back(std::move(vertices), std::move(elements));

    // to make new vertices

    vertices = {
            {
                    // this is 0
                    .Position = {-0.25f, -0.25f, 0.0f},
                    .Color = {0.f, 0.f, 0.f} // red
            },
            {
                    // this is 1
                    .Position = {0.25f, -0.25f, 0.0f},
                    .Color = {1.f, 0.f, 0.f} // red
            },
            {
                    // this is 2
                    .Position = {0.f, 0.25f, 0.0f},
                    .Color = {1.f, 0.f, 0.f} // red
            }
    };

    // define the elements (remember element arrays are only indices)
    elements = {
            // this is telling the order in which each vertex should be drawn
            0, 1, 2
    };

    _meshes.emplace_back(std::move(vertices), std::move(elements));

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
    glClear(GL_COLOR_BUFFER_BIT);

    // bind shaders before drawing meshes
    _shader.Bind();

    for (auto mesh : _meshes) {
        mesh.Draw();
    }

    glfwSwapBuffers(_window);
    glfwPollEvents();

    return false;
}





