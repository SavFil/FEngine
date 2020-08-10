#ifndef _PLAYER_H
#define _PLAYER_H

#include <SFML\Graphics.hpp>

class Player
{
private:
	sf::Sprite baseSprite;

public:
	Player(sf::Texture& image);
	Player();
	~Player();

	void Draw(int x, int y, sf::RenderWindow* rw);
};

#endif


