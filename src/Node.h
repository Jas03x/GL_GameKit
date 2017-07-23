//
//  Node.h
//  CarDemo
//
//  Created by Jas S on 2017-07-22.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <string>

#include "Math3d.h"
#include "Transform.h"

class Node
{
public:
    std::string name;
    glm::mat4 matrix;
    Transform transform;
    
    Node(){}
    Node(const std::string& _name, const glm::mat4& _matrix = glm::mat4(1.0f), const Transform& _transform = Transform()) {
        this->name = _name;
        this->matrix = _matrix;
        this->transform = _transform;
    }
};

#endif /* Node_h */
