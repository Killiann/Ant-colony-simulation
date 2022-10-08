#pragma once
#include <SFML/Graphics.hpp>

class Phermone
{
	sf::Vector2f position;
	bool toFood = false;

	sf::RectangleShape drawable;
	sf::Color c_food = sf::Color(159, 193, 49);
	sf::Color c_home = sf::Color(0, 92, 83);

	float strength = 1.f;

public:
	Phermone(sf::Vector2f pos, bool tf);
	void Update();
	void Draw(sf::RenderTarget& window);

	inline bool IsToFood() { return toFood; }
	inline float GetStrength() { return strength; }	
};

