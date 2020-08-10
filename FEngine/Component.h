#ifndef _COMPONENT_H
#define _COMPONENT_H

// component types
/* each component is a bit flag in an Uint32
	the limit is 32 bits / Uint32
*/

enum ComponentE
{
	COMPONENT_TYPE_COUNT = 6,

	COMPONENT_SET1_RENDER2D = 1u << 0, // ...0000 0001
	COMPONENT_SET1_KEYBOARD = 1u << 1, // ...0000 0010
	COMPONENT_SET1_MOUSE    = 1u << 2, // ...0000 0100
	COMPONENT_SET1_POSITION = 1u << 3, // ...0000 1000
	COMPONENT_SET1_VELOCITY = 1u << 4, // ...0001 0000
	COMPONENT_SET1_NAMETAG  = 1u << 5,  //...0010 0000

};

class Component
{
private:

	ComponentE type;	// type of the component
	void *data;			// component data

public:

	ComponentE test();

};

#endif
