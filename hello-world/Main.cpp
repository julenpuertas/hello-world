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
#include "Rotation.h"

using namespace Engine;

static void windowwwwww()
{
	Rotation foo;
	foo.get_matrix();
	foo.rotate_over(0.f, Math::Axis::Z);

	foo.get_orientation();
	foo.get_orientation(Math::Axis::Z);
	foo.get_axis_angle();
	foo.get_euler_angles();
	foo.rotate_over(0.f, FVector3::RIGHT);

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
