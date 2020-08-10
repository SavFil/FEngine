#ifndef _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "rapidxml-1.13/rapidxml.hpp"
#include <SFML\Graphics.hpp>
#include "Texture.h"

class TextureManager
{
private:
	
	std::vector<sf::Texture> textureList, playerTextureList;
	std::map<int, int> imageIDs, playerImageIDs;

	Texture tileTexture;
	sf::IntRect * tilesRects[5];
	int tileSize;

public:
	TextureManager();
	~TextureManager();

	void setTileSize(int tileSize) 
	{ 
		this->tileSize = tileSize; 
	}

	void AddTexture(sf::Texture & image, int id);
	sf::Texture& GetTexture(int index);

	void AddPlayerTexture(sf::Texture & image, int id);
	sf::Texture& GetPlayerTexture(int index);

	//Loads tileset from xml format
	void LoadTileset(std::string filename);

	//Loads player from xml format
	void LoadPlayer(std::string filename);


};

#endif