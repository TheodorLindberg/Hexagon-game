#pragma once


#include "../HexagonSpawner.h"

class NormalHexagon : public HexagonSpawner
{
public:
	NormalHexagon(float timeBetweenSpawn, float speed, int circletimes)
		:
		timeBetweenSpawn(timeBetweenSpawn),
		speed(speed),
		circletimes(circletimes)
	{}
private:
	virtual void update(float dt, HexagonGame& game, int lanes, sf::Color spawnColor) override;
	float timeBetweenSpawn, speed;
	float timer = 0;
	int nextlane = 0;
	int circletimes;
};

