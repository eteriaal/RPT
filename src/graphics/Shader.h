// github.com/eteriaal/rpt
// src/graphics/Shader.h

#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
public:
    Shader();
    ~Shader();

    bool load(const std::string& vertPath, const std::string& fragPath);

    void use() const {
        if (ID != 0) {
            glUseProgram(ID);
        }
    }

    static void unuse() { glUseProgram(0); }
    GLuint getID() const { return ID; }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

private:
    GLuint ID = 0;

    std::string loadFile(const std::string& path) const;
    GLuint compileShader(const std::string& source, GLenum type) const;
    bool linkProgram(GLuint vertexShader, GLuint fragmentShader);
    void cleanupIfNeeded();
};