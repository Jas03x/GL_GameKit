//
//  Camera.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Camera.h"

Camera* Camera::_global_camera = NULL;

CharacterCamera::CharacterCamera(float width, float height, const glm::vec3& _position, const glm::vec3& _target)
{
    this->position = _position;
    this->target = _target;
    this->rotation = glm::vec3(0);
    this->view = glm::lookAt(_position, _target, glm::vec3(0, 1, 0));
    this->projection = glm::perspective(45.0f, (float) width / (float) height, 0.1f, 1000.0f);
    Camera::update();
}

void CharacterCamera::update()
{
    this->view = glm::lookAt(this->position, this->target, glm::vec3(0, 1, 0));
    if(this->rotation != glm::vec3(0))
    {
        glm::mat4 matrices[3];
        
        static const glm::vec3 ROTATION_TABLE[3] = {
            glm::vec3(1,0,0), // x
            glm::vec3(0,1,0), // y
            glm::vec3(0,0,1)  // z
        };
        for(unsigned int i = 0; i < 3; i++)
        {
            if(this->rotation[i] == 0) continue;
            this->view = glm::rotate(this->rotation[i], ROTATION_TABLE[i]) * this->view;
        }
    }
    Camera::update();
}
