#ifndef _SOURCE_H
#define _SOURCE_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "TextureManager.h"
#include "Tile.h"
#include "Player.h"
#include "Camera.h"
#include "Level.h"
#include "IsometricEngine.h"
#include "DeltaTimer.h"
#include <string>


class  Source
{

private:

	// create  sfml window object
	sf::RenderWindow window;

	// create event object
	sf::Event evt;

	// create an image manager object
	TextureManager texManager;

	DeltaTimer deltaTimer;


	/* ************Temporary************ */
	sf::Sprite sprite, sprite2;
	sf::Texture texture, texture2;
	sf::IntRect textureClip, textureClip2;
	int loopColor = 0;
	IsometricEngine iso;
	sf::Vector2i mouseRect;
	sf::Vector2f mousePoint;


	sf::Vector2f charPoint;
	int charDirection;
	float charSpeed;
	//Camera camera;

	//Tile Dimensions
	int tileSize;
	sf::Vector2f tilePos;

	Level currentLevel;

	//Render Window (and Camera) size
	sf::Vector2f videoSize;

	bool mouseDown;
	int lastTileClicked;
	int gameMode;

	/* ********************************* */


	Tile* testTile;
	Tile* tile;
	Player* player;

public:
	 Source();
	 Source(int w, int h, int tileSize);
	~Source();

	//Main Game Loop
	void MainLoop();

	//Renders one frame
	void RenderFrame();

	//Processes user input
	void ProcessInput();

	//Updates all Engine internals
	void Update();

	void Start();

	//Temporary
	void DrawIsoMouse();
	void DrawIsoMap();
	sf::Vector2f GetMouseTilePosition();
	void GetMouseTileClick();
	/*void DrawSprite(sf::IntRect textureClip, sf::Vector2f point, float scale);*/
	void CenterMap(sf::Vector2f objectPoint);
	void CenterMapToTileUnderMouse();
	void DrawCharacter();
	void ScrollMapWithMouse();
};


#endif