#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "SzczerbiakBagienny.h"

using namespace sf;

class Bullet
{
public:
	Bullet(SzczerbiakBagienny &mob, Vector2f p, Vector2f v, int &t, int type, int dmg) {
		_Mob = &mob;
		_Type = type;
		_Timer = &t;
		_Dmg = dmg;
		switch (_Type) {
		case 1:_BulletTexture.loadFromFile("grafiki/bullet.png"); break;
		case 2:_BulletTexture.loadFromFile("grafiki/rocket.png"); break;
		case 3:_BulletTexture.loadFromFile("grafiki/plasma.png"); break;
		}
		_Velocity = v;
		_BulletSprite.setTexture(_BulletTexture);
		_BulletSprite.setOrigin(_BulletTexture.getSize().x/2.0, _BulletTexture.getSize().y / 2.0);
		_BulletSprite.setScale(0.5, 0.5);
		_BulletSprite.setPosition(p);
	}

	void draw(RenderWindow& w) {
		w.draw(_BulletSprite);
		
	}
	bool animate() {
		
		Vector2f AimDir = _Mob->getPos() - _BulletSprite.getPosition();
		Vector2f AimDirNorm = Vector2f(AimDir.x/sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)),AimDir.y/ sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)));
		_Velocity = Vector2f(AimDirNorm.x*5, AimDirNorm.y*5);
		_BulletSprite.move(_Velocity);
		return shoot();
	}
	bool shoot() {
		if ((_BulletSprite.getGlobalBounds().intersects((_Mob->getSprite().getGlobalBounds())))&&_Type==2) {
			_BulletSprite.setScale(1.0, 1.0);
			_Type = 1;
			return false;
			
		}
		else if (_BulletSprite.getGlobalBounds().intersects(_Mob->getSprite().getGlobalBounds())) {
			_Mob->isDead(_Dmg);
			return true;
		}
	}
private:
	int _Type = 0;
	int* _Timer = 0;
	int _Dmg=0;
	Vector2f _Velocity = Vector2f(0,0);
	Sprite _BulletSprite;
	Texture _BulletTexture;
	SzczerbiakBagienny *_Mob;


};

