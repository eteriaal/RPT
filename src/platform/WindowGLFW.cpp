// github.com/eteriaal/rpt
// src/platform/WindowGLFW.cpp

#include "platform/Window.h"
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window() = default;
Window::~Window() {
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}



bool Window::create(int width, int height, const std::string& title) {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    return true;
}

bool Window::shouldClose() const { return glfwWindowShouldClose(window); }
void Window::pollEvents() { glfwPollEvents(); }
void Window::swapBuffers() { glfwSwapBuffers(window); }

void Window::getSize(int& width, int& height) const {
    glfwGetFramebufferSize(window, &width, &height);
}