#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "map.h"

class MapContainer {
	std::vector<Map> allMaps;
	int currentMapIndex;
	int width;
	int height;
public:
	MapContainer(std::string fileName);
	Map currentMap();
	void nextMap();
	void previousMap();
	int getWidth();
	int getHeight();
};