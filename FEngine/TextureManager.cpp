#include "TextureManager.h"
#include <vector>

TextureManager::TextureManager()
{
	tileTexture = Texture(0, 0, 0, 0, 0, nullptr, nullptr);
}

TextureManager::~TextureManager()
{
}

// add image to the list
void TextureManager::AddTexture(sf::Texture& image, int id)
{
	textureList.push_back(image);
	
	//Map for pairing image ids and the image's index in imageList
	imageIDs[id] = textureList.size() - 1;
	
}



// retrieve image
sf::Texture& TextureManager::GetTexture(int index)
{
	return textureList[imageIDs[index]];
}

// add image to the list
void TextureManager::AddPlayerTexture(sf::Texture& image, int id)
{
	playerTextureList.push_back(image);

	//Map for pairing image ids and the image's index in imageList
	playerImageIDs[id] = playerTextureList.size() - 1;

}

// retrieve image
sf::Texture& TextureManager::GetPlayerTexture(int index)
{
	return playerTextureList[playerImageIDs[index]];
}


void TextureManager::LoadTileset(std::string filename)
{
	//Load the file
	std::ifstream inFile(filename);

	if (!inFile)
		throw "Could not load tileset: " + filename;

	//Dump contents of file into a string
	std::string xmlContents;

	//Blocked out of preference
	{
		std::string line;
		while (std::getline(inFile, line))
			xmlContents += line;
	}

	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');

	//Create a parsed document with &xmlData[0] which is the char*
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);

	//Get the root node
	rapidxml::xml_node<>* root = doc.first_node();

	//Some variables used in the following code
	std::string imagePath;
	sf::Texture tileTexture;

	//Go through each imagefile
	rapidxml::xml_node<>* texturefile = root->first_node("imagefile");
	while (texturefile)
	{
		//Get the image file we're parsing and load it
		imagePath = texturefile->first_attribute("path")->value();
		tileTexture.loadFromFile(imagePath);

		//Go through each tile
		rapidxml::xml_node<>* tile = texturefile->first_node("tile");
		while (tile)
		{
			//Get all the attributes
			int x = atoi(tile->first_attribute("x")->value());
			int y = atoi(tile->first_attribute("y")->value());
			int frames = atoi(tile->first_attribute("frames")->value());
			int id = atoi(tile->first_attribute("id")->value());
			
			
			
			//Copy the right tile image from tileset
			//sf::Image tileImage;
			
			//tileImage.create(tileSize, tileSize);
			
			//tileImage.copy(tileset, 0, 0, sf::IntRect(x * tileSize, y * tileSize, frames * tileSize, tileSize), true);
			
			//Add the image to our image list
			AddTexture(tileTexture, id);
			
			//Go to the next tile
			tile = tile->next_sibling();
		}

		//Go to the next imagefile
		texturefile = texturefile->next_sibling();
	}
}

void TextureManager::LoadPlayer(std::string filename)
{
	
	//Load the file
	std::ifstream inFile(filename);

	if (!inFile)
		throw "Could not load tileset: " + filename;

	//Dump contents of file into a string
	std::string xmlContents;

	//Blocked out of preference
	{
		std::string line;
		while (std::getline(inFile, line))
			xmlContents += line;
	}
	
	//Convert string to rapidxml readable char*
	std::vector<char> xmlData = std::vector<char>(xmlContents.begin(), xmlContents.end());
	xmlData.push_back('\0');
	
	//Create a parsed document with &xmlData[0] which is the char*
	rapidxml::xml_document<> doc;
	doc.parse<rapidxml::parse_no_data_nodes>(&xmlData[0]);
	
	//Get the root node
	rapidxml::xml_node<>* root = doc.first_node();

	//Some variables used in the following code
	std::string imagePath;
	sf::Texture playerTexture;
	//sf::Image playerset;

	//Go through each imagefile
	rapidxml::xml_node<>* texturefile = root->first_node("imagefile");

	while (texturefile)
	{
		//Get the image file we're parsing and load it
		imagePath = texturefile->first_attribute("path")->value();
		playerTexture.loadFromFile(imagePath);

		//Go through each tile
		rapidxml::xml_node<>* subpicture = texturefile->first_node("subpicture");
		while (subpicture)
		{
			//Get all the attributes
			int left = atoi(subpicture->first_attribute("left")->value());
			int top = atoi(subpicture->first_attribute("top")->value());
			int right = atoi(subpicture->first_attribute("right")->value());
			int bottom = atoi(subpicture->first_attribute("bottom")->value());
			int id = atoi(subpicture->first_attribute("id")->value());



			//Copy the right tile image from tileset
			//sf::Image tileImage;

			//tileImage.create(tileSize, tileSize);

			//tileImage.copy(tileset, 0, 0, sf::IntRect(x * tileSize, y * tileSize, frames * tileSize, tileSize), true);


			//Add the image to our image list
			AddPlayerTexture(playerTexture, id);
			
			//Go to the next tile
			subpicture = subpicture->next_sibling();
		}

		//Go to the next imagefile
		texturefile = texturefile->next_sibling();
	}

	
}




