#pragma once

#include "../../deps/imgui/include/imgui.h"
#include "../../deps/imgui/include/imgui_impl_glfw.h"
#include "../../deps/imgui/include/imgui_impl_opengl3.h"

#include <glfw3.h>

class Renderer
{
public:
    Renderer();

private:
    void loop();
};

