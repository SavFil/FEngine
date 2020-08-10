#ifndef _ISOMETRICENGINE_H
#define _ISOMETRICENGINE_H

#include <SFML\Graphics.hpp>
#include <iostream>
class IsometricEngine
{
private:
	int tileSize;
	sf::Vector2f mapIsoScroll;
	sf::Vector2f map2DScroll;
	float mapIsoScrollSpeed;
	int mapHeight;
	int mapWidth;
	sf::Vector2f point;
	float zoomLevel;
	sf::Vector2f zoom;
public:
	IsometricEngine();
	IsometricEngine(int tileSize);
	~IsometricEngine();

	void SetMapSize(int width, int height);
	sf::Vector2f Convert2DToIso(sf::Vector2f point);
	sf::Vector2f ConvertIsoTo2D(sf::Vector2f point);
	sf::Vector2f GetTileCoordinates(sf::Vector2f point);
	void ChangeScrollVector(int x, int y);
	sf::Vector2f GetScrollVector();
	void SetScrollSpeed(int speed);
	int GetScrollSpeed();
	void Changemap2DScroll(int x, int y);
	void SetMap2DScroll(int x, int y);
	sf::Vector2f Getmap2DScroll();
	void ConvertIsoCamToCart(sf::Vector2f isoCamPos);
	void ConvertCartCamToIso(sf::Vector2f cartCamPos);
	void WriteCoords();

	float GetZoomLevel();
	void SetZoomLevel(float zoomLevel);
	sf::Vector2f GetZoom();

};

#endif
