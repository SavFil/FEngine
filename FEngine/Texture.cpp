#include "Texture.h"

Texture::Texture()
{
}

Texture::Texture(int x, int y, int width, int height, double angle, sf::Vector2f * center, sf::IntRect * clipRect)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->angle = angle;
	this->center = center;
	this->clipRect = clipRect;

}

Texture::~Texture()
{
}

void Texture::setX(int x)
{
	this->x = x;
}

void Texture::setY(int y)
{
	this->y = y;
}

int Texture::getX()
{
	return this->x;
}

int Texture::getY()
{
	return this->y;
}

int Texture::getWidth()
{
	return this->width;
}

int Texture::getHeight()
{
	return this->height;
}

void Texture::setClipRect(sf::IntRect * clipRect)
{
	this->clipRect = clipRect;
}

sf::IntRect * Texture::getClipRect()
{
	return this->clipRect;
}


