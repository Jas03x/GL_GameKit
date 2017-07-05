//
//  DynamicMesh.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DynamicMesh.h"

void DynamicMesh::load(const char* path, const glm::vec3& _scale, GLenum draw_mode)
{
    this->load(ColladaLoader(path), _scale, draw_mode);
}

void DynamicMesh::load(const ColladaLoader& loader, const glm::vec3& _scale, GLenum draw_mode)
{
    // open the asset
	if (loader.getTextures().size() <= 0 || loader.getTextures().size() > DYNAMIC_MESH_MAX_TEXTURE_COUNT) {
		printf("Invalid texture count [%lu] in collada file [%s].\n", loader.getTextures().size(), loader.getPath().c_str());
		throw -1;
	}
    
    // load the textures
    this->textures = new Texture[loader.getTextures().size()];
    std::string file_path = std::string(loader.getPath().c_str());
    file_path = file_path.substr(0, file_path.find_last_of("/\\") + 1);
    for(unsigned int i = 0; i < loader.getTextures().size(); i++)
    {
        std::string t_path = file_path + loader.getTextures()[i];
        this->textures[i] = Texture(t_path.c_str());
    }
    
    // load the bones
    if(loader.getNodeNames().size() > 16) {
        printf("Node count [%lu] exceeds limit [%i] in collada file [%s].\n", loader.getNodeNames().size(), DYNAMIC_MESH_MAX_NODE_COUNT, loader.getPath().c_str());
        throw -1;
    }
    this->bones.reserve(loader.getNodeNames().size());
    // pass 1: set up the bones
    for(unsigned int i = 0; i < loader.getNodeNames().size(); i++)
    {
        const std::string& name = loader.getNodeNames()[i];
     
        // initalize the bone
        Bone bone = Bone(name);
        bone.bind_pose_matrix = loader.getNodeTransforms().at(name);
        bone.transformation_matrix = glm::mat4(1.0f);
        
        // find the animation and offset matrix (if any)
        std::map<std::string, glm::mat4>::const_iterator offset_it = loader.getBoneOffsets().find(name);
        std::map<std::string, Animation>::const_iterator animation_it = loader.getBoneAnimations().find(name);
        if(offset_it != loader.getBoneOffsets().end()) bone.offset_matrix = offset_it->second;
        if(animation_it != loader.getBoneAnimations().end()) bone.animation = animation_it->second;
        
        // append the bone
        this->bones.push_back(bone);
        this->bone_map[name] = &this->bones.back();
    }
    // pass 2: set up the parents
    for(unsigned int i = 0; i < this->bones.size(); i++)
    {
        const std::string& name = this->bones[i].name;
        
        // try to get the parent bone
        std::map<std::string, std::string>::const_iterator parent = loader.getNodeParents().find(name);
        if(parent == loader.getNodeParents().end()) {
            this->bones[i].parent = NULL;
            continue;
        }
        
        std::map<std::string, Bone*>::const_iterator p = this->bone_map.find(parent->second);
        if(p != this->bone_map.end())
            this->bones[i].parent = p->second;
        else {
            printf("Warning: Parent of bone [%s] not found.\n", name.c_str());
            this->bones[i].parent = NULL;
        }
    }
    
    size_t vc = loader.getFaces().size();
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    loader.getVertexArray(vertices);
    loader.getNormalArray(normals);
    loader.getUvArray(uvs);
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vc * (sizeof(float) * 12 + sizeof(unsigned char) * 2 + sizeof(unsigned int) * 4), NULL, draw_mode);
    
    int offset = 0;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 3,        &vertices[0][0]);                   offset += sizeof(float) * vc * 3;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 3,        &normals[0][0]);                    offset += sizeof(float) * vc * 3;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 2,        &uvs[0][0]);                        offset += sizeof(float) * vc * 2;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned char) * vc,    &loader.getTextureIndices()[0]);    offset += sizeof(unsigned char) * vc;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned char) * vc,    &loader.getNodeIndices()[0]);       offset += sizeof(unsigned char) * vc;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 4,        &loader.getBoneWeights()[0][0]);    offset += sizeof(float) * vc * 4;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned int) * vc * 4, &loader.getBoneIndices()[0][0]);
    
    glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(1); // normals
    glEnableVertexAttribArray(2); // uvs
    glEnableVertexAttribArray(3); // texture ids
    glEnableVertexAttribArray(4); // node ids
    glEnableVertexAttribArray(5); // bone weights
    glEnableVertexAttribArray(6); // bone indices
    
    offset = 0;
    glVertexAttribPointer (0, 3, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 3;
    glVertexAttribPointer (1, 3, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 3;
    glVertexAttribPointer (2, 2, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 2;
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE,             0, (char*) NULL + offset);   offset += sizeof(unsigned char) * vc;
    glVertexAttribIPointer(4, 1, GL_UNSIGNED_BYTE,             0, (char*) NULL + offset);   offset += sizeof(unsigned char) * vc;
    glVertexAttribPointer (5, 4, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 4;
    glVertexAttribIPointer(6, 4, GL_UNSIGNED_INT,              0, (char*) NULL + offset);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->texture_count = (unsigned int) loader.getTextures().size();
    this->vertex_count = (unsigned int) loader.getFaces().size();
    
    this->scale = _scale;
    this->transformation = Transform();
    this->inverse_root = loader.getInverseRoot();
}

void DynamicMesh::destroy()
{
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
    
    for(unsigned int i = 0; i < this->texture_count; i++) this->textures[i].destroy();
    if(this->textures != NULL) delete[] this->textures;
}
