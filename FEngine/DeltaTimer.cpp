#include "DeltaTimer.h"

DeltaTimer::DeltaTimer()
{
	this->clock = sf::Clock();
	this->deltaTime = 0;
	this->lastTick = 0;
	this->tick = 0;
}

DeltaTimer::~DeltaTimer()
{
}

void DeltaTimer::Update()
{
	// get previous tick 
	lastTick = tick;

	// get current tick
	tick = clock.getElapsedTime().asMilliseconds() / 10;
	// calculate delta time
	deltaTime = (tick - lastTick);
	
}

double DeltaTimer::GetDeltaTime()
{
	return deltaTime;
}
