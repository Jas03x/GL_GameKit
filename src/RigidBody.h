//
//  RigidBody.h
//  CarDemo
//
//  Created by Jas S on 2017-07-02.
//  Copyright © 2017 Jas S. All rights reserved.
//

#ifndef RigidBody_h
#define RigidBody_h

#include "Collider.h"

class RigidBody
{
protected:
	btRigidBody* rigid_body;
    btDefaultMotionState* motion_state;
	Transform* transform_pointer;
	Collider* shape;
    
	void construct(Collider* collider, const Transform& transformation, Transform* t_pointer, const float mass, const glm::vec3& inertia);
    void bind();
    void unbind();
    
public:
    RigidBody(Transform* _transformation = NULL);
	RigidBody(Collider* collider, const Transform& transformation, Transform* t_pointer, const float mass, const glm::vec3& inertia);
    virtual ~RigidBody();

	inline void setTransformationPointer(Transform* ptr) { this->transform_pointer = ptr; }
	inline bool hasTransformationPointer() const { return this->transform_pointer != NULL; }
	inline void updateTransformationPointer() {
		btTransform transform = this->rigid_body->getWorldTransform();
		const btVector3& origin = transform.getOrigin();
		const btQuaternion& rotation = transform.getRotation();
		this->transform_pointer->translation = glm::vec3(origin.getX(), origin.getY(), origin.getZ());
		this->transform_pointer->rotation = glm::quat(rotation.getW(), rotation.getX(), rotation.getY(), rotation.getZ());
	}
	btRigidBody* getRigidBodyPointer() { return rigid_body; }

	void rotate(const glm::quat& rotation);
	void translate(const glm::vec3& translation);
	void transform(const glm::vec3& translation, const glm::quat& rotation);
};

class RigidBodyManager
{
private:
	static std::vector<RigidBody*> rigid_bodies;
	static btDiscreteDynamicsWorld* dynamics_world;

public:
	static void Initalize(btDiscreteDynamicsWorld* _dynamics_world) { dynamics_world = _dynamics_world; }
	static void addRigidBody(RigidBody* body);
	static void removeRigidBody(RigidBody* body);
	static void UpdateBodies();
};

#endif /* RigidBody_h */
