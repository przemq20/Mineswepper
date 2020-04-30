#include "Coordinate.h"

Coordinate::Coordinate() {
	x = 0; y = 0;
}

Coordinate::Coordinate(int x, int y) : x(x), y(y) {}

Coordinate::Coordinate(const Coordinate& coordinate) {
	x = coordinate.getx();
	y = coordinate.gety();
}
