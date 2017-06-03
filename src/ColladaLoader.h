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
	// vertex data
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
	std::vector<float> texture_indices; // the texture which each mesh uses (for multi-textured models)
    std::vector<float> bone_weights; // the weights of each bone
    std::vector<float> bone_indices; // the indices of each bone
    std::vector<float> node_indices; // the index into the world transform nodes
    
    // bone data:
    std::vector<std::string> mesh_names;
    std::vector<std::string> bone_names;
    std::map<std::string, std::string> bone_parents;
    std::map<std::string, Animation> bone_animations;
    std::map<std::string, glm::mat4> bone_offsets;
    std::map<std::string, glm::mat4> node_transforms;
	glm::mat4 inverse_root;
    
	// dimensional data
    glm::vec3 global_max, global_min;
    std::map<std::string, glm::vec3> max_dimensions;
    std::map<std::string, glm::vec3> min_dimensions;

	std::vector<std::string> textures;

    glm::mat4 calculate_node(const aiNode* root);
    void process_nodes(const aiNode* node);
    
public:
    ColladaLoader(const char* path, unsigned int parameters = 0);
    
    const std::vector<glm::vec3>& getVertices() const { return this->vertices; }
    const std::vector<glm::vec3>& getNormals() const { return this->normals; }
    const std::vector<glm::vec2>& getUVs() const { return this->uvs; }
	const std::vector<float>& getTextureIndices() const { return this->texture_indices; }
    const std::vector<float>& getBoneWeights() const { return this->bone_weights; }
    const std::vector<float>& getBoneIndices() const { return this->bone_indices; }
    const std::vector<float>& getNodeIndices() const { return this->node_indices; }
    
    const std::vector<std::string>& getMeshNames() const { return this->mesh_names; }
    const std::vector<std::string>& getBoneNames() const { return this->bone_names; }
    const std::map<std::string, std::string>& getBoneParents() const { return this->bone_parents; }
    const std::map<std::string, Animation>& getBoneAnimations() const { return this->bone_animations; }
    const std::map<std::string, glm::mat4>& getBoneOffsets() const { return this->bone_offsets; }
    const std::map<std::string, glm::mat4>& getNodeTransforms() const { return this->node_transforms; }
    
    glm::vec3 getGlobalDimensions() const { return this->global_max - this->global_min; }
    const glm::vec3& getMaxDimensions(const std::string& name) const { return this->max_dimensions.at(name); }
    const glm::vec3& getMinDimensions(const std::string& name) const { return this->min_dimensions.at(name); }
    glm::vec3 getDimensions(const std::string& name) {
        glm::vec3 m = glm::vec3(this->node_transforms.at(name) * glm::vec4(this->min_dimensions.at(name), 1));
        glm::vec3 M = glm::vec3(this->node_transforms.at(name) * glm::vec4(this->max_dimensions.at(name), 1));
        return M - m;
        
        //glm::vec3 m = this->min_dimensions.at(name);
        //glm::vec3 M = this->max_dimensions.at(name);
        //return glm::vec3(this->node_transforms.at(name) * glm::vec4(M - m, 1));
    }
    
    const glm::mat4& getInverseRoot() const { return this->inverse_root; }
	const std::vector<std::string>& getTextures() const { return this->textures; }
    
    inline void toBuffer(std::vector<float>& buffer) const
    {
        buffer.clear();
        buffer.reserve(this->vertices.size() * 8);
        for(unsigned int i = 0; i < this->vertices.size(); i++) {
            buffer.insert(buffer.end(), &this->vertices.at(i)[0], &this->vertices.at(i)[0] + 3);
            buffer.insert(buffer.end(), &this->normals.at(i)[0], &this->normals.at(i)[0] + 3);
            buffer.insert(buffer.end(), &this->uvs.at(i)[0], &this->uvs.at(i)[0] + 2);
        }
    }
};

#endif /* ColladaLoader_hpp */
