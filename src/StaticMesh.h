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
#include "MeshLoader.h"
#include "MeshDescriptor.h"

#define STATIC_MESH_MAX_TEXTURE_COUNT 1

class StaticMesh : public Mesh
{
private:
    Texture texture;
    
protected:
    void construct(const MeshLoader& loader, const glm::vec3& _scale = glm::vec3(1.0f), const GLenum draw_mode = GL_STATIC_DRAW);
    
public:
	StaticMesh(){}
    void destroy();
    
    StaticMesh(const MeshDescriptor& descriptor) { this->construct(descriptor.getMeshLoader(), descriptor.getScale(), descriptor.getDrawMode()); }
    void operator = (const MeshDescriptor& descriptor) { this->construct(descriptor.getMeshLoader(), descriptor.getScale(), descriptor.getDrawMode()); }
    
    inline const Texture& getTexture() const { return this->texture; }
};

#endif /* StaticMesh_h */
