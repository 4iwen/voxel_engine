#pragma once

#include "../../deps/imgui/include/imgui.h"
#include "../../deps/imgui/include/imgui_impl_glfw.h"
#include "../../deps/imgui/include/imgui_impl_opengl3.h"

#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Renderer
{
public:
    Renderer();

private:
    void get_max_vertex_count();
    void draw_debug_window();
    void loop();
};

