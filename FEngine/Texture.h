#ifndef _TEXTURE_H
#define _TEXTURE_H


#include <iostream>
#include <SFML\Graphics.hpp>

class Texture
{
private:
	
	int x;
	int y;
	int width;
	int height;
	double angle;
	sf::Vector2f *center;
	sf::IntRect *clipRect;


public:

	Texture();
	Texture(int x, int y, int width, int height, double angle, sf::Vector2f *center, sf::IntRect *clipRect);
	~Texture();

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void setClipRect(sf::IntRect *clipRect);
	sf::IntRect *getClipRect();
};




#endif
