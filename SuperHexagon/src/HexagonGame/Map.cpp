#include "Map.h"
#include "Calculators.h"
#include <math/Vec2.h>
#include <iostream>
#include "../HexagonGame.h"
HexagonMap::HexagonMap(sf::Vector2f center)
	:
	m_center(center)
{}

void HexagonMap::updateLanes(int lanes)
{
	m_lanes.resize(lanes);
	m_polygons = Calculator::CalculatePolygon(0, 0, lanes, 1);
	int Curlane = 1;
	for (auto& lane : m_lanes)
	{
		lane.updateLane(Curlane, *this);
		Curlane++;
	}
	sf::Color Ocolor = sf::Color::Red;
	sf::Color Icolor = sf::Color::Green;
	m_middleRing.clear();
	
	const float width = m_centerRadius - (m_centerInnerRadius);

	std::vector<sf::Vector2f> poly = Calculator::CalculatePolygon((int)m_center.x, (int)m_center.y, (int)lanes, (float)m_centerRadius );

	for (auto i = poly.begin(), end = poly.end() - 2;
		i != end; i++)
	{

		m_middleRing.push_back({{*(i + 1)}, Ocolor });
		Vec2 n0 = Vec2(*(i + 1) - *(i + 0)).CCW90().Normalize();
		Vec2 n1 = Vec2(*(i + 2) - *(i + 1)).CCW90().Normalize();
		Vec2 b = (n0 + n1).Normalize();
		const float k = width / (b * n0);
		Vec2 q = Vec2(*(i + 1)) + (b * k);
		m_middleRing.push_back({ {q.x, q.y},Ocolor });
	}
	{
		m_middleRing.push_back({ { poly.back() }, Ocolor });
		Vec2 n0 = Vec2(poly.back() - *(poly.end() - 2)).CCW90().Normalize();
		Vec2 n1 = Vec2(poly.front() - poly.back()).CCW90().Normalize();
		Vec2 b = (n0 + n1).Normalize();
		const float k = width / (b * n0);
		Vec2 q = Vec2(poly.back()) + (b * k);
		m_middleRing.push_back({ { q.x, q.y },Ocolor });
	}
	{
		m_middleRing.push_back({{poly.front()}, Ocolor });
		Vec2 n0 = Vec2(poly.front() - poly.back()).CCW90().Normalize();
		Vec2 n1 = Vec2(*(poly.begin() + 1) - poly.front()).CCW90().Normalize();
		Vec2 b = (n0 + n1).Normalize();
		const float k = width / (b * n0);
		Vec2 q = Vec2(poly.front()) + (b * k);
		m_middleRing.push_back({ { q.x, q.y},Ocolor });
	}

	m_middleRing.push_back(m_middleRing[0]);
	m_middleRing.push_back(m_middleRing[1]);

	
	
	m_middle.resize(lanes + 2);
	m_middle[0].position = m_center;
	m_middle[0].color = Icolor;

	for (std::size_t i = 1;i< m_middle.size() - 1; i++)
	{
		auto& vertex = m_middle[i];
		vertex.color = Icolor;
		vertex.position = m_polygons[i - 1] * m_centerInnerRadius + m_center;
	}
	m_middle[lanes + 1].color = Icolor;
	m_middle[lanes + 1].position = m_polygons[0] * m_centerInnerRadius + m_center;
}

void HexagonMap::updateColors(sf::Color middleRing, sf::Color middle, std::vector<sf::Color> lanes)
{
	m_middleColor = middle;
	m_middleRingColor = middleRing;
	for (auto& m : m_middleRing)
	{
		m.color = middleRing;
	}
	for (auto& m : m_middle)
	{
		m.color = middle;
	}
	if (lanes.size() == m_lanes.size())
	{
		int count = 0;
		for (auto& lane : m_lanes)
		{
			lane.updateColor(lanes[count]);
			count++;
		}
	}
	else
	{
		throw "BAD";
	}
}


void HexagonMap::update(float dt, HexagonGame& game)
{
	for (auto& lane : m_lanes)
	{
		lane.update(dt, *this);
	}
	
}

void HexagonMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(&m_middle.front(), m_middle.size(), sf::TrianglesFan, states);
	target.draw(&m_middleRing.front(), m_middleRing.size(), sf::TrianglesStrip, states);
	for (auto& lane : m_lanes)
	{
		target.draw(lane, states);
	}
}
