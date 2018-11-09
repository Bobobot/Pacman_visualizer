#pragma once

class Map {
public:
	int currentTick;
	int currentDepth;
	std::vector<std::vector<char>> data;

	std::vector<char> operator[](int index) {
		return data[index];
	}

	int getWidth() {
		return data.size();
	}

	int getHeight() {
		return data[0].size();
	}
};