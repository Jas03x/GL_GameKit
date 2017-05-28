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

class Camera
{
private:
    static Camera* _global_camera;
    
public:
    glm::mat4 view, projection;
    glm::mat4 vp; // combined view and projection
    
    inline static const glm::mat4& getViewMatrix() { return _global_camera->view; }
    inline static const glm::mat4& getProjectionMatrix() { return _global_camera->projection; }
    inline static const glm::mat4& getMatrix() { return _global_camera->vp; }
    
    Camera(){}
    inline void update(){ this->vp = this->projection * this->view; }
    inline void bind() { _global_camera = this; }
};

// The camera designed to stay behind the player:
class CharacterCamera : public Camera
{
public:
    glm::vec3 target;
    glm::vec3 position;
    glm::vec3 rotation;
    
    CharacterCamera(){}
    CharacterCamera(float width, float height, const glm::vec3& _position, const glm::vec3& _target);
    void update();
};


#endif /* Camera_hpp */
