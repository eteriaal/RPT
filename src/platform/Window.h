// github.com/eteriaal/rpt
// src/platform/Window.h

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window();
    ~Window();

    bool create(int width, int height, const std::string& title);
    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();
    GLFWwindow* getGLFWwindow() const { return window; }

    void getSize(int& width, int& height) const;

private:
    GLFWwindow* window = nullptr;
};
