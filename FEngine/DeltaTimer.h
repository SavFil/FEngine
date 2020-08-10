#ifndef _DELTATIMER_H
#define _DELTATIMER_H

#include <SFML\Graphics.hpp>
#include <iostream>

class DeltaTimer
{

private:

	sf::Uint32 lastTick;
	sf::Uint32 tick;
	sf::Uint32 deltaTime;
	sf::Clock clock;

public:

	DeltaTimer();
	~DeltaTimer();
	
	void Update();
	double GetDeltaTime();
};

#endif
