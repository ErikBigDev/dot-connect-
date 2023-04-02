#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>

class point{
private:
	int x , y, numOfConnections;
	point* connections[3] = {nullptr};
public:
	point();
	point(int xv ,int yv);
	~point() = default;
	int getX() const;
	int getY() const;
	int getNumOfConnections() const;
	point** getConnections();
	void addConnection(point* p);
};

struct vert{
	int x , y;
	friend bool operator==(const vert& lhs , const vert& rhs){
		return (lhs.x == rhs.x && lhs.y == rhs.y);
	};
};
struct line{
	vert vert1 , vert2;
	line(int xv1, int yv1, int xv2, int yv2){
		vert1.x = xv1, vert2.x = xv2 , vert1.y = yv1 , vert2.y = yv2;
	};
};


void gameInit();
void connect(point& p1, point& p2);
bool checkValidity (point& p1 , point& p2);

#endif
