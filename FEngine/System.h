#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "Entity.h"
#include "SFML/Graphics.hpp"

//function pointers
typedef int(*systemInitFuncPointer)(void *scene);
typedef void(*systemUpdateFuncPointer)();
typedef void(*systemUpdateEntityFuncPointer)(sf::Uint32 entity);
typedef void(*systemFreeFuncPointer)();

enum SystemTypeE
{
	SYSTEM_NONE					   = 0, // no system
	SYSTEM_MOVE				   	   = 1, // system for moving entities
	SYSTEM_INPUT				   = 2, // system for handling input
	SYSTEM_RENDER_ISOMETRIC_WORLD  = 3, // system for rendering the isometric world
	SYSTEM_CONTROL_ISOMETRIC_WORLD = 4, // system for controlling the isometric world
	SYSTEM_CONTROL_ENTITY          = 5, // system for controlling entities

};

class System
{

private:

	SystemTypeE type;							// type of the system
	systemUpdateEntityFuncPointer UpdateEntity; // function pointer to run the system for an entity
	systemInitFuncPointer Init;					// function pointer to initialize the system
	systemUpdateFuncPointer Update;				// function pointer to update the system
	systemFreeFuncPointer	Free;				// function pointer to free memory allocated by the system


public:

	System();
	~System();

};

#endif
