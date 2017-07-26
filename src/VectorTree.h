//
//  VectorTree.h
//  CarDemo
//
//  Created by Jas S on 2017-07-24.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef VectorTree_h
#define VectorTree_h

#include <map>
#include <vector>
#include <stdio.h>

#include "Math3d.h"

struct VectorNode
{
    int id;
    float value;
    VectorNode* parent;
    VectorNode* left;
    VectorNode* right;
    VectorNode* next_component;
    
    VectorNode(VectorNode* p, const float val = 0)
    {
        this->id = -1;
        this->value = val;
        this->parent = p;
        this->left = NULL;
        this->right = NULL;
        this->next_component = NULL;
    }
    ~VectorNode();
    
    VectorNode* insert(const float x, const float y, const float z);
    VectorNode* insert(const float y, const float z);
    VectorNode* insert(const float z);
    void inorder_traversal() const;
};

class VectorTree
{
private:
    int id;
    size_t size;
    VectorNode* root;
    std::map<int, VectorNode*> id_map;
    
public:
    VectorTree();
    ~VectorTree();
    int insert(const glm::vec3& vec);
    void toArray(std::vector<glm::vec3>& array);
    const VectorNode* getRoot() const { return this->root; }
};

#endif /* VectorTree_h */
