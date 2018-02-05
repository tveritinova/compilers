#ifndef POSITION_H
#define POSITION_H

struct Position {

	Position() {}
	Position(const Position &) = default;
	Position(const int _x, const int _y): x(_x), y(_y) {}

	Position& operator= (const Position&) = default;

	int x;
	int y;
};

#endif //POSITION_H