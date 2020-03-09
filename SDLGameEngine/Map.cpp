#include "Map.h"
#include <fstream>
#include "Game.h"
#include "EntityManager.h"
#include "TileComponent.h"

extern EntityManager g_entityManager;

Map::Map(std::string textureId, int scale, int tileSize) {
	m_textureId = textureId;
	m_scale = scale;
	m_tileSize = tileSize;
}

void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
	std::fstream mapFile;
	mapFile.open(filePath);
	
	char ch;
	int sourceRectY, sourceRectX;

	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {				// get a character from the file, that's the columns accross in the tileset. Get next character, that's the rows down.
			mapFile.get(ch);
			sourceRectY = atoi(&ch) * m_tileSize;
			
			mapFile.get(ch);
			sourceRectX = atoi(&ch) * m_tileSize;

			AddTile(sourceRectX, sourceRectY, x * m_tileSize*m_scale, y * m_tileSize*m_scale);
			mapFile.ignore();								// skip the ',' characters
		}
	}

	mapFile.close();
}


void Map::AddTile(int sourceX, int sourceY, int destX, int destY) {
	Entity& newTile(g_entityManager.AddEntity("Tile"));
	newTile.AddComponent<TileComponent>(sourceX, sourceY, destX, destY, m_tileSize, m_scale, m_textureId);
}