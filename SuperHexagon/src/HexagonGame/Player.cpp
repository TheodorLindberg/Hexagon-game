#include "Player.h"
#include "Calculators.h"
#include "math/Rect.h"
#include "../HexagonGame.h"

Player::Player()
{
	player.setRadius(25);
	player.setOrigin({ -140,25 });
	player.setPosition(500, 500);
}

void Player::Update(HexagonGame& game, sf::Vector2f mousePos, float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{

		player.setPosition(mousePos);
		player.setOrigin({ 25,25 });
	}
	else
	{
		player.setPosition(500, 500);
		player.setOrigin({ -140,25 });
		float angle = float(atan2(500 - mousePos.y, 500 - mousePos.x) * 180 / M_PI - 180);
		angle += game.GetView().getRotation();
		player.setRotation(angle);
	}
	if (HandleCollision(game))
	{
		player.setFillColor(sf::Color::Magenta);
	}
	else
	{
		player.setFillColor(sf::Color::Blue);
	}
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(player,states);
}

bool Player::HandleCollision(HexagonGame& game)
{
	RectI objAABB(player.getGlobalBounds());

	auto playerpos = Vec2{ (float)objAABB.left,(float)objAABB.top } +Vec2{ (float)objAABB.GetWidth() / 2,(float)objAABB.GetHeight() / 2 };
	//std::cout << objAABB.top << ": " << player.getPosition().y << std::endl;
	Vec2 c = playerpos;

	const float r = player.getRadius();

	std::vector<Lane>&  lanes = game.GetMap().GetLanes();

	for (int t = 0; t < lanes.size(); t++)
	{
		for (auto& quad : lanes[t].GetQuads())
		{
			
			//if (quad.m_dist < m_distFromMiddle + 50)
			{

				Vec2 prev = { quad.vertecis[3].position.x, quad.vertecis[3].position.y };

				for(auto& vertex : quad.vertecis)
				{
					Vec2 cur = vertex.position;

					const RectI lineAABB(prev, cur);
					if (objAABB.Overlaps(lineAABB))
					{
						const std::vector< Vec2 > points = CalculateIntersectionPoints(c, cur, prev, r);
						if (points.size() != 0)
						{
							return true;
						}
					}
					prev = cur;
				}
			}
		}

	}
	return false;
}
