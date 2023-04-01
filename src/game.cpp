#include <ctime>
#include <random>
#include <vector>
#include "game.hpp"


#define pointNum 10
#define windowHeight 750


using namespace std;


void gameInit();
void handleClick(int x , int y);
line* getLines(int & len);
void connect(point& p1, point& p2);
bool checkValidity (point& p1 , point& p2); 


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
	connections[numOfConnections] = p;
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

	point** connections = p1.getConnections();

	for(int i = 0; i < 3 ; i++)
		if(connections[i] == &p2) return false;

	float k =(p1.getY() - p2.getY())/(p1.getX() - p2.getX());
	float b = p1.getY() - k*p1.getX();


	for(int i = 0 ; i < lines.size();i++){
		float nk = (lines[i].y1-lines[i].y2)/(lines[i].x1 - lines[i].x2);
		float b1 = lines[i].y1 - k*lines[i].x2;
		if(nk == k) continue;
		float x = (b1 - b)/(k - nk);
		if((abs(p1.getX() - p2.getX()) < abs(lines[i].x1 - lines[i].x2)) && ((x > p1.getX() && x < p2.getX()) || (x> p2.getX() && x < p1.getX()))) return false;
		if((abs(p1.getX() - p2.getX()) > abs(lines[i].x1 - lines[i].x2)) && ((x > lines[i].x1 && x < lines[i].x2) || (x> lines[i].x2 && x < lines[i].x1))) return false;
	};
	return true;
};
