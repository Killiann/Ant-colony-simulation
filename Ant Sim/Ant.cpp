#include "Ant.h"
#include "MathHelper.h"
#include "MapHandler.h"
#include <math.h>
#include <iostream>

Ant::Ant(sf::Vector2f pos,std::vector<std::vector<int>> md, int ps) : position(pos), mapData(md), mapPixelSize(ps){
	//init
	sprite.setSize(size);
	sprite.setFillColor(antColor);
	sprite.setOrigin(size.x / 2, size.y / 2);
	
	//set random starting heading + movement
	heading = (float)mh::Random(0,360);	
	desiredDirection = (float)mh::Random(0,360);
}

void Ant::Update() {
	//update desired direction randomly
	if (mh::Random(0, 15) == 1) desiredDirection += mh::Random(-3, 3) * randomiseAmount;
	desiredDirection = mh::NormaliseAngle(desiredDirection);

	//find closest rotation + apply
	float rotationNeeded = MinRotation(heading, desiredDirection);
	if (rotationNeeded != 0) heading += mh::Sgn(rotationNeeded) * 2.f;
	sprite.setRotation(heading - 90);

	//find next postition to handle collisions (using map grid data)
	float nextX = position.x - speed * cos(mh::DegToRadians(heading - 90));
	float nextY = position.y - speed * sin(mh::DegToRadians(heading - 90));
	if (mapData[nextY / mapPixelSize][nextX / mapPixelSize] == 1) {
		heading += 180;
		desiredDirection += 180;
	}

	//update position
	position.x = position.x - speed * cos(mh::DegToRadians(heading - 90));
	position.y = position.y - speed * sin(mh::DegToRadians(heading - 90));	
	sprite.setPosition(position);

	if (framesSincePhermone == framesBetweenPhermones) {
		framesSincePhermone = 0;
		Phermone p(position, false);
		homePhermones.push_back(p);
	}
	else framesSincePhermone++;
}

void Ant::Draw(sf::RenderTarget& window) {
	window.draw(sprite);
	for (int i = 0; i < homePhermones.size(); i++) {
		homePhermones[i].Update();		
	}
}

float Ant::MinRotation(float A, float B) {
	float D = B - A;
	if (D < -180)
		D = D + 360;
	else if (D > 180)
		D = D - 360;
	return D;
}
