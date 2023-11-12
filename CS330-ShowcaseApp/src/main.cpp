#include <iostream>
#include <application.h>


/* not using namespace std because in the real world can run into conflicting namespace issues
   get used to do seeing/doing it this way 'std::'*/

int main(int argc, char** argv) {
	// std::cout << "Hello World!" << std::endl; - just to make sure all is working

	/* moved to application.cpp
	// initialize a window with glfwInit();
	glfwInit();

	// this is so we can be compatible with older versions
	// our version is 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// above is things needed for glfw and glad
	// below - now we open a window

	GLFWwindow* window = glfwCreateWindow(800, 600, "MaxsOpenGL", nullptr, nullptr);
	// (size(x, y), title, (not sure what nullptrs are about yet but using them instead
	// of NULL because NUll is C content and we are using C++)

	if (!window) {
		std::cerr << "failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	// !window is the same as window == nullptr
	// cerr is console error
	moved to application.cpp end */

	/* moved to application.cpp
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
		{
			// this gets called whenever the window is resized
			std::cout << "window has resized!" << std::endl;
			glViewport(0, 0, width, height);
		});

	// below - now we load all of the OpenGl functions

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	*/

	/* moved to application.cpp
	// this makes the window stay open
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	*/

	/* moved to application.cpp
	glfwTerminate();
	*/

	Application app{ "Max Gilhespy CS-330 ShowcaseApp", 800, 600 };

	app.Run();

	return 0;

}