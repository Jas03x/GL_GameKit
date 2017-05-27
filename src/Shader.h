//
//  Shader.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

#include "GL.h"
#include "File.h"

#ifdef _WIN32
	#define INTERNAL(x) "C:\\Users\\Jas\\Documents\\Projects\\GameKit\\src\\Shaders\\" x
#else
	#define INTERNAL(x) "/Users/Jas/Documents/GameKit/src/Shaders/" x
#endif

// Class to manage the shader code
class ShaderSource
{
public:
    GLuint vertex_shader, fragment_shader;
    ShaderSource(const char* vpath, const char* fpath);
    ~ShaderSource();
};

// multi-stage bind-able shader
class Shader
{
private:
    GLuint id;
    
protected:
    Shader(){}
    
    void source(const ShaderSource& shader_source);
    void link(const ShaderSource& shader_source);
    void destroy();
    GLint getAttribute(const char* name);
    GLint getUniform(const char* name);
    void bindAttributeLocation(GLuint index, const char* name);
    void bindFragDataLocation(GLuint index, const char* name);
    
public:
    inline void bind() const { glUseProgram(this->id); }
};

#endif /* Shader_hpp */
