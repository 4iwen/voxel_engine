#include "Camera.h"

glm::vec3 Camera::camera_position;
glm::vec3 camera_target;
glm::vec3 camera_direction;
glm::vec3 up;
glm::vec3 camera_right;
glm::vec3 camera_up;
glm::vec3 camera_front;

bool first_mouse = true;

float sensitivity = 0.05f;
float Camera::camera_fov = 90.0f;

float Camera::yaw = -90.0f;
float Camera::pitch = 0.0f;

float last_x = Window::window_width / 2.0f;
float last_y = Window::window_height / 2.0f;

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

void Camera::mouse_callback(GLFWwindow* window, double x_in, double y_in)
{
	float x = static_cast<float>(x_in);
	float y = static_cast<float>(y_in);

	if (first_mouse) // load in initial cursor pos values
	{
		last_x = x;
		last_y = y;
		first_mouse = false;
	}

	float x_offset = x - last_x;
	float y_offset = last_y - y;
	last_x = x;
	last_y = y;

	x_offset *= sensitivity;
	y_offset *= sensitivity;

	yaw += x_offset;

	if (yaw < -270)
		yaw = 90;
	if (yaw > 90)
		yaw = -270;

	pitch += y_offset;

	// clamp the pitch so that the camera doesnt get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;											 //
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); //
	front.y = sin(glm::radians(pitch));							 // convert 
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); //
	camera_front = glm::normalize(front);						 //
}

void Camera::setup(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide the cursor
	glfwSetCursorPosCallback(window, mouse_callback); // set the mouse callback -> get the mouse input
	glfwSetScrollCallback(window, scroll_callback); // set the scroll callback so we can change the fov
}

void Camera::update(GLFWwindow* window, Shader &main_shader)
{
	float current_frame = glfwGetTime();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;

	process_input(window);
	
	glm::mat4 view = glm::mat4(1.0f);												//
	view = glm::lookAt(camera_position, camera_position + camera_front, camera_up);	// update shader var "view"
	main_shader.set_mat4("view", view);												//
                                                                                                          
	glm::mat4 projection = glm::perspective(glm::radians(camera_fov), ((float)Window::window_width / (float)Window::window_height), 0.1f, 100.0f);	// update shader var "projection"
	main_shader.set_mat4("projection", projection);																							//
}

void Camera::process_input(GLFWwindow* window)
{
	float camera_speed = 2.5f * delta_time;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera_speed *= 2;

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

void Camera::scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
	camera_fov -= (float)y_offset;
	if (camera_fov < 30.0f)
		camera_fov = 30.0f;
	if (camera_fov > 90.0f)
		camera_fov = 90.0f;
}