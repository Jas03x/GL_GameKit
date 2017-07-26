//
//  VectorTree.cpp
//  CarDemo
//
//  Created by Jas S on 2017-07-24.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "VectorTree.h"

VectorTree::VectorTree()
{
    this->id = 0;
    this->size = 0;
    this->root = NULL;
}

VectorTree::~VectorTree()
{
    if(this->root) delete this->root;
}

int VectorTree::insert(const glm::vec3& vec)
{
    if(this->root == NULL) this->root = new VectorNode(NULL, vec.x);
    VectorNode* vn = this->root->insert(vec.x, vec.y, vec.z);
    if(vn->id == -1) {
        vn->id = this->id;
        this->id_map[this->id] = vn;
        this->id ++;
        this->size ++;
    }
    return vn->id;
}

void VectorTree::toArray(std::vector<glm::vec3>& array)
{
    array.reserve(this->size);
    for(unsigned int i = 0; i < this->size; i++) {
        const VectorNode* node = this->id_map[i];
        array.push_back(glm::vec3(node->parent->parent->value, node->parent->value, node->value));
    }
}

VectorNode::~VectorNode()
{
    if(this->left) delete this->left;
    if(this->right) delete this->right;
    if(this->next_component) delete this->next_component;
}

VectorNode* VectorNode::insert(const float x, const float y, const float z)
{
    if(x == this->value) {
        if(this->next_component == NULL) this->next_component = new VectorNode(this, y);
        return this->next_component->insert(y, z);
    }
    else if(x < this->value) { // insert left
        if(this->left == NULL) this->left = new VectorNode(this->parent, x);
        return this->left->insert(x, y, z);
    }
    // else insert right
    if(this->right == NULL) this->right = new VectorNode(this->parent, x);
    return this->right->insert(x, y, z);
}

VectorNode* VectorNode::insert(const float y, const float z)
{
    if(y == this->value) {
        if(this->next_component == NULL) this->next_component = new VectorNode(this, z);
        return this->next_component->insert(z);
    }
    else if(y < this->value) { // insert left
        if(this->left == NULL) this->left = new VectorNode(this->parent, y);
        return this->left->insert(y, z);
    }
    // else insert right
    if(this->right == NULL) this->right = new VectorNode(this->parent, y);
    return this->right->insert(y, z);
}

VectorNode* VectorNode::insert(const float z)
{
    if(z == this->value)
        return this;
    else if(z < this->value) { // insert left
        if(this->left == NULL) this->left = new VectorNode(this->parent, z);
        return this->left->insert(z);
    }
    // else insert right
    if(this->right == NULL) this->right = new VectorNode(this->parent, z);
    return this->right->insert(z);
}

void VectorNode::inorder_traversal() const
{
    if(this->left) this->left->inorder_traversal();
    //print_components(this->value, this->next_component);
    if(this->next_component == NULL) {
        printf("%f %f %f\n", this->parent->parent->value, this->parent->value, this->value);
    } else {
        this->next_component->inorder_traversal();
    }
    if(this->right) this->right->inorder_traversal();
}
