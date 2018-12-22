#include <SFML/Graphics.hpp>
#include <iostream>
#include "HexagonGame.h"
#include "HexagonGame/Calculators.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Super hexagons", sf::Style::Default, settings);

	HexagonGame game;
	
	sf::Clock c;

	window.setFramerateLimit(60);


	while (window.isOpen())
	{
		float dt = c.restart().asSeconds();
		std::cout << 1 / dt << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			dt = 0.00000001f;
		}


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Update
		{
			game.update(dt,window);
		}
		window.clear();
		//Draw
		{
			window.draw(game);
		}

		window.display();
	}
	return EXIT_SUCCESS;
}