
#include "../../HexagonGame.h"
#include "CircularSpawner.h"

void CircularSpawner::update(float dt, HexagonGame & game, int lanes, sf::Color spawnColor) 
{
	if (HasFinished)
	{
		return;
	}
	timer += dt;
	if (timer > timeBetweenSpawn)
	{
		if (nextlane > lanes - 1)
		{
			nextlane = 0;
			circletimes--;
			if (circletimes <= 0)
			{
				HasFinished = true;
			}
		}
		timer -= timeBetweenSpawn;
		game.GetMap().GetLanes()[nextlane].spawnQuad(100, speed, spawnColor);
		nextlane++;
	}
}
