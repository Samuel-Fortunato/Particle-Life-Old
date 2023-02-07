#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"

class Particle
{
public:
	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;

	Particle(glm::vec2 _position,  glm::vec2 _size, glm::vec3 _color);
	static void initialize_VAO();
	void update(float delta_time);
	void draw(Shader shader);

private:
	inline static bool VAO_initialized;
	inline static unsigned int VAO, VBO;
	
	glm::vec2 velocity;

	glm::mat4 model_mat;
};
