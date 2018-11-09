#include "map_container.h"

MapContainer::MapContainer(std::string fileName) {
	std::ifstream inFile(fileName);
	std::string line;

	int currentTick;
	Map newMap;

	while (std::getline(inFile, line)) {
		if (line == "newtick") {
			std::getline(inFile, line);
			currentTick = std::stoi(line);
		} else if (line == "newmap") {
			newMap.currentTick = currentTick;
			std::getline(inFile, line);
			newMap.currentDepth = std::stoi(line);
		} else  if (line == "endmap") {
			allMaps.push_back(newMap);
			newMap.data.clear();
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

