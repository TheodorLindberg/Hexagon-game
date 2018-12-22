#pragma once
#include "../HexagonSpawner.h"

class Delay : public HexagonSpawner
{
public:
	Delay(float delay)
		:
		delay(delay)
	{}
private:
	virtual void update(float dt, class HexagonGame& game, int lanes, sf::Color spawnColor) override
	{
		timer += dt;
		if (timer > delay)
		{
			HasFinished = true;
			return;
		}
	}
	float delay;
	float timer = 0;
};
