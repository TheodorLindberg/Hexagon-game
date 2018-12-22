#include "HexagonGame.h"
#include <iostream>

void HexagonGame::update(float dt, sf::RenderWindow& window)
{
	if (CurrentSpawner.size() >= 1)
	{
		CurrentSpawner[0]->update(dt, *this, (int)m_map.GetLanes().size(), sf::Color(51, 102, 255));

		if (CurrentSpawner[0]->HasFinished)
		{
			delete CurrentSpawner[0];
			CurrentSpawner.erase(CurrentSpawner.begin());
		}
		
	}
	m_map.update(dt, *this);
	player.Update(*this, (sf::Vector2f)sf::Mouse::getPosition(window), dt);

}

void HexagonGame::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_map, states);
	target.draw(player, states);
}
