#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
private:
	std::string m_textureId;
	int m_scale, m_tileSize;

public:
	Map(std::string textureId, int scale, int tileSize);
	~Map();
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void AddTile(int sourceX, int sourceY, int destX, int destY);
};

#endif