#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <list>
#include "Bullet.h"


using namespace std;
using namespace sf;
class Tower
{
public:
	virtual Sprite getSprite() = 0;
	virtual bool collision(Vector2f v) = 0;
	virtual void setPosition(Vector2f p) = 0;
	virtual int getType() = 0;
	virtual void shoot(SzczerbiakBagienny& mob, Vector2f p, list<Bullet*>& b) = 0;
	virtual void draw(RenderWindow &window) = 0;
	virtual int getCost() = 0;
	
};

