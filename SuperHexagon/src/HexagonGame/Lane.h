#pragma once
#include <SFML/Graphics.hpp>

class Lane : public sf::Drawable
{
public:
	struct Quad
	{
	public:
		sf::Vertex vertecis[4];
		float m_width;
		float m_dist; //  Distance to center;
		float m_speed; // Traveling speed towards the center
		void RecalculateVertecis(std::vector<sf::Vector2f>& polygons, int lane, sf::Vector2f & center);
		void setColor(sf::Color color);
	};
public:
	Lane();
	void update(float dt, class HexagonMap&);
	void updateLane(int newlane, HexagonMap&);
	void updateColor(sf::Color);
	void spawnQuad(float m_width, float m_speed, sf::Color color);
	std::vector<Quad>& GetQuads() { return quads; }
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	int lane;
	std::vector<Quad> quads;
	sf::Vertex m_background[4];
	sf::Color m_backgroundColor;
	
};