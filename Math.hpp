#pragma once
#include <iostream>


struct Vector2f
{

	Vector2f()
		:x(0.0f), y(0.0f)
	{}

	Vector2f(float stX, float stY)
		:x(stX), y(stY)
	{}

	void PrintVector()
	{
		std::cout << x << ", " << y << std::endl;
	}

	float x, y;

};

