#pragma once
#include <SFML/Graphics.hpp>
#include "math/Vec2.h"
#include "HexagonGame/Map.h"
#include "HexagonGame/Player.h"
#include "HexagonGame/Hexagon-Spawner/CircularSpawner.h"
#include "HexagonGame/Hexagon-Spawner/1-2.h"
#include "HexagonGame/Hexagon-Spawner/NormalHexagon.h"
#include "HexagonGame/Hexagon-Spawner/Delay.h"

class HexagonGame : public sf::Drawable, public sf::Transformable
{
public:
	enum class GameState
	{
		MainMenue = 0,
		Playing,
		PlayAgainMenue
	};
public:
	HexagonGame()
		:
		m_map(m_center)
	{
		m_gameState = GameState::MainMenue;
		InitGame();
	}
	void update(float dt, sf::RenderWindow& window);

	sf::View& GetView() { return view; }
	HexagonMap& GetMap() { return m_map; }
public:
	void InitGame()
	{
		m_map.updateLanes(6);
		m_map.updateColors(sf::Color(51, 102, 255), sf::Color::Blue, { sf::Color(0, 204, 255), sf::Color(0, 153, 255),sf::Color(0, 102, 255),sf::Color(0, 204, 255), sf::Color(0, 153, 255),sf::Color(0, 102, 255) });

		CurrentSpawner.emplace_back(new CircularSpawner{ 0.2f,500.0f,1 });
		CurrentSpawner.emplace_back(new NormalHexagon{ 0.7f,400.0f,5 });
		CurrentSpawner.emplace_back(new Delay{ 0.3f });
		CurrentSpawner.emplace_back(new CircularSpawner{ 0.19f,400.0f,2 });
		CurrentSpawner.emplace_back(new _1_2{ 0.8f,750.0f,5 });
		CurrentSpawner.emplace_back(new NormalHexagon{ 0.7f,400.0f,5 });
		CurrentSpawner.emplace_back(new Delay{ 0.3f });

		CurrentSpawner.emplace_back(new CircularSpawner{ 0.2f,700.0f,1 });
		CurrentSpawner.emplace_back(new NormalHexagon{ 0.7f,600.0f,5 });
		CurrentSpawner.emplace_back(new Delay{ 0.3f });
		CurrentSpawner.emplace_back(new CircularSpawner{ 0.19f,600.0f,2 });
		CurrentSpawner.emplace_back(new _1_2{ 0.8f,850.0f,5 });
		CurrentSpawner.emplace_back(new NormalHexagon{ 0.65f,600.0f,5 });

		CurrentSpawner.emplace_back(new Delay{ 0.3f });
		CurrentSpawner.emplace_back(new CircularSpawner{ 0.2f,800.0f,1 });
		CurrentSpawner.emplace_back(new NormalHexagon{ 0.7f,800.0f,5 });
		CurrentSpawner.emplace_back(new Delay{ 0.3f });
		CurrentSpawner.emplace_back(new CircularSpawner{ 0.19f,800.0f,2 });
		CurrentSpawner.emplace_back(new _1_2{ 0.8f,950,5 });
		CurrentSpawner.emplace_back(new NormalHexagon{ 0.65f,800.0f,5 });
	}
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
	sf::Vector2f m_center = {500,500};
	HexagonMap m_map;
	sf::View view;
	Player player;
	GameState m_gameState;
	std::vector<HexagonSpawner*> CurrentSpawner;
};