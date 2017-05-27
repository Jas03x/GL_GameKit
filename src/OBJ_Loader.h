//
//  OBJ_Loader.hpp
//  TunnelRun
//
//  Created by Jas S on 2016-12-21.
//  Copyright © 2016 Jas S. All rights reserved.
//

#ifndef OBJ_Loader_hpp
#define OBJ_Loader_hpp

#include <stdio.h>

#include <vector>

#include "GLM.h"
#include "File.h"

class OBJ_Loader
{
public:
	enum OBJ_Format
	{
		V,
		VN,
		VNT
	};

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<glm::uvec3> indices;

    bool read_objects(const char* path, OBJ_Format format);

public:
    OBJ_Loader(const char* obj_path, OBJ_Format format = VNT);

    const std::vector<glm::vec3>& getVertices() const { return this->vertices; }
    const std::vector<glm::vec3>& getNormals() const { return this->normals; }
    const std::vector<glm::vec2>& getUVs() const { return this->uvs; }
    const std::vector<glm::uvec3>& getIndices() const { return this->indices; }
};

#endif /* OBJ_Loader_hpp */
