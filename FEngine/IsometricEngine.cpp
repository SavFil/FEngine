#include "IsometricEngine.h"

IsometricEngine::IsometricEngine()
{
}

IsometricEngine::IsometricEngine(int tileSize)
{
	this->tileSize = tileSize;
	this->mapHeight = 0;
	this->mapWidth = 0;
	mapIsoScroll = { 0, 0 };
	map2DScroll = { 0, 0 };
	mapIsoScrollSpeed = 2;
}

IsometricEngine::~IsometricEngine()
{
}

void IsometricEngine::SetMapSize(int width, int height)
{
	this->mapWidth = width;
	this->mapHeight = height;
}

sf::Vector2f IsometricEngine::Convert2DToIso(sf::Vector2f point)
{
	sf::Vector2f temp;

	temp.x = point.x - point.y;
	temp.y = (point.x + point.y) * 0.5;

	return temp;
}

sf::Vector2f IsometricEngine::ConvertIsoTo2D(sf::Vector2f point)
{
	sf::Vector2f temp;

	temp.x = (2 * point.y + point.x)*0.5;
	temp.y = (2 * point.y - point.x)*0.5;

	return temp;
}

sf::Vector2f IsometricEngine::GetTileCoordinates(sf::Vector2f point)
{
	sf::Vector2f temp;

	temp.x = (float)point.x / (float)tileSize;
	temp.y = (float)point.y / (float)tileSize;

	return (sf::Vector2f)temp;
}

void IsometricEngine::ChangeScrollVector(int x, int y)
{
	mapIsoScroll.x += x;
	mapIsoScroll.y += y;
}

sf::Vector2f IsometricEngine::GetScrollVector()
{
	return mapIsoScroll;
}

void IsometricEngine::SetScrollSpeed(int speed)
{
	mapIsoScrollSpeed = speed;
}

int IsometricEngine::GetScrollSpeed()
{
	return mapIsoScrollSpeed;
}

void IsometricEngine::Changemap2DScroll(int x, int y)
{
	map2DScroll.x += x;
	map2DScroll.y += y;
}

void IsometricEngine::SetMap2DScroll(int x, int y)
{
	sf::Vector2f tmp;
	tmp.x = x;
	tmp.y = y;

	map2DScroll = tmp;
}

sf::Vector2f IsometricEngine::Getmap2DScroll()
{
	return map2DScroll;
}

void IsometricEngine::ConvertCartCamToIso(sf::Vector2f cartCamPos)
{
	sf::Vector2f tmpPoint = cartCamPos;

	tmpPoint.x = tmpPoint.x * 2;

	if (tmpPoint.x < 0)
	{
		tmpPoint.x = abs(tmpPoint.x);

	}
	else if (tmpPoint.x > 0)
	{
		tmpPoint.x = -abs(tmpPoint.x);

	}
	tmpPoint = ConvertIsoTo2D(tmpPoint);

	mapIsoScroll = tmpPoint;


}

void IsometricEngine::WriteCoords()
{
	std::cout << "\r2D x: " << (int)map2DScroll.x
		<< " 2D y: " << (int)map2DScroll.y
		<< " Iso x: " << (int)mapIsoScroll.x
		<< " Iso y: " << (int)mapIsoScroll.y << "                  "
		<<  std::flush;
}

float IsometricEngine::GetZoomLevel()
{
	return zoomLevel;
}

void IsometricEngine::SetZoomLevel(float zoomLevel)
{
	this->zoomLevel = zoomLevel;
	this->zoom = { zoomLevel, zoomLevel };
}

sf::Vector2f IsometricEngine::GetZoom()
{
	return zoom;
}




void IsometricEngine::ConvertIsoCamToCart(sf::Vector2f isoCamPos)
{
	sf::Vector2f tmpPoint = GetScrollVector();

	tmpPoint = Convert2DToIso(tmpPoint);

	tmpPoint.x = tmpPoint.x / 2;

	if (tmpPoint.x < 0)
	{
		tmpPoint.x = abs(tmpPoint.x);

	}
	else if (tmpPoint.x > 0)
	{
		tmpPoint.x = -abs(tmpPoint.x);

	}

	map2DScroll = tmpPoint;
}
