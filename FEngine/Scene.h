#ifndef _SCENE_H
#define _SCENE_H

#include "Entity.h"
#include "Component.h"
#include "System.h"
#include "IsometricEngine.h"

#define NUM_INITIAL_SYSTEMS 1
#define NUM_INITIAL_ENTITIES 1

#define SCENE_NAME_LENGTH 100

class Scene
{

private:

	char name[SCENE_NAME_LENGTH];	// name of the scene
	Entity *entities;				// entities in the scene
	sf::Uint32 numEntities;         // current number of entities
	sf::Uint32 maxEntities;         // current max number of entities that has been allocated to the memory

	Component *components;			// the components available in the scene
	sf::Uint32 numComponents;         // current number of components
	sf::Uint32 maxComponents;         // current max number of components that has been allocated to the memory
		
	System *systems;				// the systems available in the scene
	sf::Uint32 numSystems;         // current number of systems
	sf::Uint32 maxSystems;         // current max number of systems that has been allocated to the memory

	int memAllocFailed;				//if a memory allocation failure has occured
	int systemInitFailed;			// if a system has failed to initialize
	int deleteScene;				// if the scene should be deleted and removed from memory
	int exitScene;					//if the user/player wants to exit the scene
	int consumeLessCPU;				//if the scene should use less cpu (sfml delay(1))

	int sceneHasInputMouseComponent; //if the scene has the mouse input component
	
	/*if there is no keyboard input provided by components, we add the ability to close the scene by pressing ESC
	or triggering the close event. */
	int sceneHasInputSystem;		 // if the scene has an input system
	int sceneHasInputKeyboadComponent; // if the scene has the keyboard input component
	int componentPointersReallocated; // if the components in the scene has been reallocated

	IsometricEngine *isoEngine;		// pointer to the isometric engine
public:

	Scene();
	~Scene();

	Scene *EcsSceneCreateNewScene(char *name);
	void EcsSceneFreeScene(Scene *scene);
	sf::Uint32 EcsSceneAddEntityToScene(Scene *scene, ComponentE componentE);


};

#endif
