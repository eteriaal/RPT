// github.com/eteriaal/rpt
// src/graphics/Shader.cpp

#include "graphics/Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader() = default;
Shader::~Shader() {
    cleanupIfNeeded();
}

void Shader::cleanupIfNeeded() {
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }
}

std::string Shader::loadFile(const std::string &path) const {
    std::ifstream file(path);
    if(!file.is_open()) {
        std::cerr << "Error: Shader::loadFile: file not found: " << path << "\n";
        return {};
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::compileShader(const std::string& source, GLenum type) const {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);

    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        const char* typeName = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
        std::cerr << "\033[1;31m" << typeName << " shader compilation failed:\033[0m\n";
        std::cerr << infoLog << "\n";
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

bool Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader) {
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    GLint success;
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "\033[1;31m shader linking failed:\033[0m\n";
        std::cerr << infoLog << "\n";

        glDeleteProgram(ID);
        ID = 0;
        return false;
    }
    return true;
}

bool Shader::load(const std::string& vertPath, const std::string& fragPath) { 
    cleanupIfNeeded();

    std::string vertSource = loadFile(vertPath);
    std::string fragSource = loadFile(fragPath);
    if(vertSource.empty() || fragSource.empty()) {
        std::cerr << "Failed to read one or both shader files\n";
        return false;
    }
    
    GLuint vertShader = compileShader(vertSource, GL_VERTEX_SHADER);
    GLuint fragShader = compileShader(fragSource, GL_FRAGMENT_SHADER);
    if (vertShader == 0 || fragShader == 0) {
        std::cerr << "Failed to compile one or both shader files\n";
        if (vertShader != 0) glDeleteShader(vertShader);
        if (fragShader != 0) glDeleteShader(fragShader);
        return false;
    }

    if (!linkProgram(vertShader, fragShader)) {
        std::cerr << "Failed to link shaders\n";
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        return false;
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    std::cout << "Shader loaded successfully! Program ID: " << ID << "\n";
    return true;
}


Shader::Shader(Shader&& other) noexcept
    : ID(other.ID)
{
    other.ID = 0;
}

Shader& Shader::operator=(Shader&& other) noexcept {
    if (this != &other) {
        cleanupIfNeeded();
        ID = other.ID;
        other.ID = 0;
    }
    return *this;
}