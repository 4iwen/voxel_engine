#include "Window.h"

GLFWwindow* window_handle;

unsigned int _width;
unsigned int _height;
std::string _name;

Window::Window(unsigned int window_width, unsigned int window_height, std::string window_name)
{
	_width = window_width;
	_height = window_height;
	_name = window_name;

	create_window();
}

void Window::process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		printf("Detected input: Escape\n");
}

void Window::create_window()
{
	glfwSetErrorCallback(glfw_error_callback);

	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_handle = glfwCreateWindow(_width, _height, "voxel engine", NULL, NULL);
	if (window_handle == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window_handle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
	}

	glViewport(0, 0, _width, _height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	glfwSetFramebufferSizeCallback(window_handle, framebuffer_size_callback);
}