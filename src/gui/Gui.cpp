#include "Gui.h"

void Gui::setup()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); // setup imgui context
	ImGuiIO& io = ImGui::GetIO(); (void)io; // imgui io settings
}

void Gui::init(GLFWwindow* main_window)
{
	setup();
	set_style();

	ImGui_ImplGlfw_InitForOpenGL(main_window, true); // imgui glfw init
	ImGui_ImplOpenGL3_Init("#version 330"); // imgui opengl init
}

void Gui::set_style()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.22f, 0.48f, 0.16f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.41f, 0.98f, 0.26f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.41f, 0.98f, 0.26f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.23f, 0.48f, 0.16f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.23f, 0.48f, 0.16f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.23f, 0.48f, 0.16f, 0.98f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.41f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.37f, 0.88f, 0.24f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.41f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.41f, 0.98f, 0.26f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.41f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.98f, 0.06f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.41f, 0.98f, 0.26f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.98f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.41f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.24f, 0.75f, 0.10f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.24f, 0.75f, 0.10f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.41f, 0.98f, 0.26f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.98f, 0.26f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.41f, 0.98f, 0.26f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.26f, 0.58f, 0.18f, 0.86f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.41f, 0.98f, 0.26f, 0.80f);
	colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.68f, 0.20f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.15f, 0.07f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.42f, 0.14f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.41f, 0.98f, 0.26f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.41f, 0.98f, 0.26f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	ImGuiStyle* style = &ImGui::GetStyle();
	style->ChildRounding = 4.0f;
	style->FrameRounding = 2.0f;
	style->GrabMinSize = 7.0f;
	style->PopupRounding = 2.0f;
	style->ScrollbarRounding = 12.0f;
	style->ScrollbarSize = 13.0f;
	style->TabBorderSize = 1.0f;
	style->TabRounding = 0.0f;
	style->WindowRounding = 4.0f;
}

void Gui::new_frame()
{
	ImGui_ImplOpenGL3_NewFrame(); // imgui frame setup
	ImGui_ImplGlfw_NewFrame();    // 
	ImGui::NewFrame(); // start new imgui drawing area
}

void Gui::render()
{
	ImGui::Render();                                        // pass all imgui things to imgui render
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); //
}

void Gui::draw_debug_window()
{
	unsigned int chunks_loaded = 0;
	unsigned int voxels_loaded = 0;

	ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Once);
	ImGui::Begin("debug", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("fps: %.1f", ImGui::GetIO().Framerate);
	ImGui::Separator();
	ImGui::Text("chunks loaded: %u", chunks_loaded);
	ImGui::Text("voxels loaded: %u", voxels_loaded);
	ImGui::Separator();
	ImGui::Text("camera x: %f", Camera::camera_position.x);
	ImGui::Text("camera y: %f", Camera::camera_position.y);
	ImGui::Text("camera z: %f", Camera::camera_position.z);
	ImGui::End();
}

void Gui::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown(); //
	ImGui_ImplGlfw_Shutdown();    // destroy imgui context
	ImGui::DestroyContext();      //
}