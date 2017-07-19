//
//  StaticMesh.h
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef StaticMesh_h
#define StaticMesh_h

#include <stdio.h>

#include <vector>

#include "GL.h"
#include "Mesh.h"
#include "Math3d.h"
#include "Texture.h"
#include "Transform.h"
#include "OBJ_Loader.h"

class StaticMesh : public Mesh
{
private:
    Texture texture;
    
protected:
    void load(const char* source, const char* texture, const glm::vec3& _scale = glm::vec3(1.0f));
    
public:
	StaticMesh(){}
    StaticMesh(const char* source, const char* texture, const glm::vec3& _scale = glm::vec3(1.0f)){ this->load(source, texture, _scale); }
    void destroy();
    
    inline const Texture& getTexture() const { return this->texture; }
};

#endif /* StaticMesh_h */
