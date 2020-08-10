#ifndef _ENTITY_H
#define _ENTITY_H

#include <SFML/Graphics.hpp>


class Entity
{

private:
	sf::Uint32 id;	// A unique ID that tags each game - object as a separate item
	
	/*Each Uint32 can have 32 components (32 bits in 32bit integer)*/
	sf::Uint32 componentSet1; // first set of components
	//sf::Uint32 componentSet2; // second set of components (uncomment when needed)

public:

	Entity();
	~Entity();

};

#endif
