#include "Player.h"
#include <iostream>

Player::Player(sf::Texture & image)
{
	baseSprite.setTexture(image);
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Draw(int x, int y, sf::RenderWindow * rw)
{
	// position the sprite
	//std::cout << "x" << x << " y " << y << std::endl;
	baseSprite.setPosition(x, y);
	// draw to render window
	rw->draw(baseSprite);
}
