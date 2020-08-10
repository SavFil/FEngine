#ifndef _TILE_H
#define _TILE_H

#include <SFML\Graphics.hpp>

class Tile
{
private:
	sf::Sprite baseSprite;

public:
	Tile(sf::Texture& image);
	Tile();
	~Tile();

	void Draw(int x, int y, sf::RenderWindow* rw);
};

#endif
