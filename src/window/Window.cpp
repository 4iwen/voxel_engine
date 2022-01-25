#include "Window.h"

GLFWwindow* window_handle;

unsigned int Window::window_width;
unsigned int Window::window_height;
std::string _name;

Window::Window(unsigned int width, unsigned int height, std::string name)
{
	window_width = width;
	window_height = height;
	_name = name;
}

void Window::create()
{
	glfwSetErrorCallback(glfw_error_callback); // set the glfw error callback -> if an error occurs, it will be displayed in the console

	if (!glfwInit()) // check if glfw correctly initialized -> exit if not
	{
		printf("Failed to initialize GLFW\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);				   // 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);				   // hints for opengl, what version are we using and what profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 

	window_handle = glfwCreateWindow(window_width, window_height, "voxel engine", NULL, NULL); // create window using glfw
	if (window_handle == NULL) // check if window got created -> exit if not
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window_handle); // create context for glfw

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // load opengl
	{
		printf("Failed to initialize GLAD\n");
	}

	glViewport(0, 0, window_width, window_height);

	glfwSetFramebufferSizeCallback(window_handle, framebuffer_size_callback); // check for window resize -> adjust opengl viewport
	glfwSwapInterval(1); // vsync | 1 -> enabled | 0 -> disabled
}

void Window::glfw_error_callback(int error, const char* description)
{
	printf("Glfw Error %d: %s\n", error, description);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	printf("Window resized to: %i x %i\n", width, height);
	glViewport(0, 0, width, height);

	window_height = height;
	window_width = width;
}