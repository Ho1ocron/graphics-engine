#ifndef SHADER_CPP
#define SHADER_CPP

#include <glad/glad.h>
#include <shader.h>

#include <fstream>
#include <glm/glm.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "glm/gtc/type_ptr.hpp"

// utility function for checking shader compilation/linking errors.
void _checkCompileErrors(const GLuint id, const std::string &type) {
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(id, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
void _checkCompileErrors(const GLuint id, const GLuint type) {
    switch(type) {
        case GL_VERTEX_SHADER:
            _checkCompileErrors(id, "VERTEX");
            break;
        case GL_FRAGMENT_SHADER:
            _checkCompileErrors(id, "FRAGMENT");
            break;
        case GL_GEOMETRY_SHADER:
            _checkCompileErrors(id, "GL_GEOMETRY_SHADER");
            break;
    }
}
GLuint _compileShader(const char *src, const GLuint type) {
    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    _checkCompileErrors(id, type);
    return id;
}

// constructor generates the shader on the fly
// ------------------------------------------------------------------------
Shader::Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode, fragmentCode, geometryCode;
    std::ifstream vShaderFile, fShaderFile, gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if(geometryPath != nullptr) {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    } catch(std::ifstream::failure &e) { std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl; }
    // 2. compile shaders
    unsigned int vertex, fragment, geometry;
    vertex = _compileShader(vertexCode.c_str(), GL_VERTEX_SHADER);
    fragment = _compileShader(fragmentCode.c_str(), GL_FRAGMENT_SHADER);
    // if geometry shader is given, compile geometry shader
    if(geometryPath != nullptr) geometry = _compileShader(geometryCode.c_str(), GL_GEOMETRY_SHADER);

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if(geometryPath != nullptr) glAttachShader(ID, geometry);
    glLinkProgram(ID);
    _checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer
    // necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr) glDeleteShader(geometry);
}

void Shader::use() const { glUseProgram(ID); }

void Shader::setBool(const char *name, const bool value) const { glUniform1i(glGetUniformLocation(ID, name), (int)value); }
void Shader::setInt(const char *name, const int value) const { glUniform1i(glGetUniformLocation(ID, name), value); }
void Shader::setFloat(const char *name, const float value) const { glUniform1f(glGetUniformLocation(ID, name), value); }
void Shader::setVec2(const char *name, const glm::vec2 &value) const { glUniform2fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value)); }
void Shader::setVec3(const char *name, const glm::vec3 &value) const { glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value)); }
void Shader::setVec4(const char *name, const glm::vec4 &value) const { glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value)); }
void Shader::setMat2(const char *name, const glm::mat2 &value) const { glUniformMatrix2fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value)); }
void Shader::setMat3(const char *name, const glm::mat3 &value) const { glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value)); }
void Shader::setMat4(const char *name, const glm::mat4 &value) const { glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value)); }


#endif
