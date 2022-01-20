#pragma once

#include "../shader/Shader.h"
#include "../window/Window.h"

class Camera 
{
public:
	static glm::vec3 camera_position;

	Camera(glm::vec3 cam_position, glm::vec3 cam_target, glm::vec3 cam_up, glm::vec3 cam_front);
	void update(GLFWwindow* window, Shader& main_shader);
	static void process_input(GLFWwindow* window);
};