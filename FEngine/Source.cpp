#include "Source.h"
#include <math.h>
#include "Component.h"
#define MAP_WIDTH 16
#define MAP_HEIGHT 16

#define PLAYER_DIR_S 0
#define PLAYER_DIR_SE 1
#define PLAYER_DIR_E 2
#define PLAYER_DIR_NE 3
#define PLAYER_DIR_N 4
#define PLAYER_DIR_NW 5
#define PLAYER_DIR_W 6
#define PLAYER_DIR_SW 7

#define FREE_VIEW_MODE 0
#define OBJECT_FOCUS_MODE 1
#define NO_OF_GAME_MODES 2

const sf::Uint32 W_WIDTH = 1400, W_HEIGHT = 900;
const int testMap[MAP_WIDTH][MAP_HEIGHT] = {
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,3,3,3,1,4,4,4,4,4,1,3,3,3,3,2},
	{2,3,3,3,1,4,4,4,4,4,1,3,3,3,3,2},
	{2,3,3,3,1,4,4,4,4,4,1,3,3,3,3,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
	{2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2},
	{2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2},
	{2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2},
	{2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2},
	{2,5,5,5,5,5,5,5,5,5,5,5,5,5,5,2},
	{2,3,3,3,1,1,1,1,1,1,1,4,4,4,4,2},
	{2,3,3,3,1,1,1,1,1,1,1,4,4,4,4,2},
	{2,3,3,3,1,1,1,1,1,1,1,4,4,4,4,2},
	{2,3,3,3,1,1,1,1,1,1,1,4,4,4,4,2},
	{2,3,3,3,1,1,1,1,1,1,1,4,4,4,4,2},
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

Source::Source()
{
}

// Initializes the engine
Source::Source(int w, int h, int tileSize)
{
	videoSize = sf::Vector2f(w, h);
	this->tileSize = tileSize;

	// create and set window object
	window.create(sf::VideoMode(W_WIDTH, W_HEIGHT, 32), "FEngine", sf::Style::Default);
	window.setMouseCursorVisible(false);
	window.setMouseCursorGrabbed(true);
	sf::Mouse::setPosition(sf::Vector2i(W_WIDTH / 2 + window.getPosition().x, W_HEIGHT  / 2 + window.getPosition().y));
	//setPosition(sf::Vector2i(W_WIDTH, 4));
	// initialize texManager object and load level
	//texManager = TextureManager();
	iso = IsometricEngine(tileSize);
	texture.loadFromFile("res/images/tiles.png");
	sprite.setTexture(texture, false);
	texture2.loadFromFile("res/images/player.png");
	sprite2.setTexture(texture2, false);
	lastTileClicked = -1;
	iso.SetZoomLevel(1.0);
	charPoint = { 0, 0 };
	charDirection = PLAYER_DIR_S;
	charSpeed = 0.05;
	gameMode = FREE_VIEW_MODE;
	//currentLevel =  Level();
	//currentLevel.LoadLevel("res/xml/level.xml", texManager);
	deltaTimer = DeltaTimer();
}

void Source::MainLoop()
{
	while (window.isOpen())
	{
		ProcessInput();
		Update();
		RenderFrame();
	}
}

void Source::RenderFrame()
{
	window.clear(sf::Color(40, 40, 40, 255));
	DrawIsoMap();
	DrawCharacter();
	DrawIsoMouse();
	window.display();
}

void Source::ProcessInput()
{
	sf::Event evt;
	//Loop through all window events
	//if (evt.type == sf::Event::KeyPressed)
	//{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.x += charSpeed;
			charPoint.y += charSpeed;
			charDirection = PLAYER_DIR_S;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.x -= charSpeed;
			charPoint.y -= charSpeed;
			charDirection = PLAYER_DIR_N;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.y -= charSpeed;
			charDirection = PLAYER_DIR_NE;
			
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.x -= charSpeed;
			charDirection = PLAYER_DIR_NW;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.x += charSpeed;
			charPoint.y -= charSpeed;
			charDirection = PLAYER_DIR_E;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.x -= charSpeed;
			charPoint.y += charSpeed;
			charDirection = PLAYER_DIR_W;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.y += charSpeed;
			charDirection = PLAYER_DIR_SW;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			charPoint.x += charSpeed;
			charDirection = PLAYER_DIR_SE;
		}
		


		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			iso.Changemap2DScroll(0, iso.GetScrollSpeed());
			iso.ConvertCartCamToIso(iso.Getmap2DScroll());
			iso.WriteCoords();

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			iso.Changemap2DScroll(-iso.GetScrollSpeed(), 0);
			iso.ConvertCartCamToIso(iso.Getmap2DScroll());
			iso.WriteCoords();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			iso.Changemap2DScroll(0, -iso.GetScrollSpeed());
			iso.ConvertCartCamToIso(iso.Getmap2DScroll());
			iso.WriteCoords();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			iso.Changemap2DScroll(iso.GetScrollSpeed(),0);
			iso.ConvertCartCamToIso(iso.Getmap2DScroll());
			iso.WriteCoords();

		}*/
		
			
	//}

	while (window.pollEvent(evt))
	{
		// catch the resize events
		if (evt.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, evt.size.width, evt.size.height);
			window.setView(sf::View(visibleArea));
		}

		if (evt.type == sf::Event::Closed)
			window.close();

		if (evt.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			{
				gameMode = FREE_VIEW_MODE;

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
			{
				gameMode = OBJECT_FOCUS_MODE;

			}
		}


		if ((evt.type == sf::Event::MouseButtonPressed) && (mouseDown == false))
		{
			if (gameMode == FREE_VIEW_MODE)
			{
				CenterMapToTileUnderMouse();
			}
			if (gameMode == OBJECT_FOCUS_MODE)
			{
				GetMouseTileClick();
			}
			mouseDown = true;
		}
		if (evt.type == sf::Event::MouseButtonReleased)
			mouseDown = false;
		
		
		if (evt.type == sf::Event::MouseWheelMoved)
		{
			if (evt.mouseWheel.delta == 1)
			{
				if (iso.GetZoomLevel() < 3.0)
				{
					iso.SetZoomLevel(iso.GetZoomLevel() + 0.25);
					if (gameMode == FREE_VIEW_MODE)
					{
						CenterMap(tilePos);
					}
					if (gameMode == OBJECT_FOCUS_MODE)
					{
						CenterMap(charPoint);
					}
				}
			}
			else
			{
				if (iso.GetZoomLevel() > 1.0)
				{
					iso.SetZoomLevel(iso.GetZoomLevel() - 0.25);
					if (gameMode == FREE_VIEW_MODE)
					{
						CenterMap(tilePos);
					}
					if (gameMode == OBJECT_FOCUS_MODE)
					{
						CenterMap(charPoint);
					}
				}
			}
		}
	}
}



void Source::Update()
{
	
	mouseRect.x = sf::Mouse::getPosition(window).x / iso.GetZoomLevel();
	mouseRect.y = sf::Mouse::getPosition(window).y / iso.GetZoomLevel();

	if (gameMode == OBJECT_FOCUS_MODE)
	{
		CenterMap(charPoint);
	}
	else if (gameMode == FREE_VIEW_MODE)
	{
		ScrollMapWithMouse();
	}
	
	
	deltaTimer.Update();
	//camera.Update();
}



Source::~Source()
{

}

void Source::Start()
{
	MainLoop();
}


void Source::DrawIsoMap()
{
	int i, j, x, y;
	int tile; //contains one of the possible textures from a texture map
	sf::Vector2f point; // point to render a specific map tile

	// scale zoomLevel for left and top clip edge respectively
	int startX = -iso.GetZoomLevel() + (iso.Getmap2DScroll().x / iso.GetZoomLevel() / tileSize) * 2;
	int startY = -5* iso.GetZoomLevel() - (iso.Getmap2DScroll().y / iso.GetZoomLevel() / tileSize) * 2;

	int numTilesInWidth = (W_WIDTH / tileSize) / iso.GetZoomLevel();
	int numTilesInHeight = ((W_HEIGHT / tileSize) / iso.GetZoomLevel())*2;

	// scale zoomLevel for bottom and right clip edge respectively
	for (i = startY; i < startY + numTilesInHeight  +  3 * iso.GetZoomLevel(); i++)
	{
		for (j = startX; j < startX + numTilesInWidth + iso.GetZoomLevel(); j++)
		{
			// only draw if j and i are both even or odd
			if ((j & 1) != (i & 1))
			{
				continue;
			}

			x = (i + j) / 2;
			y = (i - j) / 2;
			
			if (x >= 0 && y >= 0 && x < MAP_WIDTH && y < MAP_HEIGHT)
			{
				tile = testMap[y][x]; 
				point.x = (x * iso.GetZoomLevel() * tileSize) + iso.GetScrollVector().x;
				point.y = (y * iso.GetZoomLevel() * tileSize) + iso.GetScrollVector().y;
				point = iso.Convert2DToIso(point);

				//temporary code
				switch (tile)
				{
				case 1:
					textureClip = { 63, 0, 62, 102 };
					break;
				case 2:
					textureClip = { 125, 0, 62, 102 };
					break;
				case 3:
					textureClip = { 187, 0, 62, 102 };
					break;
				case 4:
					textureClip = { 249, 0, 62, 102 };
					break;
				case 5:
					textureClip = { 311, 0, 62, 102 };
					break;
				}
				//*****************
				sprite.setPosition(point.x, point.y);
				sprite.setTextureRect(textureClip);
				sprite.setScale(iso.GetZoom());
				window.draw(sprite);

			}
		}
	}



	/*
	//loop through the map
	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			point.x = j * zoomLevel * tileSize + iso.GetScrollVector().x;
			point.y = i * zoomLevel * tileSize + iso.GetScrollVector().y;
			tile = testMap[i][j];
			point = iso.Convert2DToIso(point);
			//temporary code
			switch (tile)
			{
				case 1:
					textureClip = { 63, 0, 62, 102 };
					break;
				case 2:
					textureClip = { 125, 0, 62, 102 };
					break;
				case 3:
					textureClip = { 187, 0, 62, 102 };
					break;
				case 4:
					textureClip = { 249, 0, 62, 102 };
					break;
				case 5:
					textureClip = { 311, 0, 62, 102 };
					break;
			}
			//*****************
			sprite.setPosition(point.x, point.y);
			sprite.setTextureRect(textureClip);
			sprite.setScale(zoom);
			window.draw(sprite);
		}
	}*/
	
}

sf::Vector2f Source::GetMouseTilePosition()
{
	sf::Vector2f point, correct;
	sf::Vector2f tileShift, mouseIsoPoint;

	int modX = tileSize * iso.GetZoomLevel();
	int modY = tileSize * iso.GetZoomLevel();

	correct.x = ((int)iso.Getmap2DScroll().x % modX) * 2;
	correct.y = (int)iso.Getmap2DScroll().y % modY;

	mouseIsoPoint = mousePoint;
	mouseIsoPoint = iso.ConvertIsoTo2D(mousePoint);
	point = iso.GetTileCoordinates(mouseIsoPoint);
	tileShift = correct;
	tileShift = iso.Convert2DToIso(tileShift);

	if (iso.Getmap2DScroll().x > 0)
	{
		point.x -= ((float)iso.GetScrollVector().x + (float)tileShift.x) / (float)tileSize / iso.GetZoomLevel();
		point.x++;

	}
	else
	{
		point.x -= ((float)iso.GetScrollVector().x + (float)tileShift.x) / (float)tileSize / iso.GetZoomLevel();
	}

	if (iso.Getmap2DScroll().y > 0)
	{
		point.y -= ((float)iso.GetScrollVector().y - (float)tileShift.y) / (float)tileSize / iso.GetZoomLevel();
		point.y++;
	}
	else
	{
		point.y -= ((float)iso.GetScrollVector().y - (float)tileShift.y) / (float)tileSize / iso.GetZoomLevel();

	}

	return point;
}


void Source::DrawIsoMouse()
{
	sf::Vector2f correct;
	int modX = tileSize * iso.GetZoomLevel();
	int modY = tileSize * iso.GetZoomLevel();

	correct.x = ((int)iso.Getmap2DScroll().x % modX) * 2;
	correct.y = (int)iso.Getmap2DScroll().y % modY;

	mousePoint.x = ((int)mouseRect.x / tileSize)*tileSize;
	mousePoint.y = ((int)mouseRect.y / tileSize)*tileSize;

	if (((int)mousePoint.x / tileSize) % 2)
	{
		mousePoint.y += tileSize * 0.5;
	}

	sprite.setPosition(iso.GetZoomLevel() * mousePoint.x - correct.x - iso.GetZoomLevel(),
		iso.GetZoomLevel() * mousePoint.y + correct.y);
	textureClip = { 0, 0, 63, 102 };
	sprite.setTextureRect(textureClip);
	window.draw(sprite);
}

void Source::GetMouseTileClick()
{
	sf::Vector2f point = GetMouseTilePosition();

	if (point.x >= 0 && point.y >= 0 && point.x < MAP_WIDTH && point.y < MAP_HEIGHT)
	{
		lastTileClicked = testMap[(int)point.y][(int)point.x];
	}
	else
		lastTileClicked = -1;

	std::cout << "\rlastTileClicked: " << (lastTileClicked != -1 ? std::to_string(lastTileClicked) : "NO_TILE")
		<< ", point.x: " << (int)point.x
		<< " point.y " << (int)point.y
		<< std::flush;
}

void Source::CenterMap(sf::Vector2f objectPoint)
{
	sf::Vector2f tmpPos = objectPoint;

	// calculate the offset of the center of the screen

	int offsetX = W_WIDTH / iso.GetZoomLevel() / 2;
	int offsetY = W_HEIGHT / iso.GetZoomLevel() / 2;

	tilePos = objectPoint;
	
	tmpPos = iso.Convert2DToIso(tmpPos);
	
	iso.SetMap2DScroll(floor(tmpPos.x * iso.GetZoomLevel() / 2), -floor(tmpPos.y * iso.GetZoomLevel()));
	iso.Changemap2DScroll(-offsetX * iso.GetZoomLevel() / 2, offsetY * iso.GetZoomLevel());

	if ( gameMode == OBJECT_FOCUS_MODE)
	{ 
		// account for object width and height for correct center, temporary
		iso.Changemap2DScroll(sprite2.getTextureRect().width / 8 * iso.GetZoomLevel() -5, -sprite2.getTextureRect().height / 6 * iso.GetZoomLevel());
	}

	iso.ConvertCartCamToIso(iso.Getmap2DScroll());

}

void Source::CenterMapToTileUnderMouse()
{
	sf::Vector2f mouseIsoTilePos;
	
	// calculate the offset of the center of the screen

	int offsetX = W_WIDTH / iso.GetZoomLevel() / 2;
	int offsetY = W_HEIGHT / iso.GetZoomLevel() / 2;

	mouseIsoTilePos = GetMouseTilePosition();

	tilePos.x = mouseIsoTilePos.x * tileSize;
	tilePos.y = mouseIsoTilePos.y * tileSize;

	mouseIsoTilePos = iso.Convert2DToIso(mouseIsoTilePos);

	iso.SetMap2DScroll(mouseIsoTilePos.x * tileSize * iso.GetZoomLevel() / 2,
					   -(mouseIsoTilePos.y * tileSize * iso.GetZoomLevel()));

	iso.Changemap2DScroll(-offsetX * iso.GetZoomLevel() / 2, offsetY * iso.GetZoomLevel());
	iso.ConvertCartCamToIso(iso.Getmap2DScroll());

}

void Source::DrawCharacter()
{
	sf::Vector2f point;

	point.x = (int)(charPoint.x * iso.GetZoomLevel()) + iso.GetScrollVector().x;
	point.y = (int)(charPoint.y * iso.GetZoomLevel()) + iso.GetScrollVector().y;
	point = iso.Convert2DToIso(point);

	sprite2.setPosition(point.x, point.y);
	switch (charDirection)
	{
		
	case PLAYER_DIR_S:
		textureClip2 = { 0, 0, 92, 267 };
		break;
	case PLAYER_DIR_SE:

		textureClip2 = { 133, 0, 92, 267 };
		break;
	case PLAYER_DIR_E:
		textureClip2 = { 273, 0, 92, 267 };
		break;
	case PLAYER_DIR_NE:
		textureClip2 = { 405, 0, 92, 267 };
		break;
	case PLAYER_DIR_N: 
		textureClip2 = { 540, 0, 92, 267 };
		break;
	case PLAYER_DIR_NW:
		textureClip2 = { 670, 0, 92, 267 };
		break;
	case PLAYER_DIR_W:
		textureClip2 = { 805, 0, 92, 267 };
		break;
	case PLAYER_DIR_SW:
		textureClip2 = { 931, 0, 92, 267 };
		break;
	}


	sprite2.setTextureRect(textureClip2);
	sprite2.setScale((iso.GetZoom() / 4.0f));
	window.draw(sprite2);

}

void Source::ScrollMapWithMouse()
{
	int zoomEdgeX = W_WIDTH * iso.GetZoomLevel() - W_WIDTH;
	int zoomEdgeY = W_HEIGHT * iso.GetZoomLevel() - W_HEIGHT;
	
	if (mouseRect.x < 2)
	{
		iso.Changemap2DScroll(-iso.GetScrollSpeed() * deltaTimer.GetDeltaTime(), 0);
		iso.ConvertCartCamToIso(iso.Getmap2DScroll());
	}
	if (mouseRect.x > W_WIDTH - (zoomEdgeX/ iso.GetZoomLevel()) - 2)
	{
		iso.Changemap2DScroll(iso.GetScrollSpeed() * deltaTimer.GetDeltaTime(), 0);
		iso.ConvertCartCamToIso(iso.Getmap2DScroll());
	}
	if (mouseRect.y < 2)
	{
		iso.Changemap2DScroll(0, iso.GetScrollSpeed() * deltaTimer.GetDeltaTime());
		iso.ConvertCartCamToIso(iso.Getmap2DScroll());
	}
	if (mouseRect.y > W_HEIGHT- (zoomEdgeY / iso.GetZoomLevel()) - 2)
	{
		iso.Changemap2DScroll(0, -iso.GetScrollSpeed() * deltaTimer.GetDeltaTime());
		iso.ConvertCartCamToIso(iso.Getmap2DScroll());
	}
}

