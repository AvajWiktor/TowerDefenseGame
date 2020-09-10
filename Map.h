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

class Map
{

public:
	Map(int x, int y, char type) {

		//w zaleznosci od odczytanego typu pola, nastepuje przypisanie mu roli jaka bedzie pelnic
		switch (type) {
		case '4': {_Direction = 4; break; } //w gore
		case '5': {_Direction = 5; break; } //w dol
		case '6': {_Direction = 6; break; } //w prawo
		case '7': {_Direction = 7; break; } //w lewo
		case '2': {_Direction = 2; break; } //wiezyczka
		case '8': {_Direction = 8; break; } //tancz
		}

		if (type == '2') {
		_MapTexture.loadFromFile("grafiki/tower.png");
		}
		else if (type == '8') {
		_MapTexture.loadFromFile("grafiki/dancing.png");
		}
		else {
		_MapTexture.loadFromFile("grafiki/kafelek.png");
		}

		_MapSprite.setTexture(_MapTexture);
		
		_MapSprite.setOrigin(22, 24); //ustawienie "srodka ciezkosci" w faktycznym srodku elementu

		_MapSprite.setPosition(x, y);

		
		
		
	}

	~Map(){
	}

	int whatToDo() {
		return _Direction;
	}
	Sprite getMapSprite() {
		return _MapSprite;
	}
	Vector2f getPosition() {
		return _MapSprite.getPosition();
	}

	void draw(RenderWindow& window) {
		window.draw(_MapSprite);
	}


private:

	Sprite _MapSprite;
	Texture _MapTexture;
	int _Direction=0;

};

