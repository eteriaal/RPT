// github.com/eteriaal/rpt
// src/graphics/Renderer.h

#pragma once
#include <glad/glad.h>
#include "graphics/Shader.h"
#include "platform/Window.h"
#include "ui/DebugParams.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(const Window& window);
    void render(const DebugParams& params);

private:
    const Window* m_window = nullptr;

    Shader shader;
    GLuint vao = 0;
    GLuint vbo = 0;
    
    GLint uTimeLocation = -1;
    GLint uTransformLocation = -1;
    GLint uViewLocation = -1;
    GLint uProjectionLocation = -1;

    GLuint textureID = 0;
};