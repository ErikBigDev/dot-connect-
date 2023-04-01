#include <GLFW/glfw3.h>
#include <cmath>
#include <math.h>
#include <vector>
#include "render.hpp"
#include "game.hpp"


#define defaultRadius 10
#define segmentNum 16 
#define windowHeight 750
#define windowWidth 750


using namespace std;

void display();
void drawCricle(int x, int y, int r);
void drawLine(int x1 , int y1, int x2 , int y2);


extern vector<point> points;
extern vector<line> lines;
extern int clickX;
extern int clickY;
extern bool clicked;
extern GLFWwindow* window;




void display(){

	double xpos,ypos;
	glfwGetCursorPos(window,&xpos,&ypos);

	if(clicked)drawLine((int)xpos, (int)ypos, clickX,clickY);

	for(int i = 0 ; i < points.size();i++)
		drawCricle(points[i].getX(), points[i].getY(), defaultRadius);
	for(int i = 0 ; i < lines.size(); i++)
		drawLine(lines[i].x1 , lines[i].y1, lines[i].x2, lines[i].y2);
};



void drawCricle(int x, int y, int r){

	glBegin(GL_POLYGON);

	float cx = x - windowWidth/2;
	float cy = windowHeight/2 - y;
	float cr = r;
	cr = 2*cr/windowWidth;
	cx = 2*cx/windowWidth;
	cy = 2*cy/windowHeight;

	float angle = 0;
	float dAngle = 2*M_PI/segmentNum;


	for(int i = 0 ;i < segmentNum;i++){
		glVertex2f(cx+cr*cos(angle), cy+cr*sin(angle));
		angle+=dAngle;
	};

	glEnd();
};

void drawLine(int x1, int y1  ,int x2 , int y2){

	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINES);
	
	float cx1 = x1 ,cx2 = x2 , cy1= y1 , cy2 = y2;


	cx1 = cx1 - windowWidth/2;
	cx2 = cx2 - windowWidth/2;
	cy1 = windowHeight/2 - cy1;
	cy2 = windowHeight/2 - cy2;


	cx1 = 2*cx1/windowWidth;
	cy1 = 2*cy1/windowHeight;

	cx2 = 2*cx2/windowWidth;
	cy2 = 2*cy2/windowHeight;

	glVertex2f(cx1,cy1);
	glVertex2f(cx2,cy2);

	glEnd();
};
