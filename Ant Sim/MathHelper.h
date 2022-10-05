#pragma once
#define _USE_MATH_DEFINES

#include <math.h>
#include <random>

namespace mh
{
	inline float DegToRadians(float degrees) { return degrees * M_PI / 180; }
	inline float RadToDegrees(float radians) { return radians * 180 / M_PI; }
	inline float Sgn(float val) { return val >= 0 ? 1.f : -1.f; }
	inline int Random(int min, int max) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(min, max);
		return distr(gen);
	}
	inline float NormaliseAngle(float angle) {
		float orientation = std::remainder(angle, 360);
		if (orientation < 0) orientation += 360.f;
		return orientation;
	}
};

