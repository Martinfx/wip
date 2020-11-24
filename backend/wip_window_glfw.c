//
// WIP
// Copyright (c) 2020 Jovan Lanik
//

// GLFW Window Functions

#include <GLFW/glfw3.h>

#include "wip_fn.h"
#include "wip_window.h"
#include "wip_input.h"
#include "wip_conf.h"

void error_callback(int error, const char *message) {
	wip_log(WIP_ERROR, "GLFW: %s", message);
	return;
}

void window_close_callback(GLFWwindow *window) {
	wip_debug(WIP_INFO, "GLFW: Close requested by environment...");
	//glfwSetWindowShouldClose(window, GLFW_FALSE);
	return;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if(action == GLFW_REPEAT) return;
	wip_key_t nkey = { action ? 1 : 0, key };
	int ret = wip_writeKey(nkey);
	if(!ret) wip_log(WIP_ERROR, "GLFW: Dropped input key.");
	return;
}

void wip_initWindow(wip_window_t *window) {
	wip_debug(WIP_INFO, "%s: Initializing window...", __func__);

	if(!glfwInit())
		wip_log(WIP_FATAL, "%s: Couldn't initialize GLWF.", __func__);
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_FALSE);
	glfwWindowHint(GLFW_SAMPLES, wip_getConfInt("graphics.msaa"));
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window->handle = glfwCreateWindow(wip_getConfInt("video.width"), wip_getConfInt("video.height"), "WIP", NULL, NULL);
	if(!window->handle) {
		wip_log(WIP_FATAL, "%s: Couldn't create window.", __func__);
	}
	glfwSetWindowCloseCallback(window->handle, window_close_callback);
	glfwSetKeyCallback(window->handle, key_callback);

	wip_debug(WIP_INFO, "%s: Done.", __func__);
	return;
}

void wip_setWindow(wip_window_t *window) {
	glfwMakeContextCurrent(window->handle);
}

void wip_swapWindow(wip_window_t *window) {
	glfwSwapBuffers(window->handle);
}

void wip_pollWindow(wip_window_t *window) {
	glfwPollEvents();
	if(glfwWindowShouldClose(window->handle)) window->close = 1;
}

double wip_timeWindow(wip_window_t *window) {
	return glfwGetTime();
}

void wip_termWindow(wip_window_t *window) {
	wip_debug(WIP_INFO, "%s: Terminating window...", __func__);
	glfwTerminate();
}

