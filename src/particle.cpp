#include <iostream>
#include <math.h>

#include <glm/gtc/matrix_transform.hpp>

#include "particle.h"

#define NUM_VERTICES 100

Particle::Particle(glm::vec2 _position,  glm::vec2 _size, glm::vec3 _color)
					:position(_position), size(_size),  color(_color)
{
	if (!VAO_initialized)
	{
		initialize_VAO();
	}

	velocity = glm::vec2(50.0f, 0.0f);
}

void Particle::initialize_VAO()
{
	float twoPi = 2 * M_PI;
	
	float vertices[NUM_VERTICES * 3];

	for (int i = 0; i < NUM_VERTICES; i++)
	{
		float angle = i * twoPi / NUM_VERTICES;

		vertices[(3 * i) + 0] = cos(angle);			// each vertex is 3 floats (i + 0, i + 1, i + 2)
		vertices[(3 * i) + 1] = sin(angle);
		vertices[(3 * i) + 2] = 0;
	}

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Particle::update(float delta_time)
{
	position += velocity * delta_time;

	if (position.x > 100 | position.x < -100)
		velocity.x = -velocity.x;
	
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, glm::vec3(position, 0.0f));
	model_mat = glm::scale(model_mat, glm::vec3(size, 1.0f));
}

void Particle::draw(Shader shader)
{
	shader.use();

	shader.setMat4("model", model_mat);
	
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);
}