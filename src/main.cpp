#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

float vertices[] = {
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	0.924, 0.383, 0.0,
	0.707, 0.707, 0.0,
	0.383, 0.924, 0.0,
	0.0, 1.0, 0.0,
	-0.383, 0.924, 0.0,
	-0.707, 0.707, 0.0,
	-0.924, 0.383, 0.0,
	-1.0, 0.0, 0.0,
	-0.924, -0.383, 0.0,
	-0.707, -0.707, 0.0,
	-0.383, -0.942, 0.0,
	0.0, -1.0, 0.0,
	0.383, -0.924, 0.0,
	0.707, -0.707, 0.0,
	0.942, -0.383, 0.0,
	1.0, 0.0, 0.0
};

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Particle-Life", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initalize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	
	Shader myShader = Shader("resources/shader.vert", "resources/shader.frag");

	unsigned int VBO, VAO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{		
		glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		myShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 18);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
	{
		if (glfwGetWindowMonitor(window) == NULL)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		}
		else
		{
			glfwSetWindowMonitor(window, NULL, 0, 0, 720, 480, GLFW_DONT_CARE);
		}
	}
}