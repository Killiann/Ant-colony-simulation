#pragma once
#include <SFML/Graphics.hpp>
#include "Phermone.h"

class Ant
{
	sf::Vector2f position;	
	sf::RectangleShape sprite;
	sf::Color antColor = sf::Color::Black;
	sf::Vector2f size = sf::Vector2f(6, 2);	
	
	//ant data
	const float speed = 1.5f;
	const float randomiseAmount = 16.f;
	float heading = 45.0f;
	float desiredDirection = 0.f;		
	
	//map data
	std::vector<std::vector<int>> mapData;
	int mapPixelSize;

	//phermones
	int framesSincePhermone = 0;
	const int framesBetweenPhermones = 30;
	std::vector<Phermone> homePhermones;
public:	
	Ant(sf::Vector2f pos, std::vector<std::vector<int>> md, int ps);

	void Update();
	void Draw(sf::RenderTarget& window);
	float MinRotation(float, float);

	inline sf::Vector2f GetPosition() { return position; }
	inline float GetHeading() { return heading; }
};

