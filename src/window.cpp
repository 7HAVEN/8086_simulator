//user defined
#include "../include/window.h"
// externals

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

//std
#include<stdexcept>
#include<iostream>

window::window(int width, int height, std::string name,Decoder* decoder,_8086_Operations* Operation) {
	winHeight = height;
	winWidth = width;
	winName = name;
    this->decoder = decoder;
    this->Operation = Operation;
	createWindow(winHeight, winWidth, winName ,nullptr,nullptr);
    win = nullptr;


}
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// most of the stuff is based on imgui examples 

void window::createWindow(int width, int height, std::string name, GLFWmonitor* monitor, GLFWwindow* share) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        throw(std::runtime_error("glfw failed to initalise"));

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 
#endif
    win = glfwCreateWindow(height, width, name.c_str(), nullptr, nullptr);
    if (win == NULL) {
        std::cout << "window creation failed";
        throw(std::runtime_error("window creation failed"));
       
    }
   glfwMakeContextCurrent(this->win);
//    glfwSwapInterval(1); // Enable vsync
      //Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(win, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    char codeBuffer[1000 * 16] = {};
    char segment[10] = {};
    char offset[10] = {};
    bool run = false;
    int seg;
    // Main loop
    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (show_demo_window) // demo window
            ImGui::ShowDemoWindow(&show_demo_window);

        if (show_another_window)
        {
            ImGui::Begin("Example Window", &show_another_window);
            ImGui::InputTextMultiline("example", codeBuffer, IM_ARRAYSIZE(codeBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            {
                ImGui::PushID(0);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV( 7.0f, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV( 7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
                run = ImGui::Button("RUN CODE");
                ImGui::PopStyleColor(3);
                ImGui::PopID();

            }
            
            if (run) {
              
            }
            {
                ImGui::InputTextWithHint("segment","segment address", segment, IM_ARRAYSIZE(segment));
                //ImGui::SameLine(); 
                ImGui::InputTextWithHint("offset","offset", offset, IM_ARRAYSIZE(segment));

                //ImGui::InputInt

            }
            
            ImGui::End();
        }

       
       
        // Rendering
        ImGui::Render();
        
        int display_w, display_h;
        glfwGetFramebufferSize(win, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(win);
    }


}

window::~window() {

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(win);
    glfwTerminate();

}

