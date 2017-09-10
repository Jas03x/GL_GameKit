//
//  Collider.cpp
//  CarDemo
//
//  Created by Jas S on 2017-06-30.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "Collider.h"

Collider::Collider() {
    this->shape = NULL;
}

Collider::~Collider()
{
    if(this->shape) delete this->shape;
}
