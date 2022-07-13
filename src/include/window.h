#pragma once

#ifndef _window_
#define _window_
//externals
#include "include/memory.h"
#include "include/decoder.h"
#include "include/operations.h"

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
	int regData[13];
public:
	GLFWwindow* win;
	Decoder* decoder;
	_8086_Operations* Operation;

	window(int width, int height, std::string name,Decoder* decoder,_8086_Operations* Operation);
	~window();
	void createWindow(int height, int width, std::string name, GLFWmonitor* monitor, GLFWwindow* share);
	void getDataFromRegisters();
	//void framebuffer_size_callback(GLFWwindow* window, int width, int height);  // idk why this wasnt used

};
#endif