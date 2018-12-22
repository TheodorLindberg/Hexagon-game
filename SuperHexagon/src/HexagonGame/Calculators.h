#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#define M_PI           3.14159265358979323846  /* pi */
namespace Calculator
{
	static std::vector<sf::Vector2f> CalculatePolygon(int _cx, int _cy, int _sides, float _radius, float _startAngle = 0)
	{
		int cx = _cx;  //center x
		int cy = _cy;  //center y
		int n = _sides;   //number of sides
		float r = _radius;  //radius. Dist from center to a vertex

		double ang;
		double startAng;

		double centerAng = 2 * M_PI / n;

		startAng = M_PI * _startAngle / 180;

		if (_startAngle == 0) //none supplied
		{
			if (n % 2 == 1)
				startAng = M_PI / 2; //12 oclock
			else
				startAng = M_PI / 2 - centerAng / 2;
		}

		std::vector<sf::Vector2f> vertecis;
		vertecis.resize(n);
		for (int i = 0; i < n; i++)
		{
			ang = startAng + (i*centerAng);
			double vx = (cx + r * cos(ang));
			double vy = (cy - r * sin(ang));

			vertecis[i] = { (float)vx,(float)vy };
		}
		return vertecis;
	}
}
