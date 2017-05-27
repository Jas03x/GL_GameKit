#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include "GL.h"
#include "GLM.h"
#include "OBJ_Loader.h"

namespace Light
{
	class PointLight
	{
	private:
		// global data:
		static GLuint _vao;
		static GLuint _vbo;
		static unsigned int _vertex_count;

	public:
		static void _init_system();
		static void _free_system();
		inline static void bindVAO() { glBindVertexArray(_vao); }
		inline static unsigned int getVertexCount() { return _vertex_count; }

		// local data:
		glm::vec3 position;
		glm::vec3 size;
		glm::vec3 color;

		PointLight(const glm::vec3& _position, const glm::vec3& _size, const glm::vec3& _color);
	};

	extern std::vector<PointLight> point_lights;

	void init_system();
	void insert(const PointLight& point_light);
	void free_system();
}

#endif