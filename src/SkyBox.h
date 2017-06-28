#ifndef SKYBOX_H
#define SKYBOX_H

#include <array>

#include "GL.h"
#include "Texture.h"

class SkyBox
{
private:
    GLuint texture;
    
public:
    SkyBox(){}
    SkyBox(const char* tex_path);
    SkyBox(const std::array<std::string, 6>& tex_paths); // +x, -x, +y, -y, +z, -z
    void destroy();
    
    inline void bind(GLenum uniform, int target) const {
        glActiveTexture(GL_TEXTURE0 + target);
        glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
        glUniform1i(uniform, target);
    }
};

#endif
