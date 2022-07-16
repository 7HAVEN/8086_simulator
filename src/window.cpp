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
void embraceTheDarkness();
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
    char segment[10] = "0000";
    char offset[10] = "0000";
    bool run = false,fetch = false,write= false;
    int seg = 0;
    //int ax, bx, cx, dx;
    
    // Main loop
    while (!glfwWindowShouldClose(win))
    {
        getDataFromRegisters();
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        if (show_another_window)
        {
            //embraceTheDarkness();g
            ImGui::Begin("8086 sim", &show_another_window);
            ImGui::GetWindowContentRegionMax();
            ImGui::SetWindowFontScale(1.5f);
            ImGui::InputTextMultiline("example", codeBuffer, IM_ARRAYSIZE(codeBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            {
                ImGui::PushID(0);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV( 0.6f, 0.7f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV( 0.15f, 0.9f, 0.9f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.2f, 0.8f, 1.0f));
                run = ImGui::Button("RUN CODE");
                ImGui::PopStyleColor(3);
                ImGui::PopID();

            }
            
            if (run) {
                Operation->executeCode(codeBuffer);
                std::cout << Operation->Ds << std::endl;
                run = false;
            }
            if (fetch) {
                if (segment[0] == '\0' || offset[0] == '\0') {
                    std::cout << "pls enter a valid value\n";
                }
                else {
                    int segm = std::stoi(segment);
                    int off = std::stoi(offset);

					seg = Operation->getDataFromMemory(segm, off);
                }
                
            }
            if (write) {
                int segm = std::stoi(segment);
                int off = std::stoi(offset);
                Operation->writeDataToMemory(segm, off, seg);

            }
            {
                // registers
                ImGui::PushItemWidth(width / 2 - 100);
                ImGui::Text("16 bit Registers");
                ImGui::Text("AX");
                ImGui::SameLine();
                ImGui::InputInt("##AX",&regData[1]);
                ImGui::SameLine();
                
                ImGui::Text("BX");
                ImGui::SameLine();
                ImGui::InputInt("##BX", &regData[2]);
                
                ImGui::Text("CX");
                ImGui::SameLine();
                ImGui::InputInt("##CX", &regData[3]);
                ImGui::SameLine();

                ImGui::Text("DX");
                ImGui::SameLine();
                ImGui::InputInt("##DX", &regData[4]);
         

                ImGui::Text("8 bit Registers");
                ImGui::Text("AH");
                ImGui::SameLine();
                ImGui::InputInt("##AH", &regData[5]);
                ImGui::SameLine();

                ImGui::Text("AL");
                ImGui::SameLine();
                ImGui::InputInt("##AL", &regData[6]);
        

                ImGui::Text("BH");
                ImGui::SameLine();
                ImGui::InputInt("##BL", &regData[7]);
                ImGui::SameLine();

                ImGui::Text("BL");
                ImGui::SameLine();
                ImGui::InputInt("##BH", &regData[8]);

                ImGui::Text("CH");
                ImGui::SameLine();
                ImGui::InputInt("##CH", &regData[9]);
                ImGui::SameLine();

                ImGui::Text("CL");
                ImGui::SameLine();
                ImGui::InputInt("##CL", &regData[10]);

                ImGui::Text("DH");
                ImGui::SameLine();
                ImGui::InputInt("##DH", &regData[11]);
                ImGui::SameLine();

                ImGui::Text("DL");
                ImGui::SameLine();
                ImGui::InputInt("##DL", &regData[12]);

                ImGui::PopItemWidth();

            }
            {
                ImGui::PushItemWidth((width / 2) - 50);

                ImGui::Text("Fetch and Write Data to memory");
                ImGui::InputTextWithHint("segment", "segment address", segment, IM_ARRAYSIZE(segment));

                ImGui::InputTextWithHint("offset", "offset", offset, IM_ARRAYSIZE(segment));
                ImGui::PopItemWidth();

                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.13f, 0.8f, 0.9f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(9.0f, 0.3f, 0.9f));
                fetch = ImGui::Button("FETCH DATA");
                ImGui::PopStyleColor(3);
                ImGui::Text("DATA: ");
                ImGui::SameLine();
                ImGui::InputInt("##data", &seg);

                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.7f, 0.88f, 0.9f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(9.0f, 0.3f, 0.9f));
                write = ImGui::Button("WRITE DATA");
                ImGui::PopStyleColor(3);
               
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
void window::getDataFromRegisters() {
    for (int i = 0; i < 5; i++) {
        uint16_t data = Operation->get16bitData(i);
        regData[i] = (int)data;
    }
    for (int i = 5; i < 13; i++) {
        uint8_t data = Operation->get8bitData(i);
        regData[i] = (int)data;
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
void embraceTheDarkness()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    //colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    //colors[ImGuiCol_TitleBg] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    //colors[ImGuiCol_TitleBgActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    //colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    
    colors[ImGuiCol_Header] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

   /* style->FramePadding = ImVec2(4, 2);
    style->ItemSpacing = ImVec2(10, 2);
    style->IndentSpacing = 12;
    style->ScrollbarSize = 10;

    style->WindowRounding = 4;
    style->FrameRounding = 4;
    style->PopupRounding = 4;
    style->ScrollbarRounding = 6;
    style->GrabRounding = 4;
    style->TabRounding = 4;*/

    //style->WindowTitleAlign = ImVec2(1.0f, 0.5f);
    //style->WindowMenuButtonPosition = ImGuiDir_Right;

    style->DisplaySafeAreaPadding = ImVec2(4, 4);
}

