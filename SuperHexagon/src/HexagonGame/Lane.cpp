#include "Lane.h"
#include "Map.h"
#include <iostream>
Lane::Lane()
{
}

void Lane::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_background, 4, sf::Quads, states);

	
	for (auto& quad : quads)
	{
		target.draw(quad.vertecis, 4, sf::Quads, states);
	}
}

void Lane::update(float dt, HexagonMap& map)
{
	for (std::size_t i = 0; i < quads.size(); i++)
	{
		Quad& quad = quads[i];
		quad.m_dist -= quad.m_speed * dt;
		if (quad.m_dist < map.GetCenterRadius())
		{
			quad.m_width -= map.GetCenterRadius() - quad.m_dist;
			quad.m_dist = map.GetCenterRadius();
		}
		if (quad.m_width < 0)
		{
			quads.erase(quads.begin() + i);
		}
		
		quad.RecalculateVertecis(map.GetPolygons(), lane, map.GetCenter());
	}
}

void Lane::updateLane(int newlane, HexagonMap& map)
{
	lane = newlane;
	std::cout << (map.GetPolygons().size() - 1 >= lane ? lane : 0) << std::endl;
	m_background[0].position = map.GetPolygons()[lane - 1] * map.GetCenterRadius() + map.GetCenter();
	m_background[1].position = map.GetPolygons()[(map.GetPolygons().size() - 1 >= lane ? lane : 0)] * map.GetCenterRadius() + map.GetCenter();

	m_background[2].position = map.GetPolygons()[(map.GetPolygons().size() - 1 >= lane ? lane : 0)] * map.GetCenter().x * 2.0f + map.GetCenter();
	m_background[3].position = map.GetPolygons()[lane - 1] * map.GetCenter().x * 2.0f + map.GetCenter();

	for (auto& background : m_background)
	{
		background.color = m_backgroundColor;
	}

}

void Lane::updateColor(sf::Color color)
{
	m_backgroundColor = color;
	for (auto& background : m_background)
	{
		background.color = m_backgroundColor;
	}
}

void Lane::spawnQuad(float width, float speed, sf::Color color)
{
	Quad quad;
	quad.m_width = width;
	quad.m_speed = speed;
	quad.m_dist = 800;
	quads.emplace_back(quad);
}

void Lane::Quad::RecalculateVertecis(std::vector<sf::Vector2f>& polygons, int lane, sf::Vector2f & center)
{
	//The polygons is in unit vectors
	vertecis[0].position = sf::Vector2f{ polygons[lane - 1] * m_dist } +sf::Vector2f(center);
	vertecis[1].position = sf::Vector2f{ polygons[(polygons.size() - 1 >= lane ? lane : 0)] * m_dist } +sf::Vector2f(center);

	float dist = m_dist + m_width;
	vertecis[2].position = sf::Vector2f{ polygons[(polygons.size() - 1 >= lane ? lane : 0)] * dist } +sf::Vector2f(center);
	vertecis[3].position = sf::Vector2f{ polygons[lane - 1] * dist } +sf::Vector2f(center);

}

void Lane::Quad::setColor(sf::Color color)
{
	for (sf::Vertex& vertex : vertecis)
	{
		vertex.color = color;
	}
}
