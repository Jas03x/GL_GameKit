//
//  Collider.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-08.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Collider_hpp
#define Collider_hpp

#include "GLM.h"
#include "btBulletDynamicsCommon.h"

class Collider
{
protected:
    btScalar mass;
    glm::vec3 scale;
    
    btCollisionShape* shape;
    btDefaultMotionState* motion_state;
    btRigidBody* rigid_body;
    
public:
    Collider(const glm::vec3& _scale = glm::vec3(1.0f));
    ~Collider();
    
    inline void getModelMatrix(glm::mat4& matrix) const {
        btTransform transform;
        this->rigid_body->getMotionState()->getWorldTransform(transform);
        float arr[16];
        transform.getOpenGLMatrix(arr);
        memcpy(&matrix[0][0], arr, sizeof(float) * 16);
    }
    
    inline const glm::vec3& getScale() const { return this->scale; }
    
    void update();
    void translate(const glm::vec3& translation);
    void setTranslation(const glm::vec3& translation);
    void rotate(const glm::vec3& rotation);
    void setRotation(const glm::vec3& rotation);
    void setModelMatrix(const glm::mat4& matrix);
};

#endif /* Collider_hpp */
