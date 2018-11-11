#pragma once

#include "point.h"

class Map {
public:
	int currentTick;
	int currentDepth;
	std::vector<std::vector<char>> data;
	std::vector<Point> pacmanTiles;
	std::vector<Point> ghostTiles;

	std::vector<char> operator[](int index) {
		return data[index];
	}

	int getWidth() {
		return data.size();
	}

	int getHeight() {
		return data[0].size();
	}

	void clear() {
		data.clear();
		pacmanTiles.clear();
		ghostTiles.clear();
	}
};