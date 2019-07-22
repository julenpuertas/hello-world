#include "Transform.h"
#include "DynamicArray.h"
#include "String.h"
#include "Component.h"
#include <iostream>
#include "Hasheable.h"
#include "System.h"
#include "GameObject.h"
#include "Color.h"
#include <random>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Division.h"

static void windowwwwww()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		///* Swap front and back buffers */
		glfwSwapBuffers(window);

		///* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}

int main(int argc, char* argv[])
{
	return 0;
}
