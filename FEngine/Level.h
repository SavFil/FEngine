#ifndef _LEVEL_H
#define _LEVEL_H

#include <vector>
#include "Tile.h"
#include "Player.h"
#include "TextureManager.h"
#include "rapidxml-1.13/rapidxml.hpp"

class Level
{
private:
	//A 2D array of Tile pointers
	std::vector<std::vector<Tile*> > map;
	std::vector<std::vector<Player*>> playerMap;

	//Width and height of level (in tiles)
	int w;
	int h;

	void SetDimensions(int w, int h);

public:
	Level(int w, int h);
	Level();
	~Level();

	void AddTile(int x, int y, Tile* tile);
	Tile* GetTile(int x, int y);

	void AddPlayer(int x, int y, Player* player);
	Player* GetPlayer(int x, int y);

	void LoadLevel(std::string filename, TextureManager& textureManager);


	int GetWidth();
	int GetHeight();
};

#endif
