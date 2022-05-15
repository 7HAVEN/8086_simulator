#pragma once

#ifndef _window_
#define _window_
//externals

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


// std headers 
#include<string>
class window {
private:
	int winWidth, winHeight;
	std::string winName;

public:
	GLFWwindow* win;
	window(int widht, int height, std::string name);
	~window();
	void createWindow(int width, int height, std::string name, GLFWmonitor* monitor, GLFWwindow* share);
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // idk why this wasnt used

};
#endif