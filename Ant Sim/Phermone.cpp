#include "Phermone.h"
Phermone::Phermone(sf::Vector2f pos, bool tf) : position(pos), toFood(tf) {	
	drawable = sf::RectangleShape(sf::Vector2f(1, 1));
	drawable.setPosition(position);
	drawable.setFillColor(toFood ? c_food : c_home);
}

void Phermone::Update() {
	strength -= 0.0001f;
	//drawable.setFillColor(sf::Color(c_home.r, c_home.g, c_home.b, 1.f-strength));
}

void Phermone::Draw(sf::RenderTarget& window) {		
	window.draw(drawable);
}