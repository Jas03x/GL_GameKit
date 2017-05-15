//
//  ColladaLoader.cpp
//  Bobo
//
//  Created by Jas S on 2017-02-04.
//  Copyright © 2017 Jas S. All rights reserved.
//

#include "ColladaLoader.h"

ColladaLoader::ColladaLoader(const char* path, unsigned int parameters)
{
    Assimp::Importer* importer = new Assimp::Importer();
    const struct aiScene* scene = importer->ReadFile(path, aiProcess_Triangulate);
    
    std::vector<glm::vec3> _vertices;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec2> _uvs;
    
    for(unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        const struct aiMesh* mesh = scene->mMeshes[i];
        std::string name = std::string(mesh->mName.C_Str());
        // helper function
        auto find_node = [this, name]() -> float {
            for(unsigned int i = 0; i < mesh_names.size(); i++) {
                if(name == mesh_names[i])
                    return i;
            }
            // else not found:
            mesh_names.push_back(name);
            return mesh_names.size() - 1;
        };
        
        float node_index = find_node();
        glm::vec3& max = this->max_dimensions[name];
        glm::vec3& min = this->min_dimensions[name];
        
        for(unsigned int o = 0; o < mesh->mNumVertices; o++)
        {
            if(mesh->HasPositions()) {
                const aiVector3D* v = &mesh->mVertices[o];
                glm::vec3 vec;
                if(parameters & COLLADA_AXIS_SWAP)
                    vec = glm::vec3(v->x, v->z, -v->y);
                else
                    vec = glm::vec3(v->x, v->y, v->z);
                if(v->x > max.x) max.x = v->x;
                if(v->y > max.y) max.y = v->y;
                if(v->z > max.z) max.z = v->z;
                if(v->x < min.x) min.x = v->x;
                if(v->y < min.y) min.y = v->y;
                if(v->z < min.z) min.z = v->z;
                if(v->x > this->global_max.x) this->global_max.x = v->x;
                if(v->y > this->global_max.y) this->global_max.y = v->y;
                if(v->z > this->global_max.z) this->global_max.z = v->z;
                if(v->x < this->global_min.x) this->global_min.x = v->x;
                if(v->y < this->global_min.y) this->global_min.y = v->y;
                if(v->z < this->global_min.z) this->global_min.z = v->z;
                
                // OR
                /*
                if(glm::length(vec) > glm::length(max)) max = vec;
                if(glm::length(vec) < glm::length(min)) min = vec;
                if(glm::length(vec) > glm::length(this->global_max)) this->global_max = vec;
                if(glm::length(vec) > glm::length(this->global_min)) this->global_min = vec;
                */
                
                _vertices.push_back(vec);
            }
            if(mesh->HasNormals()) {
                const aiVector3D* v = &mesh->mNormals[o];
                glm::vec3 vec = glm::vec3(v->x, v->y, v->z);
                _normals.push_back(vec);
            }
            if(mesh->HasTextureCoords(0)) {
                const aiVector3D* v = &mesh->mTextureCoords[0][o];
                glm::vec2 vec = glm::vec2(v->x, v->y);
                _uvs.push_back(vec);
            }
        }
        if(mesh->HasFaces()) {
            for(unsigned int o = 0; o < mesh->mNumFaces; o++) {
                const aiFace* face = &mesh->mFaces[o];
                if(face->mNumIndices != 3) {
                    printf("Warning: Unsupported face index count of %i. Only 3 indices per face are supported. Skipping face.\n", face->mNumIndices);
                    continue;
                }
                for(unsigned int t = 0; t < 3; t++) {
                    this->vertices.push_back(_vertices.at(face->mIndices[t]));
                    this->normals.push_back(_normals.at(face->mIndices[t]));
                    this->uvs.push_back(_uvs.at(face->mIndices[t]));
                    this->node_indices.push_back(node_index);
                }
            }
        }
        _vertices.clear();
        _normals.clear();
        _uvs.clear();
    }
    
    for(unsigned int i = 0; i < scene->mNumMeshes; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        if(mesh->HasBones()) {
            glm::vec4* weights = new glm::vec4[mesh->mNumVertices]();
            glm::vec4* indices = new glm::vec4[mesh->mNumVertices]();
            unsigned int* counts = new unsigned int[mesh->mNumVertices]();
            for(unsigned int o = 0; o < mesh->mNumBones; o++) {
                const aiBone* bone = mesh->mBones[o];
                unsigned int bone_index = -1;
                for(unsigned int b = 0; b < this->bone_names.size(); b++) {
                    if(this->bone_names[b] == std::string(bone->mName.C_Str())) {
                        bone_index = b;
                        break;
                    }
                }
                if(bone_index == -1) {
                    glm::mat4 matrix;
                    memcpy(&matrix[0][0], &bone->mOffsetMatrix[0][0], sizeof(float) * 16);
                    this->bone_offsets[bone->mName.C_Str()] = glm::transpose(matrix);
                    bone_index = (unsigned int) this->bone_names.size();
                    this->bone_names.push_back(bone->mName.C_Str());
                }
                for(unsigned int w = 0; w < bone->mNumWeights; w++) {
                    const struct aiVertexWeight* weight = &bone->mWeights[w];
                    if(counts[weight->mVertexId] < 4) {
                        indices[weight->mVertexId][counts[weight->mVertexId]] = bone_index;
                        weights[weight->mVertexId][counts[weight->mVertexId]] = weight->mWeight;
                        counts[weight->mVertexId]++;
                    } else {
                        puts("Vertex limit of 4 bones per vertex exceeded. Terminating.");
                        throw -1;
                    }
                }
            }
            this->bone_weights.insert(this->bone_weights.end(), &weights[0][0], &weights[0][0] + mesh->mNumVertices * 4);
            this->bone_indices.insert(this->bone_indices.end(), &indices[0][0], &indices[0][0] + mesh->mNumVertices * 4);
            delete[] weights;
            delete[] indices;
            delete[] counts;
        }
    }
    for(unsigned int i = 0; i < scene->mNumAnimations; i++) {
        const aiAnimation* animation = scene->mAnimations[i];
        for(unsigned int n = 0; n < animation->mNumChannels; n++) {
            const aiNodeAnim* node_animation = animation->mChannels[n];
            Animation animation = Animation();
            for(unsigned int o = 0; o < node_animation->mNumPositionKeys; o++) {
                const aiVector3D translation = node_animation->mPositionKeys[o].mValue;
                const aiVector3D scale = node_animation->mScalingKeys[o].mValue;
                const aiQuaternion rotation = node_animation->mRotationKeys[o].mValue;
                animation.translations.push_back(glm::vec3(translation.x, translation.y, translation.z));
                animation.scales.push_back(glm::vec3(scale.x, scale.y, scale.z));
                animation.rotations.push_back(glm::vec4(rotation.x, rotation.y, rotation.z, rotation.w));
            }
            this->bone_animations[std::string(node_animation->mNodeName.C_Str())] = animation;
        }
    }
    memcpy(&this->inverse_root[0][0], &scene->mRootNode->mTransformation[0][0], sizeof(float) * 16);
    this->inverse_root = glm::inverse(this->inverse_root);
    this->process_nodes(scene->mRootNode);
    this->animation_length = (unsigned int) this->bone_animations.begin()->second.translations.size(); // assume all lengths equal
    delete importer;
}

glm::mat4 ColladaLoader::calculate_node(const aiNode* root) {
    glm::mat4 ret = glm::mat4(1.0f);
    const aiNode* node = root;
    while(node != NULL) {
        glm::mat4 mat;
        memcpy(&mat[0][0], &node->mTransformation[0][0], sizeof(float) * 16);
        ret = glm::transpose(mat) * ret;
        node = node->mParent;
    }
    return ret;
}

void ColladaLoader::process_nodes(const aiNode* node) {
    if(node == NULL) return;
    if(node->mParent != NULL) this->bone_parents[std::string(node->mName.C_Str())] = std::string(node->mParent->mName.C_Str());
    this->node_transforms[std::string(node->mName.C_Str())] = calculate_node(node);
    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        this->process_nodes(node->mChildren[i]);
    }
}
