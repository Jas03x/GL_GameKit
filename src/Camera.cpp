//
//  Camera.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Camera.h"

glm::mat4 Camera::model, Camera::view, Camera::projection;
glm::mat4 Camera::mv, Camera::mvp;

void Camera::init(float width, float height) {
    model = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(0, 3, 5), glm::vec3(0), glm::vec3(0, 1, 0));
    projection = glm::perspective(45.0f, (float) width / (float) height, 0.1f, 1000.0f);
    Camera::update();
}
