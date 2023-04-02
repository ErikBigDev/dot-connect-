#include <ctime>
#include <random>
#include <vector>
#include "game.hpp"
#include "render.hpp"
#include <algorithm>


#define pointNum 10
#define windowHeight 750


using namespace std;


void gameInit();
void handleClick(int x , int y);
line* getLines(int & len);
void connect(point& p1, point& p2);
bool checkValidity (point& p1 , point& p2); 
bool lineIntersect(line& l1 ,line& l2);
bool boundingBoxIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);


line* problematic1;
line* problematic2;
int seed;
vector<point> points;
vector<line> lines;


point::point(){};
point::point(int xv , int yv){
	x = xv;
	y = yv;
	numOfConnections = 0;
};

int point::getX() const{
	return x;
};

int point::getY() const{
	return y;
};

int point::getNumOfConnections() const{
	return numOfConnections;
}

void point::addConnection(point* p){
	connections[numOfConnections++] = p;
};

point** point::getConnections() {
	return connections;
};


void gameInit(){

	int seed = time(NULL);
	default_random_engine gr(seed);
	uniform_int_distribution<int> dist(10, windowHeight - 10);

	for(int i = 0 ; i < pointNum ; i++){
		point tmp(dist(gr),dist(gr));
		points.push_back(tmp);
	};

};

void connect(point& p1, point& p2){

	int x = (p1.getX() + p2.getX())/2;
	int y = (p1.getY() + p2.getY())/2;

	point p3(x,y);

	p3.addConnection(&p1);
	p3.addConnection(&p2);

	points.push_back(p3);
	
	p1.addConnection(&points[points.size() - 1]);
	p2.addConnection(&points[points.size() - 1]);

	line L1(p1.getX(), p1.getY(), x , y);
	line L2(x , y , p2.getX(), p2.getY());

	lines.push_back(L1);
	lines.push_back(L2);
};


bool checkValidity (point& p1 , point& p2){

	if(p1.getNumOfConnections() == 3 || p2.getNumOfConnections() == 3) return false;
	if(p1.getX() == p2.getX() && p1.getY() == p2.getY()) return false;


	point** connections = p1.getConnections();

	for(int i = 0; i < 3 ; i++)
		if(connections[i] == &p2) return false;

	line nl(p1.getX(),p1.getY() ,p2.getX(),p2.getY());

	vector<int> sharedCordIndex;

	for(int i = 0 ; i < lines.size();i++)
		if(nl.vert1 == lines[i].vert1 || nl.vert1 == lines[i].vert2 || nl.vert2 == lines[i].vert1 || nl.vert2 == lines[i].vert2) sharedCordIndex.push_back(i);


	int sharedCount = 0;

	for(int i = 0 ; i < lines.size();i++){
		line l = lines[i];

		if( sharedCordIndex.size() != 0 &&i == sharedCordIndex[sharedCount]){
			sharedCount++;
			continue;
		};

		if(lineIntersect(l,nl)){
			return false;
		};
	};

	return true;
};


bool lineIntersect(line& l1 ,line& l2){

	float x1 = l1.vert1.x , x2 = l1.vert2.x , x3 = l2.vert1.x , x4 = l2.vert2.x;
	float y1 = l1.vert1.y , y2 = l1.vert2.y , y3 = l2.vert1.y , y4 = l2.vert2.y;

	if(!boundingBoxIntersect(x1,y1,x2,y2,x3,y3,x4,y4)) return false;

	float den = ((x1 - x2)*(y3-y4)) - ((y1 - y2)*(x3-x4));
	
	if(den == 0) return false;

	float px = (((x1*y2-y1*x1)*(x3-x4))-((x1-x2)*(x3*y4-y3*x4)))/den;
	float py = (((x1*y2-y1*x1)*(y3-y4))-((y1-y2)*(x3*y4-y3*x4)))/den;
	
	double lx = min(min(x1,x2),min(x3,x4));
	double mx = max(max(x1,x2),max(x3,x4));    

	double ly = min(min(y1,y2),min(y3,y4));
	double my = max(max(y1,y2),max(y3,y4));

	if(px> lx && px < mx && py > ly && py < my){
		return true;
	};

	return false;
};

bool boundingBoxIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	// Determine the bounding boxes for the two rectangles
	float left1 = min(x1, x2);
	float right1 = max(x1, x2);
	float top1 = min(y1, y2);
	float bottom1 = max(y1, y2);
	float left2 = min(x3, x4);
	float right2 = max(x3, x4);
	float top2 = min(y3, y4);
	float bottom2 = max(y3, y4);
    
	// Check for intersection
	if (right1 < left2 || left1 > right2 || bottom1 < top2 || top1 > bottom2) {
		return false;
	}
	else {
		return true;
	}
};
