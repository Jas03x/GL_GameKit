//
//  ColladaLoader.hpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef ColladaLoader_hpp
#define ColladaLoader_hpp

#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <map>

#include "Math3d.h"
#include "Bone.h"

#define COLLADA_AXIS_SWAP 0x01

class ColladaLoader
{
private:
    std::string path; // the path of this model
    
	// vertex data
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    std::vector<int> faces;
    
    // texture data:
    std::vector<std::string> textures;
    std::vector<unsigned char> texture_indices; // the texture which each mesh uses (for multi-textured models)
    
    // index data:
    std::vector<unsigned char> node_indices; // the index into the world transform nodes
    std::vector<glm::uvec4> bone_indices; // the indices of each bone
    std::vector<glm::vec4> bone_weights; // the weights of each bone
    
    // mesh information:
    std::vector<std::string> mesh_names;
    std::map<std::string, std::vector<int>> mesh_faces; // the faces of each mesh
    
    // node data:
    std::vector<std::string> node_names; // the names of the nodes
    std::map<std::string, std::string> node_parents; // bone hierchy
    std::map<std::string, glm::mat4> node_transforms; // matrices from the node hierchy
    
    // bone data:
    std::vector<std::string> bone_names;
    std::map<std::string, glm::mat4> bone_offsets; // bone offset matrices
    std::map<std::string, Animation> bone_animations;
    
    // misc:
    glm::mat4 inverse_root;
	
    // private helper functions:
    void process_nodes(const aiNode* node);
    glm::mat4 calculate_node(const aiNode* root);
    
    template<typename T>
    inline void genArray(const std::vector<T>& source, std::vector<T>& destination) const {
        destination.clear();
        destination.reserve(this->faces.size());
        for(unsigned int i = 0; i < this->faces.size(); i++) destination.push_back(source[i]);
    }
    
public:
    ColladaLoader(const char* _path, unsigned int parameters = 0);
    
    const std::string& getPath() const { return this->path; }
    
    const std::vector<glm::vec3>& getVertices() const { return this->vertices; }
    const std::vector<glm::vec3>& getNormals() const { return this->normals; }
    const std::vector<glm::vec2>& getUVs() const { return this->uvs; }
    void getVertexArray(std::vector<glm::vec3>& source) const { this->genArray<glm::vec3>(this->vertices, source); }
    void getNormalArray(std::vector<glm::vec3>& source) const { this->genArray<glm::vec3>(this->normals, source); }
    void getUvArray(std::vector<glm::vec2>& source) const { this->genArray<glm::vec2>(this->uvs, source); }
    const std::vector<int> getFaces() const { return this->faces; }
    
    const std::vector<std::string>& getTextures() const { return this->textures; }
    const std::vector<unsigned char>& getTextureIndices() const { return this->texture_indices; }
    
    const std::vector<unsigned char>& getNodeIndices() const { return this->node_indices; }
    const std::vector<glm::vec4>& getBoneWeights() const { return this->bone_weights; }
    const std::vector<glm::uvec4>& getBoneIndices() const { return this->bone_indices; }
    
    const std::vector<std::string>& getMeshNames() const { return this->mesh_names; }
    const std::vector<int>& getMeshFaces(const std::string& name) const { return this->mesh_faces.at(name); }
    
    const std::vector<std::string>& getNodeNames() const { return this->node_names; }
    const std::map<std::string, std::string>& getNodeParents() const { return this->node_parents; }
    const std::map<std::string, glm::mat4>& getNodeTransforms() const { return this->node_transforms; }
    
    const std::vector<std::string>& getBoneNames() const { return this->bone_names; }
    const std::map<std::string, glm::mat4>& getBoneOffsets() const { return this->bone_offsets; }
    const std::map<std::string, Animation>& getBoneAnimations() const { return this->bone_animations; }
    
    const glm::mat4& getInverseRoot() const { return this->inverse_root; }
    
    void removeVertexBones(const std::vector<int>& mesh_faces);
};

#endif /* ColladaLoader_hpp */
