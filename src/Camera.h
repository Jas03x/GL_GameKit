//
//  Camera.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "GLM.h"

// the camera designed to stay behind the player
namespace Camera
{
    extern glm::mat4 view, projection;
    extern glm::mat4 vp;
    
    void perspectiveView(float width, float height, const glm::vec3& position, const glm::vec3& target);
    void orthographicView(float width, float height, const glm::vec3& position);
    
    inline void update() {
        vp = projection * view;
    }
    
    inline void translate(const glm::vec3& translation) {
        Camera::view = glm::translate(Camera::view, translation);
    }
    
    inline void rotate(float radians, const glm::vec3& axis) {
        Camera::view = glm::rotate(Camera::view, radians, axis);
    }
}


#endif /* Camera_hpp */
