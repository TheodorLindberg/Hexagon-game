#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Player : public sf::Drawable
{
public:
	Player();
	void Update(class HexagonGame& map, sf::Vector2f mousePos, float dt);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool HandleCollision(class HexagonGame& game);

	sf::CircleShape player;

	float m_distFromMiddle = 100;
};