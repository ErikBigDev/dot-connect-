#include <iostream>
#include <GLFW/glfw3.h>
#include "render.hpp"
#include "game.hpp"
#include "controls.hpp"



using namespace std;

#define windowWidth 750
#define windowHeight 750

GLFWwindow* window;


int main(int argc, char** argv){

	if (!glfwInit()) return -1;

	gameInit();

	window = glfwCreateWindow(windowWidth,windowHeight, "Dot Game", NULL, NULL);
	if(!window){
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowSizeLimits(window, windowWidth, windowHeight, windowWidth, windowHeight);
	glfwSetMouseButtonCallback(window,mouseButtonCallback);

	while (!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT);
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
};
