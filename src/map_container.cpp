#include "map_container.h"

MapContainer::MapContainer(std::string fileName) {
	std::ifstream inFile(fileName);
	std::string line;

	int currentTick;
	Map newMap;

	inFile >> width;
	inFile >> height;

	inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (std::getline(inFile, line)) {
		if (line == "newtick") {
			std::getline(inFile, line);
			currentTick = std::stoi(line);
		} else if (line == "newmap") {
			newMap.currentTick = currentTick;
			std::getline(inFile, line);
			newMap.currentDepth = std::stoi(line);
		} else if (line == "newpath") {
			std::getline(inFile, line);
			std::istringstream iss(line);
			int x;
			Point p;
			while (iss >> x) {
				p.x = x;
				iss >> p.y;
				newMap.pacmanTiles.push_back(p);
			}
		} else  if (line == "endmap") {
			allMaps.push_back(newMap);
			newMap.data.clear();
			newMap.pacmanTiles.clear();
		} else {
			std::vector<char> charVector(line.begin(), line.end());
			newMap.data.push_back(charVector);
		}
	}

	currentMapIndex = 0;
}

Map MapContainer::currentMap() {
	return allMaps[currentMapIndex];
}

void MapContainer::nextMap() {
	if (currentMapIndex < allMaps.size() - 1) {
		currentMapIndex++;
	}
}

void MapContainer::previousMap() {
	if (currentMapIndex > 0) {
		currentMapIndex--;

	}
}

int MapContainer::getWidth() {
	return width;
}

int MapContainer::getHeight() {
	return height;
}

