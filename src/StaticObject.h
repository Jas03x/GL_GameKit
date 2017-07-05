//
//  StaticObject.h
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef StaticObject_h
#define StaticObject_h

#include "Collider.h"
#include "StaticMesh.h"

class StaticObject : protected StaticMesh
{
protected:
    Collider* collider;
    
public:
    StaticObject(){}
    StaticObject(const char* path, Collider::Type type = Collider::NULL_COLLIDER);
};

#endif /* StaticObject_h */
