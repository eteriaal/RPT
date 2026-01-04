// github.com/eteriaal/rpt
// src/graphics/Renderer.cpp

#include "graphics/Renderer.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Renderer::Renderer() = default;

Renderer::~Renderer() {
    if (vbo != 0) glDeleteBuffers(1, &vbo);
    if (vao != 0) glDeleteVertexArrays(1, &vao);
    std::cout << "Renderer shutdown complete\n";
}

bool Renderer::init(const Window& window) {
    m_window = &window;

    if(!shader.load("shaders/triangle.vert", "shaders/triangle.frag")) {
        std::cerr << "renderer:init error: !shader.load() \n";
        return false;
    }

    shader.use();

    uTimeLocation = glGetUniformLocation(shader.getID(), "uTime");
    uTransformLocation = glGetUniformLocation(shader.getID(), "uTransform");
    uViewLocation = glGetUniformLocation(shader.getID(), "uView");
    uProjectionLocation = glGetUniformLocation(shader.getID(), "uProjection");
    glUniform1i(glGetUniformLocation(shader.getID(), "ourTexture"), 0);

    float vertices[] = {
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };


    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    glEnable(GL_DEPTH_TEST);

    std::cout << "VBO created and data uploaded (ID: " << vbo << ")\n";
    std::cout << "VAO created and configured (ID: " << vao << ")\n";
    // std::cout << "EBO created and data uploaded (ID: " << ebo << ")\n";

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("resources/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "texture loaded \n";
    }
    else
    {
        std::cerr << "Failed to load texture \n";
    }
    stbi_image_free(data);

    return true;
}

void Renderer::render(const DebugParams& params) {
    glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float time = static_cast<float>(glfwGetTime());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time*glm::radians(params.rotationSpeedY), glm::vec3(0,1,0));
    model = glm::rotate(model, time*glm::radians(params.rotationSpeedX), glm::vec3(1,0,0));
    model = glm::rotate(model, time*glm::radians(params.rotationSpeedZ), glm::vec3(0,0,1));

    glm::mat4 view = glm::lookAt(
        glm::vec3(params.camDistance, params.camHeight, params.camDistance),
        glm::vec3(0,0,0),
        glm::vec3(0,1,0)
    );

    int width, height;
    m_window->getSize(width,height);
    float aspect = (height==0) ? 1.f : float(width)/height;

    glm::mat4 projection = glm::perspective(glm::radians(params.fov), aspect, 0.1f, 100.f);

    shader.use();
    glUniformMatrix4fv(uTransformLocation,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(uViewLocation,1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(uProjectionLocation,1,GL_FALSE,glm::value_ptr(projection));

    glPolygonMode(GL_FRONT_AND_BACK, params.wireframe ? GL_LINE : GL_FILL);

    glBindVertexArray(vao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}