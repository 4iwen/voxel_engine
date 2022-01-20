#include "Camera.h"

glm::vec3 Camera::camera_position;
glm::vec3 camera_target;
glm::vec3 camera_direction;
glm::vec3 up;
glm::vec3 camera_right;
glm::vec3 camera_up;
glm::vec3 camera_front;

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera::Camera(glm::vec3 cam_position, glm::vec3 cam_target, glm::vec3 cam_up, glm::vec3 cam_front)
{
	camera_direction = glm::normalize(camera_position - camera_target);
	camera_right = glm::normalize(glm::cross(up, camera_direction));
	camera_position = cam_position;
	camera_target = cam_target;
	camera_front = cam_front;
	camera_up = cam_up;
}

void Camera::update(GLFWwindow* window, Shader &main_shader)
{
	float current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;

	process_input(window);
	
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);
	main_shader.set_mat4("view", view);
                                                                                                          
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), ((float)Window::window_width / (float)Window::window_height), 0.1f, 100.0f);
	main_shader.set_mat4("projection", projection);
}

void Camera::process_input(GLFWwindow* window)
{
	const float camera_speed = 2.5f * delta_time;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_position += camera_speed * camera_front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_position -= camera_speed * camera_front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_position -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_position += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera_position += camera_speed * camera_up;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera_position -= camera_speed * camera_up;
}