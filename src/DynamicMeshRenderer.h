//
//  DynamicMeshRenderer.h
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef DynamicMeshRenderer_h
#define DynamicMeshRenderer_h

#include <stdio.h>

#include "Path.h"
#include "Camera.h"
#include "Shader.h"
#include "DynamicMesh.h"
#include "Framebuffer.h"

class _DynamicMeshRenderer : public Shader
{
private:
    GLuint textures[DYNAMIC_MESH_MAX_TEXTURE_COUNT];
    GLuint vertex_matrix;
	GLuint normal_matrix;

public:
    _DynamicMeshRenderer(){}
    void initalize();
    void bind();
    void render(const DynamicMesh& mesh);
    void destroy();
};

extern _DynamicMeshRenderer DynamicMeshRenderer;

#endif /* DynamicMeshRenderer_h */
