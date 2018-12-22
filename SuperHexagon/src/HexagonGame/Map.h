#pragma once
#include <SFML/Graphics.hpp>
#include "Lane.h"
class HexagonMap : public sf::Drawable
{
public:
	HexagonMap(sf::Vector2f center);
	void updateLanes(int lanes);
	void updateColors(sf::Color middleRing, sf::Color middle, std::vector<sf::Color> lanes);
	void update(float dt,class HexagonGame& game);

	sf::Vector2f& GetCenter() { return m_center; }
	std::vector<sf::Vector2f>& GetPolygons() { return m_polygons; }
	float GetCenterRadius() { return m_centerRadius; }
	std::vector<Lane>& GetLanes() { return m_lanes; }
	void SpawnHexagon()
	{
		
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	std::vector<Lane> m_lanes;
	sf::Vector2f m_center;
	std::vector<sf::Vector2f> m_polygons;
	float m_centerRadius = 100;
	float m_centerInnerRadius = 80;
	
	std::vector<sf::Vertex> m_middleRing;
	std::vector<sf::Vertex> m_middle;
	sf::Color m_middleRingColor;
	sf::Color m_middleColor;
};