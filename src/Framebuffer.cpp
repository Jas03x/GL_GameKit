//
//  Framebuffer.cpp
//  RoughRocket
//
//  Created by Jas S on 2017-05-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Framebuffer.h"

void Framebuffer::init(unsigned int width, unsigned int height)
{
    glGenFramebuffers(1, &this->id);
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
    
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenRenderbuffers(1, &this->depth_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER, this->depth_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depth_buffer);
    
    GLenum DRAW_BUFFERS[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DRAW_BUFFERS);
    
    GLint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE)
    {
        printf("OpenGL error %i while trying to create framebuffer: ", glGetError());
        switch(status)
        {
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                puts("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                puts("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                puts("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                puts("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER");
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED:
                puts("GL_FRAMEBUFFER_UNSUPPORTED");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                puts("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
                break;
            default:
                puts("GL_FRAMEBUFFER_UNDEFINED");
                break;
        }
        throw -1;
    }
    
    this->dimensions = glm::uvec2(width, height);
    this->unbind();
}

void Framebuffer::destroy()
{
    if(glIsTexture(this->texture) == GL_TRUE) glDeleteTextures(1, &this->texture);
    if(glIsRenderbuffer(this->depth_buffer) == GL_TRUE) glDeleteRenderbuffers(1, &this->depth_buffer);
    if(glIsFramebuffer(this->id) == GL_TRUE) glDeleteFramebuffers(1, &this->id);
}
