#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
private:
	std::string m_textureId;
	unsigned int m_scale, m_tileSize, m_mapSizeX, m_mapSizeY;

public:
	Map(std::string textureId, int scale, int tileSize);
	~Map();
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY);
	void AddTile(int sourceX, int sourceY, int destX, int destY);
	unsigned int GetMapWidth();
	unsigned int GetMapHeight();
	unsigned int GetTileSize();
	unsigned int GetScale();
};

#endif