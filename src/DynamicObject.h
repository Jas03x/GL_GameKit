//
//  DynamicObject.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DynamicObject_h
#define DynamicObject_h

#include "Collider.h"
#include "SoftBody.h"
#include "DynamicMesh.h"
#include "PlaneCollider.h"

class DynamicObject : public DynamicMesh
{
protected:
    Collider* collider;
    
public:
    DynamicObject();
    void destroy();
    
    inline void rotate(const glm::quat& rotation){ this->collider->rotate(rotation); }
    inline void translate(const glm::vec3& translation){ this->collider->translate(translation); }
    inline void transform(const glm::vec3& translation, const glm::quat& rotation) { this->collider->transform(translation, rotation); }
};

#endif /* DynamicObject_h */
