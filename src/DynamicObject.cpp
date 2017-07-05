//
//  DynamicObject.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DynamicObject.h"

DynamicObject::DynamicObject()
{
}

void DynamicObject::destroy()
{
    DynamicMesh::destroy();
    if(this->collider) delete this->collider;
}
