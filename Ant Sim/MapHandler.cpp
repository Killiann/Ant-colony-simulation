#include "MapHandler.h"

MapHandler::MapHandler(int w, int h, int pSize) : width(w), height(h), pixelSize(pSize){	

	//fill map with walls (iteration 1)	
	for (int y = 0; y < height; y++) {
		std::vector<int> row(width);
		data.push_back(row);

		for (int x = 0; x < width; x++) {
			//set walls initial
			data[y][x] = mh::Random(0, 100) < initialWallChance ? 1 : 0;							

			//add border
			if (x == 0 || y == 0 || y == height - 1 || x == width - 1) 
				data[y][x] = 1;			
		}		
	}

	//next 4 iterations with extra rule 
	for (int i = 0; i < 4; i++) 
		Iterate();	

	//last 3 to smooth out
	for (int i = 0; i < 3; i++) 
		Iterate(false);		

	PurgeWithFlood();
	UpdateDrawable();
}

void MapHandler::Iterate(bool extraRule) {
	//cellular automata logic
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {	

			//count surrounding walls
			int wallcount = 0;
			for (int yi = y - 1; yi <= y + 1; yi++) 
				for (int xi = x - 1; xi <= x + 1; xi++) 
					if (yi != y || xi != x)
						if (data[yi][xi] == 1)
							wallcount++;							

			//if wall has 4 or more neighbours			
			data[y][x] = data[y][x] == 1 && wallcount >= 4 ? 1 : 0;			
			
			//if empty space has 5 or more neighbours								
			if (data[y][x] == 0) {
				if (extraRule)
					data[y][x] = wallcount >= 5 || wallcount == 0 ? 1 : 0;
				else
					data[y][x] = wallcount >= 5 ? 1 : 0;
			}
		}
	}
}

void MapHandler::PurgeWithFlood() {
	//copy wall data to exlude walls 
	for (int i = 0; i < data.size(); i++) 
		fillChecked.push_back(data[i]);

	//check all tiles until all caves are flooded
	for (int y = 1; y < height - 1; y++) {
		std::vector<int> row(width);
		for (int x = 1; x < width - 1; x++) {
			
			//find unchecked empty space
			if (data[y][x] == 0 && fillChecked[y][x] == 0) 
				FloodFrom(x, y);			
		}
	}

	//when complete with flooding all caves, find largest
	int largestCavernIndex = 0;
	for (int i = 0; i < floodedCaverns.size(); i++) 
		if (floodedCaverns[i].size() >= floodedCaverns[largestCavernIndex].size())largestCavernIndex = i;	

	//fill all but largest
	for (int i = 0; i < floodedCaverns.size(); i++) {
		if (i != largestCavernIndex) {
			for (int j = 0; j < floodedCaverns[i].size(); j++) {
				sf::Vector2f tile = floodedCaverns[i][j];
				data[tile.y][tile.x] = 1;
			}
		}
	}
	floodedCaverns.clear();
}

//flood region starting at x y pos
void MapHandler::FloodFrom(int x, int y) {
	std::vector<sf::Vector2f> floodedCave;
	std::queue<sf::Vector2f> tileQueue;
	tileQueue.push(sf::Vector2f(x, y));
	
	//basic flood alg
	while (!tileQueue.empty()) {
		sf::Vector2f tile = tileQueue.front();
		tileQueue.pop();
		if (fillChecked[tile.y][tile.x] == 1)
			continue;
		else {
			floodedCave.push_back(tile);
			fillChecked[tile.y][tile.x] = 1;
			tileQueue.push(sf::Vector2f(tile.x - 1, tile.y));
			tileQueue.push(sf::Vector2f(tile.x + 1, tile.y));
			tileQueue.push(sf::Vector2f(tile.x, tile.y - 1));
			tileQueue.push(sf::Vector2f(tile.x, tile.y + 1));			
		}
	}	
	floodedCaverns.push_back(floodedCave);
}

//update pixel vec for display
void MapHandler::UpdateDrawable() {
	drawable.clear();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (data[y][x] == 1) {
				//random color for cave wall
				int rnd = mh::Random(0, 2);
				sf::Color c;
				switch (rnd)
				{
				case(0): c = caveWall1; break;
				case(1): c = caveWall2; break;
				case(2): c = caveWall3; break;
				default:
					break;
				}				

				//vertex array setup for quicker drawing
				drawable.setPrimitiveType(sf::Quads);
				drawable.resize(width * height * 4);

				sf::Vertex* quad = &drawable[(x + y * width) * 4];				
				quad[0].color = c;
				quad[1].color = c;
				quad[2].color = c;
				quad[3].color = c;

				quad[0].position = sf::Vector2f(x * pixelSize, y * pixelSize);
				quad[1].position = sf::Vector2f((x + 1) * pixelSize, y * pixelSize);
				quad[2].position = sf::Vector2f((x + 1) * pixelSize, (y + 1) * pixelSize);
				quad[3].position = sf::Vector2f(x * pixelSize, (y + 1) * pixelSize);					
			}
		}
	}
}

void MapHandler::Draw(sf::RenderTarget& window) {
	window.draw(drawable);
}