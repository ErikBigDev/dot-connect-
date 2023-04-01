#ifndef GAME_HPP
#define GAME_HPP

class point{
private:
	int x , y, numOfConnections;
	point* connections[3];
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

struct line{
	int x1 , x2 ,y1 , y2;
	line(int xv1, int yv1, int xv2, int yv2){
		x1 = xv1, x2 = xv2 , y1 = yv1 , y2 = yv2;
	};
};


void gameInit();
void connect(point& p1, point& p2);
bool checkValidity (point& p1 , point& p2);

#endif
