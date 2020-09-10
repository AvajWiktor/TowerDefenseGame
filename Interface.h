#pragma once
#include "Map.h"
#include "Gun.h"
#include "Rocket.h"
#include "Plasma.h"
class Interface
{
public:
	Interface(int hp, string fontDirection) {
		_PlayerHp = hp;
		_InterfaceFont.loadFromFile(fontDirection);
		_PlayerHpTxt.setFont(_InterfaceFont);
		_PlayerHpTxt.setFillColor(Color::Cyan);
		_PlayerGoldTxt.setFont(_InterfaceFont);
		_PlayerGoldTxt.setFillColor(Color::Yellow);
		_PlayerHpTexture.loadFromFile("grafiki/hpTex.png");
		MakeGunInterface();

		MakeHpBar();
		
	}

	
	void LoseHp() {
		if (_PlayerHp > 0) _PlayerHp--;
	}
	void EarnMoney(int g) {
		_PlayerGold += g;
	}
	void DrawInterface(RenderWindow &window) {

		for (int i = 0; i < _PlayerHp; i++)
		{
			window.draw(*_HpBar[i]);
		}
		string s = to_string(_PlayerHp);
		_PlayerHpTxt.setString(s);
		_PlayerHpTxt.setCharacterSize(15);
		
		_PlayerHpTxt.setPosition(89,15);
		window.draw(_PlayerHpTxt);

		 s = to_string(_PlayerGold);
		_PlayerGoldTxt.setString("Gold : " + s);
		_PlayerGoldTxt.setCharacterSize(15);

		_PlayerGoldTxt.setPosition(815, 20);
		window.draw(_PlayerHpTxt);
		window.draw(_PlayerGoldTxt);
		for (auto itr = _GunInterface.begin(); itr != _GunInterface.end(); itr++)
		{
			
			window.draw((*itr)->getSprite());
		}
		if ((_GunInterface[0])->collision(Vector2f(Mouse::getPosition(window)))) changeCursor(true, window);
		else if ((_GunInterface[1])->collision(Vector2f(Mouse::getPosition(window)))) changeCursor(true, window);
		else if ((_GunInterface[2])->collision(Vector2f(Mouse::getPosition(window)))) changeCursor(true, window);
		else changeCursor(false, window);
	}
	bool collision(Sprite s1, Sprite s2) {
		if (s1.getGlobalBounds().intersects(s2.getGlobalBounds())) return true;
		else return false;
	}
	bool collision(Sprite s, Vector2f v) {
		if (s.getGlobalBounds().contains(v)) return true;
		else return false;
	}
	void changeCursor(bool b, RenderWindow &w) {
		Cursor c;
		c.loadFromSystem(Cursor::Hand);

		if (b) w.setMouseCursor(c);
		else {
			c.loadFromSystem(Cursor::Arrow);
			w.setMouseCursor(c);
		}
	}



private:

	void MakeHpBar() {
		for (int i = 0; i < _PlayerHp; i++)
		{
			Sprite* n = new Sprite(_PlayerHpTexture);
			n->setOrigin(8,11);
			n->setPosition(Vector2f(151 + i * 20, 19));
			_HpBar.push_back(n);
		}
	}
	void MakeGunInterface() {
		Gun *g = new Gun(1325, 104);
		_GunInterface.push_back(g);
		Rocket *r = new Rocket(1405, 104);
		_GunInterface.push_back(r);
		Plasma *p = new Plasma(1485, 104);
		_GunInterface.push_back(p);


	}

	int _PlayerHp = 0;
	int _PlayerGold = 0;
	Text _PlayerHpTxt, _PlayerGoldTxt;
	Font _InterfaceFont;
	vector<Sprite*> _HpBar;
	vector<Tower*> _GunInterface;
	Texture _PlayerHpTexture;
};

