#pragma once
#include <SFML/Graphics.hpp>
class HexagonSpawner
{
public:
	virtual void update(float dt, class HexagonGame& game, int lanes, sf::Color spawnColor) = 0;
	bool HasFinished = false;
	int priority = 0;
};