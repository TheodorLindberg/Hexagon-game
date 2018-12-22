#include "1-2.h"
#include "../../HexagonGame.h"
void _1_2::update(float dt, HexagonGame & game, int lanes, sf::Color spawnColor)
{
	if (HasFinished)
	{
		return;
	}
	timer += dt;
	if (timer > timeBetweenSpawn)
	{
		circletimes--;
		if (circletimes <= 0)
		{
			HasFinished = true;
		}
		
		timer -= timeBetweenSpawn;
	
		for (int i = 0; i < lanes / 2; i++)
		{

			game.GetMap().GetLanes()[i * 2 + firstLane].spawnQuad(100, speed, spawnColor);
		}
		if (firstLane == 1)
		{
			firstLane = 0;
		}
		else
		{
			firstLane = 1;
		}
	}
}
