#pragma once

#include "../HexagonSpawner.h"

class _1_2 : public HexagonSpawner
{
public:
	_1_2(float timeBetweenSpawn, float speed, int circletimes)
		:
		timeBetweenSpawn(timeBetweenSpawn),
		speed(speed),
		circletimes(circletimes)
	{}
private:
	virtual void update(float dt, HexagonGame& game, int lanes, sf::Color spawnColor) override;
	float timeBetweenSpawn, speed;
	float timer = 0;

	int firstLane = 0;

	int circletimes;
};