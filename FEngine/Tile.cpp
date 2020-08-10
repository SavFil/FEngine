#include "Tile.h"
#include <iostream>


Tile::Tile(sf::Texture& image)
{
	baseSprite.setTexture(image);
}

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Draw(int x, int y, sf::RenderWindow * rw)
{
	// position the sprite
	baseSprite.setPosition(x, y);
	// draw to render window
	rw->draw(baseSprite);
}
