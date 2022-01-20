#pragma once

#include <glad/glad.h> 
#include <glfw3.h>

#include <stdio.h>
#include <string>

class Window
{
public:
	GLFWwindow* window_handle;

public:
	Window(unsigned int window_width, unsigned int window_height, std::string window_name);
	void process_input(GLFWwindow* window);

private:
	void create_window();

	static void glfw_error_callback(int error, const char* description);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};