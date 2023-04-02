#include <GLFW/glfw3.h>
#include "game.hpp"
#include "controls.hpp"
#include <vector>
#include <iostream>
#include <cmath>


using namespace std;

#define defaultRadius 10

extern vector<point> points;

#define notClicked -1

int clickX = notClicked;
int clickY = notClicked;
bool clicked = false;


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	static point* grabbed;
	point* attached = nullptr;

	if(button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS){
		clicked = false;
		return;
	};

	for(int i = 0 ; i < points.size();i++){
		int dx = xpos - points[i].getX();
		int dy = ypos - points[i].getY();

		if(sqrt(dx*dx+dy*dy) < defaultRadius) attached = &points[i];
	};

	if(attached == nullptr) {
		clicked = false;
		return;
	};
	
	if(action == GLFW_PRESS) {
		grabbed = attached,clicked = true; 
		clickX = xpos ; 
		clickY = ypos;
		return;
	};
	if(action == GLFW_RELEASE&& checkValidity(*grabbed,*attached)) {
		connect(*grabbed,*attached);
		clicked = false;
	};
	clicked = false;
};
