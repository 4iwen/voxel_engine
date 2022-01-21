#pragma once

#include "../shader/Shader.h"
#include "../window/Window.h"

class Camera 
{
public:
	static glm::vec3 camera_position;
	static float camera_fov;
	static float yaw;
	static float pitch;

	Camera(glm::vec3 cam_position, glm::vec3 cam_target, glm::vec3 cam_up, glm::vec3 cam_front);
	void update(GLFWwindow* window, Shader& main_shader);
	static void process_input(GLFWwindow* window);
	void setup(GLFWwindow* window);
	
private:
	static void mouse_callback(GLFWwindow* window, double x_in, double y_in);
	static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
};