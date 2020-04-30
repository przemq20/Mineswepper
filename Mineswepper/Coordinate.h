#pragma once
class Coordinate {
private:
	int x;
	int y;
public:
	Coordinate();
	Coordinate(int x, int y);
	Coordinate(const Coordinate& coordinate);
	int getx() const { return x; }
	int gety() const { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
};
