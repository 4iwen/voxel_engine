#pragma once

#include "../../deps/imgui/include/imgui.h"
#include "../../deps/imgui/include/imgui_impl_glfw.h"
#include "../../deps/imgui/include/imgui_impl_opengl3.h"

#include "../camera/Camera.h"

class Gui
{
public:
	static void init(GLFWwindow* main_window);
	static void render();
	static void draw_debug_window();
	static void cleanup();
	static void new_frame();

private:
	static void setup();
	static void set_style();
};