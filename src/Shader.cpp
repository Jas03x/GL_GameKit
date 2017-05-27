//
//  Shader.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Shader.h"

bool shader_status(GLuint id, GLenum type, const std::string& filename) {
    GLint status = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        int length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* error = new char[length];
        glGetShaderInfoLog(id, length, &length, error);
        
        printf("%s shader error (%s):\n%s\n", type == GL_VERTEX_SHADER ? "Vertex" : "Fragment", filename.c_str(), error);
        delete[] error;
        return false;
    }
    return true;
}

ShaderSource::ShaderSource(const char* vpath, const char* fpath)
{
    std::string vertex_source = File::read(vpath);
    std::string fragment_source = File::read(fpath);
    
    this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    this->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* v_source = &vertex_source[0];
    const char* f_source = &fragment_source[0];
    glShaderSource(this->vertex_shader, 1, &v_source, 0);
    glShaderSource(this->fragment_shader, 1, &f_source, 0);
    glCompileShader(this->vertex_shader);
    glCompileShader(this->fragment_shader);
    if(!shader_status(this->vertex_shader, GL_VERTEX_SHADER, vpath) || !shader_status(this->fragment_shader, GL_FRAGMENT_SHADER, fpath))
        throw -1;
}

ShaderSource::~ShaderSource() {
    if(glIsShader(this->vertex_shader) == GL_TRUE) glDeleteShader(this->vertex_shader);
    if(glIsShader(this->fragment_shader) == GL_TRUE) glDeleteShader(this->fragment_shader);
}

void Shader::source(const ShaderSource& shader_source) {
    this->id = glCreateProgram();
    glAttachShader(this->id, shader_source.vertex_shader);
    glAttachShader(this->id, shader_source.fragment_shader);
}

void Shader::link(const ShaderSource& shader_source)
{
    glLinkProgram(this->id);
    
    GLint status = 0;
    glGetProgramiv(this->id, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        int length = 0;
        glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &length);
        char* error = new char[length];
        glGetProgramInfoLog(this->id, length, &length, error);
        
        printf("Program link failure:\n%s\n", error);
        delete[] error;
        throw -1;
    }
    
    glDetachShader(this->id, shader_source.vertex_shader);
    glDetachShader(this->id, shader_source.fragment_shader);
}

void Shader::destroy() {
    if(glIsProgram(this->id) == GL_TRUE) glDeleteProgram(this->id);
}

GLint Shader::getAttribute(const char* name)
{
    GLint id = glGetAttribLocation(this->id, name);
    if(id < 0)
        printf("Warning: Attribute [%s] not found.\n", name);
    return id;
}

GLint Shader::getUniform(const char* name)
{
    GLint id = glGetUniformLocation(this->id, name);
    if(id < 0)
        printf("Warning: Uniform [%s] not found.\n", name);
    return id;
}

void Shader::bindAttributeLocation(GLuint index, const char* name) {
    glBindAttribLocation(this->id, index, name);
}

void Shader::bindFragDataLocation(GLuint index, const char* name) {
    glBindFragDataLocation(this->id, index, name);
}
