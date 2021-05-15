#pragma once
#include "Tower.h"
class Gun :
    public Tower
{
public:
    Gun(int x, int y, int &t) 
    {
        _Timer = &t;
        _Texture.loadFromFile("grafiki/gun-1.png");
        _Sprite.setTexture(_Texture);
        _Sprite.setOrigin(_Texture.getSize().x/2.0, _Texture.getSize().y/2.0);
        _Sprite.setScale(50.0 / 28.0, 55.0 / 28.0);
        _Sprite.setPosition(Vector2f(x,y));
        _RangeCircle.setRadius(_Range);
        _RangeCircle.setFillColor(Color::Transparent);
        _RangeCircle.setOutlineColor(Color::Red);
        _RangeCircle.setOutlineThickness(2);
        _RangeCircle.setOrigin(_Range, _Range);
        _RangeCircle.setPosition(x, y);
    }
    void draw(RenderWindow& window) 
    {
        window.draw(_Sprite);
        window.draw(_RangeCircle);
        _CanShoot = true;
        _Cost = 1 + (_TowerLevel - 1) * 15;
    }
    int getLvl() 
    {
        return _TowerLevel;
    }
    int getType() 
    {
        return _Type;
    }
    int getCost() 
    {
        return _Cost;
    }
    void upgrade() 
    {
        _TowerLevel++;
        _Dmg += _TowerLevel * _Dmg;
        _Range += 50;
        _AttackSpeed += 0.2;
    }
    Sprite getSprite() 
    {
        return _Sprite;
    }
    bool collision(Vector2f v) 
    {
        if (_Sprite.getGlobalBounds().contains(v)) return true;
        else return false;
    }
    void setPosition(Vector2f p) 
    {
        _Sprite.setPosition(p);
    }
    void shoot(SzczerbiakBagienny& mob, Vector2f p, list<Bullet*>& b) 
    {
        if (_RangeCircle.getGlobalBounds().contains(p)) 
        {
            if (_CanShoot) 
            {
                if ((*_Timer % int(60 / _AttackSpeed) == 0)) 
                {
                    Vector2f AimDir = mob.getPos() - _Sprite.getPosition();
                    Vector2f AimDirNorm = Vector2f(AimDir.x / sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)), AimDir.y/ sqrt(pow(AimDir.x, 2) + pow(AimDir.y, 2)));
                    float angle = atan2(AimDir.y, AimDir.x) * 180 / 3.14;
                 
                    _Sprite.setRotation(angle);

                    Bullet* bullet = new Bullet(mob, _Sprite.getPosition(), AimDirNorm, *_Timer, _Type, _Dmg);
                    b.push_back(bullet);
                    _CanShoot = false;
                }
            }
        }
    }

private:
    bool _CanShoot = true;
    int* _Timer;
    int _Cost = 10;
    int _TowerLevel = 1;
    int _Type = 1;
    int _Range = 100;
    Sprite _Sprite;
    Texture _Texture;
    CircleShape _RangeCircle;
    int _Dmg = 10;
    float _AttackSpeed = 3.0;
};

