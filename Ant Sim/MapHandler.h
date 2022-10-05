#pragma once
#include <vector>
#include <queue>
#include "SFML/Graphics.hpp"
#include "MathHelper.h"

class MapHandler
{
	//setup
	std::vector<std::vector<int>> data;
	int width, height, pixelSize;
	int initialWallChance = 48; //percentage 	

	//drawables
	sf::VertexArray drawable;
	sf::Color caveWall1 = sf::Color(87, 77, 83);
	sf::Color caveWall2 = sf::Color(82, 72, 77);
	sf::Color caveWall3 = sf::Color(77, 68, 71);		

	//flood fill
	std::vector<std::vector<int>> fillChecked;
	std::vector<std::vector<sf::Vector2f>> floodedCaverns;
	
	//generation
	void Iterate(bool withExtraRule = true);
	void UpdateDrawable();
	void PurgeWithFlood();
	void FloodFrom(int x, int y);

public:	
	MapHandler(int width, int height, int pixelSize);
	inline std::vector<std::vector<int>> GetData() { return data; }	
	void Draw(sf::RenderTarget& window);
};

