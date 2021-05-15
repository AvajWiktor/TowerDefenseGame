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

class MapField
{
public:
	MapField(int x, int y, char type) 
	{
		//w zaleznosci od odczytanego typu pola, nastepuje przypisanie mu roli jaka bedzie pelnic
		switch (type) 
		{
			case '4': {_Direction = 4; break; } //w gore
			case '5': {_Direction = 5; break; } //w dol
			case '6': {_Direction = 6; break; } //w prawo
			case '7': {_Direction = 7; break; } //w lewo
			case '2': {_Direction = 2; break; } //wiezyczka
			case '8': {_Direction = 8; break; } //tancz
		}
		if (type == '2') 
		{
			_MapFieldTexture.loadFromFile("grafiki/tower.png");
		}
		else if (type == '8') 
		{
			_MapFieldTexture.loadFromFile("grafiki/dancing.png");
		}
		else 
		{
			_MapFieldTexture.loadFromFile("grafiki/kafelek.png");
		}

		_MapFieldSprite.setTexture(_MapFieldTexture);
		
		_MapFieldSprite.setOrigin(22, 24); //ustawienie "srodka ciezkosci" w faktycznym srodku elementu

		_MapFieldSprite.setPosition(x, y);	
	}
	int whatToDo() 
	{
		return _Direction;
	}
	Sprite getMapSprite() 
	{
		return _MapFieldSprite;
	}
	Vector2f getPosition() 
	{
		return _MapFieldSprite.getPosition();
	}
	void draw(RenderWindow& window) 
	{
		window.draw(_MapFieldSprite);
	}
	void place() 
	{
		if (_IsFree) 
		{
			_IsFree = false;
		}
	}
	bool collision(Vector2f p) 
	{
		if (_MapFieldSprite.getGlobalBounds().contains(p)) return true;
		else return false;
	}
	bool isFree() 
	{
		return _IsFree;
	}

private:
	bool _IsFree = true;
	Sprite _MapFieldSprite;
	Texture _MapFieldTexture;
	int _Direction=0;
};

