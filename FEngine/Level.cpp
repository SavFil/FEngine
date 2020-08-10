#include <vector>
#include "Level.h"
#include "Tile.h"

Level::Level(int w, int h)
{
	SetDimensions(w, h);
	this->w = w;
	this->h = h;
}

Level::Level()
{
}

Level::~Level()
{

}

int Level::GetHeight()
{
	return h;
}

int Level::GetWidth()
{
	return w;
}

void Level::SetDimensions(int w, int h)
{
	//w rows
	map.resize(w);
	playerMap.resize(w);

	//Each row has h columns of null Tile pointers
	for (int i = 0; i < w; i++)
	{
		map.at(i).resize(h, 0);
		playerMap.at(i).resize(h, 0);
	}
}

void Level::AddTile(int x, int y, Tile* tile)
{
	map[x][y] = tile;
}

Tile* Level::GetTile(int x, int y)
{
	return map[x][y];
}

void Level::AddPlayer(int x, int y, Player* player)
{
	playerMap[x][y] = player;
}

Player* Level::GetPlayer(int x, int y)
{
	return playerMap[x][y];
}

void Level::LoadLevel(std::string filename, TextureManager& textureManager)
{
	//Loads a level from xml file
	//Load the file
	std::ifstream inFile(filename);

	if (!inFile)
		throw "Could not load tileset: " + filename;

	//Dump contents of file into a string
	std::string xmlContents;

	//Blocked out of preference
	{
		std::string line;
		while (std::getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	//Get the root node
	rapidxml::xml_node<>* root = doc.first_node();

	//Get level attributes
	int width = atoi(root->first_attribute("width")->value());
	int height = atoi(root->first_attribute("height")->value());

	//Resize level
	this->w = width;
	this->h = height;
	SetDimensions(width, height);

	//Load each necessary tileset
	rapidxml::xml_node<>* tileset = root->first_node("tileset");
	while (tileset)
	{
		std::string path = tileset->first_attribute("path")->value();
		//Load tileset
		textureManager.LoadTileset(path);
		//Go to next tileset
		tileset = tileset->next_sibling("tileset");
	}

	//Go through each tile
	rapidxml::xml_node<>* tile = root->first_node("tile");
	while (tile)
	{
		//Get all the attributes
		int x = atoi(tile->first_attribute("x")->value());
		int y = atoi(tile->first_attribute("y")->value());
		int baseid = atoi(tile->first_attribute("baseid")->value());

		std::string walkString = tile->first_attribute("walkable")->value();
		bool walkable = (walkString == "true") ? true : false;

		//Create the tile and add it to the level.
		Tile* newTile = new Tile(textureManager.GetTexture(baseid));
		//std::cout << "x: " << x << " y: " << y << std::endl;
		//std::cout << map[0][0]<< "ok" << std::endl;
		AddTile(x, y, newTile);
		
		//Go to the next tile
		tile = tile->next_sibling("tile");
	}
	
	//Load each necessary player
	rapidxml::xml_node<>* player = root->first_node("player");
	while (player)
	{
		std::string path = player->first_attribute("path")->value();
		//Get all the attributes
		int x = atoi(player->first_attribute("x")->value());
		int y = atoi(player->first_attribute("y")->value());
		int baseid = atoi(player->first_attribute("baseid")->value());
		//Load player
		textureManager.LoadPlayer(path);

		//Create the tile and add it to the level.
		Player* newPlayer = new Player(textureManager.GetPlayerTexture(baseid));
		//std::cout << "x: " << x << " y: " << y << std::endl;
		//std::cout << map[0][0]<< "ok" << std::endl;
		//std::cout << "x " << x << " y " << y << std::endl;
		AddPlayer(x, y, newPlayer);
		//std::cout << "baseid: " << baseid << std::endl;
		//Go to next player
		player = player->next_sibling("player");
	}
}

