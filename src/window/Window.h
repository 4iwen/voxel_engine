#pragma once

#include <glad/glad.h> 
#include <glfw3.h>

#include <stdio.h>
#include <string>

class Window
{
public:
	GLFWwindow* window_handle;
	static unsigned int window_width;
	static unsigned int window_height;
	static bool show_mouse;

public:
	Window(unsigned int window_width, unsigned int window_height, std::string window_name);
	void create();

private:
	static void glfw_error_callback(int error, const char* description);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};