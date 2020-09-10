#pragma once
#include "Tower.h"
class Gun :
    public Tower
{


public:
    Gun(int x, int y) {
        _Texture.loadFromFile("grafiki/gun-1.png");
        _Sprite.setTexture(_Texture);
        _Sprite.setOrigin(_Texture.getSize().x/2.0, _Texture.getSize().y/2.0);
        _Sprite.setScale(50.0 / 28.0, 55.0 / 28.0);
        _Sprite.setPosition(Vector2f(x,y));
    }
    ~Gun() {

    }

    void draw(RenderWindow& window) {
        window.draw(_Sprite);
    }
    int getLvl() {
        return _TowerLevel;
    }
    int getType() {
        return _Type;
    }
    void upgrade() {
        _TowerLevel++;
        _Dmg += _TowerLevel * _Dmg;
        _Range += 50;
        _AttackSpeed += 0.2;
    }
    Sprite getSprite() {
        return _Sprite;
    }
    bool collision(Vector2f v) {
        
        if (_Sprite.getGlobalBounds().contains(v)) return true;
        else return false;
    }

private:
    
    int _TowerLevel = 1;
    int _Type = 1;
    int _Range = 100;
    Sprite _Sprite;
    Texture _Texture;
    CircleShape _RangeSprite;
    int _Dmg = 50;
    float _AttackSpeed = 1.0;

};

