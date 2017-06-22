//
//  Camera.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Camera.h"

Camera* Camera::_global_camera = NULL;

/************************************************************************/
/************************************************************************/

CharacterCamera::CharacterCamera(float width, float height, const glm::vec3& _position, const glm::vec3& _target, float z_near, float z_far)
{
    this->position = _position;
    this->target = _target;
    this->rotation = glm::vec3(0);
    this->view = glm::lookAt(_position, _target, glm::vec3(0, 1, 0));
    this->projection = glm::perspective(45.0f, (float) width / (float) height, z_near, z_far);
    Camera::update();
}

void CharacterCamera::update()
{
    this->view = glm::lookAt(this->position, this->target, glm::vec3(0, 1, 0));
    if(this->rotation != glm::vec3(0))
    {
        this->view = this->view * glm::toMat4(glm::quat(this->rotation));
    }
    Camera::update(); // multiplies the view by the projection
}

/************************************************************************/
/************************************************************************/

TargetCamera::TargetCamera(float width, float height, const glm::vec3& _position, const glm::vec3& _target, float z_near, float z_far)
{
    this->position = _position;
    this->target = _target;
    this->rotation = glm::vec3(0);
    this->up_vector = glm::vec3(0, 1, 0);
    this->view = glm::lookAt(_position, _target, this->up_vector);
    this->projection = glm::perspective(45.0f, (float) width / (float) height, z_near, z_far);
    Camera::update();
}

void TargetCamera::update()
{
    this->view = glm::lookAt(this->position, this->target, this->up_vector);
    if(this->rotation != glm::vec3(0))
    {
        this->view = glm::toMat4(glm::quat(this->rotation)) * this->view;
    }
    Camera::update(); // multiplies the view by the projection
}
