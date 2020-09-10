#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <list>

using namespace std;
using namespace sf;
class Tower
{
public:
	virtual Sprite getSprite() = 0;
	virtual bool collision(Vector2f v) = 0;
		
	
};

