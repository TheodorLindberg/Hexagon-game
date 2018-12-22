#include "NormalHexagon.h"
#include "../../HexagonGame.h"
void NormalHexagon::update(float dt, HexagonGame & game, int lanes, sf::Color spawnColor)
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
			return;
		}
		
		timer -= timeBetweenSpawn;



		int OpenGate = rand() % (game.GetMap().GetPolygons().size());

		for (int i = 0; i < game.GetMap().GetPolygons().size(); i++)
		{
			if (i == OpenGate)
			{
				continue;
			}
			game.GetMap().GetLanes()[i].spawnQuad(100, speed, sf::Color::Red);
		}

	}

}
