#ifndef _CAMERA_H
#define _CAMERA_H

#include <SFML\Graphics.hpp>
#include "Tile.h"

class Camera
{
private:
	//Absolute position of camera (number of
	//pixels from origin of level map)
	sf::Vector2f position;

	//Target position camera is moving towards
	sf::Vector2f target;

	//Size of camera
	sf::Vector2f size;

	//Speed of camera, a value between 0.0 and 1.0
	float speed;

public:
	Camera(int w, int h, float speed);
	Camera();
	~Camera();

	//Moves camera immediately to coordinates
	void Move(int x, int y);
	void MoveCenter(int x, int y);

	//Sets camera target
	void GoTo(int x, int y);
	void GoToCenter(int x, int y);

	//Updates camera position
	void Update();

	sf::Vector2f GetPosition() { return sf::Vector2f((int)position.x, (int)position.y); }

	//Helper function for retreiving camera's offset from
	//nearest tile
	sf::Vector2f GetTileOffset(int tileSize) { return sf::Vector2f((int)(position.x) % tileSize, (int)(position.y) % tileSize); }

	//Helper function for retreiving a rectangle defining
	//which tiles are visible through camera
	sf::IntRect GetTileBounds(int tileSize);
};

#endif
