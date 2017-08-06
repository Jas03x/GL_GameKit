//
//  DynamicMesh.cpp
//  BobosPuzzle
//
//  Created by Jas S on 2017-05-09.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "DynamicMesh.h"

void DynamicMesh::construct(const MeshLoader& loader, const glm::vec3& _scale, GLenum draw_mode)
{
    // open the asset
	if (loader.getTextures().size() == 0 || loader.getTextures().size() > DYNAMIC_MESH_MAX_TEXTURE_COUNT) {
		printf("Invalid texture count [%zu] in collada file [%s].\n", loader.getTextures().size(), loader.getPath().c_str());
		throw -1;
	}
    
    loader.genTextures(&this->textures);
    this->materials = loader.getMaterials();
    
    this->default_instance = DynamicMeshInstance(_scale);
    this->generateNodes(loader);
    
    size_t vc = loader.getFaces().size();
    
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<unsigned char> m_indices;
    loader.getDynamicVertexArray(vertices);
    loader.getNormalArray(normals);
    loader.getUvArray(uvs);
    loader.getMaterialArray(m_indices);
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, vc * (sizeof(float) * 12 + sizeof(unsigned char) * 7), NULL, draw_mode);
    
    size_t offset = 0;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 3,        &vertices[0][0]);                   offset += sizeof(float) * vc * 3;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 3,        &normals[0][0]);                    offset += sizeof(float) * vc * 3;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 2,        &uvs[0][0]);                        offset += sizeof(float) * vc * 2;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned char) * vc,    &m_indices[0]);                     offset += sizeof(unsigned char) * vc;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned char) * vc,    &loader.getTextureIndices()[0]);    offset += sizeof(unsigned char) * vc;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned char) * vc,    &loader.getNodeIndices()[0]);       offset += sizeof(unsigned char) * vc;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(float) * vc * 4,        &loader.getBoneWeights()[0][0]);    offset += sizeof(float) * vc * 4;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(unsigned char) * vc * 4, &loader.getBoneIndices()[0][0]);   offset += sizeof(unsigned char) * vc * 4;
    
    glEnableVertexAttribArray(0); // vertices
    glEnableVertexAttribArray(1); // normals
    glEnableVertexAttribArray(2); // uvs
    glEnableVertexAttribArray(3); // material ids
    glEnableVertexAttribArray(4); // texture ids
    glEnableVertexAttribArray(5); // node ids
    glEnableVertexAttribArray(6); // bone weights
    glEnableVertexAttribArray(7); // bone indices
    
    offset = 0;
    glVertexAttribPointer (0, 3, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 3;
    glVertexAttribPointer (1, 3, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 3;
    glVertexAttribPointer (2, 2, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 2;
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE,             0, (char*) NULL + offset);   offset += sizeof(unsigned char) * vc;
    glVertexAttribIPointer(4, 1, GL_UNSIGNED_BYTE,             0, (char*) NULL + offset);   offset += sizeof(unsigned char) * vc;
    glVertexAttribIPointer(5, 1, GL_UNSIGNED_BYTE,             0, (char*) NULL + offset);   offset += sizeof(unsigned char) * vc;
    glVertexAttribPointer (6, 4, GL_FLOAT,           GL_FALSE, 0, (char*) NULL + offset);   offset += sizeof(float) * vc * 4;
    glVertexAttribIPointer(7, 4, GL_UNSIGNED_BYTE,             0, (char*) NULL + offset);   offset += sizeof(unsigned char) * vc * 4;
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    this->texture_count = (unsigned int) loader.getTextures().size();
    this->vertex_count = (unsigned int) loader.getFaces().size();
}

void DynamicMesh::generateNodes(const MeshLoader& loader)
{
    // load the bones
    if(loader.getNodeNames().size() > DYNAMIC_MESH_MAX_NODE_COUNT || loader.getBoneNames().size() > DYNAMIC_MESH_MAX_BONE_COUNT) {
        printf("Collada file [%s] exceeds max bone/node limit.\n", loader.getPath().c_str());
        throw -1;
    }
    
    this->default_instance.nodes.reserve(loader.getNodeNames().size());
    for(unsigned int i = 0; i < loader.getNodeNames().size(); i++) {
        const std::string& name = loader.getNodeNames()[i];
        const glm::mat4& mat = loader.getNodeTransforms()[i];
        this->default_instance.nodes.push_back(Node(name, mat, Transform()));
        this->default_instance.node_map[name] = (unsigned int) this->default_instance.nodes.size() - 1;
    }
    
    this->default_instance.bones.reserve(loader.getBoneNames().size());
    
    // pass 1: set up the bones
    for(unsigned int i = 0; i < loader.getBoneNames().size(); i++)
    {
        const std::string& name = loader.getBoneNames()[i];
        
        // initalize the bone
        Bone bone = Bone(name);
        bone.node = &this->default_instance.nodes[default_instance.node_map.at(name)];
        bone.offset_matrix = loader.getBoneOffsets()[i];
        
        // load the bone's animation (if any)
        std::map<std::string, Animation>::const_iterator animation_it = loader.getBoneAnimations().find(name);
        if(animation_it != loader.getBoneAnimations().end()) bone.animation = animation_it->second;
        
        // append the bone
        this->default_instance.bones.push_back(bone);
        this->default_instance.bone_map[name] = (unsigned int) this->default_instance.bones.size() - 1;
    }
    
    // pass 2: set up the parents
    for(unsigned int i = 0; i < this->default_instance.bones.size(); i++)
    {
        const std::string& name = this->default_instance.bones[i].name;
        
        // try to get the parent bone
        std::map<std::string, std::string>::const_iterator parent = loader.getNodeParents().find(name);
        if(parent == loader.getNodeParents().end()) {
            this->default_instance.bones[i].parent = NULL;
            continue;
        }
        
        std::map<std::string, unsigned int>::const_iterator p = this->default_instance.bone_map.find(parent->second);
        if(p != this->default_instance.bone_map.end())
            this->default_instance.bones[i].parent = &this->default_instance.bones[p->second];
        else {
            printf("Warning: Parent of bone [%s] not found.\n", name.c_str());
            this->default_instance.bones[i].parent = NULL;
        }
    }
    
    this->inverse_root = loader.getInverseRoot();
}

void DynamicMesh::destroy()
{
    if(glIsBuffer(this->vbo) == GL_TRUE) glDeleteBuffers(1, &this->vbo);
    if(glIsVertexArray(this->vao) == GL_TRUE) glDeleteVertexArrays(1, &this->vao);
    
    for(unsigned int i = 0; i < this->texture_count; i++) this->textures[i].destroy();
    if(this->textures != NULL) delete[] this->textures;
    
    Mesh::destroy();
}
