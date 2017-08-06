//
//  Collider.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Collider_h
#define Collider_h

#include <BulletCollision/btBulletCollisionCommon.h>
#include <BulletDynamics/btBulletDynamicsCommon.h>

#include "Math3d.h"
#include "Transform.h"

class Collider
{
protected:
    btCollisionObject* body;
    Transform* transformation;
    
public:
    enum Type
    {
        NULL_COLLIDER = 0,
        SOFT_BODY = 1,
        PLANE_COLLIDER = 2
    };
    
    Collider(Transform* _transformation = NULL);
    virtual ~Collider();
    
    virtual void bind();
    virtual void unbind();
    
    inline const btCollisionObject* getCollisionObject() const { return this->body; }
    inline bool hasTransformationPointer() const { return this->transformation != NULL; }
    
    void rotate(const glm::quat& rotation);
    void translate(const glm::vec3& translation);
    void transform(const glm::vec3& translation, const glm::quat& rotation);
    
    inline void updateTransformationPointer() {
        btTransform transform = this->body->getWorldTransform();
        const btVector3& origin = transform.getOrigin();
        const btQuaternion& rotation = transform.getRotation();
        this->transformation->translation = glm::vec3(origin.getX(), origin.getY(), origin.getZ());
        this->transformation->rotation = glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ());
    }
};

#endif /* Collider_h */
