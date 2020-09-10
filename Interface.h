#pragma once
#include "MapField.h"
#include "Gun.h"
#include "Rocket.h"
#include "Plasma.h"
#include <SFML/Audio.hpp>
class Interface
{
public:
	Interface(int hp, string fontDirection, RenderWindow &w, int &t) {
		_Timer = &t;
		_Window = &w;
		_PlayerHp = hp;
		_Window->setFramerateLimit(60);
		_InterfaceFont.loadFromFile(fontDirection);
		_PlayerHpTxt.setFont(_InterfaceFont);
		_PlayerHpTxt.setFillColor(Color::Cyan);
		_PlayerGoldTxt.setFont(_InterfaceFont);
		_PlayerGoldTxt.setFillColor(Color::Yellow);
		_PlayerScoreTxt.setFont(_InterfaceFont);
		_PlayerScoreTxt.setFillColor(Color::Cyan);
		_PlayerHpTexture.loadFromFile("grafiki/hpTex.png");
		_QuitButtonTextureOff.loadFromFile("grafiki/quit-off.png");
		_QuitButtonTextureOn.loadFromFile("grafiki/quit-on.png");
		_QuitButtonSprite.setTexture(_QuitButtonTextureOff);
		_QuitButtonSprite.setOrigin(_QuitButtonTextureOff.getSize().x/2.0, _QuitButtonTextureOff.getSize().y/2.0);
		_QuitButtonSprite.setPosition(1507, 28);
		//_SoundBuffer.loadFromFile("nuta.ogg");
		//_Sound.setBuffer(_SoundBuffer);
		//_Sound.play();
		
		_BackGroundTexture.loadFromFile("grafiki/tlo1.png");
		_BackGroundSprite.setTexture(_BackGroundTexture);
		MakeGunInterface();

		MakeHpBar();
		
	}

	
	void LoseHp() {
		if (_PlayerHp > 0)_PlayerHp--;
	}
	void EarnMoney(int g) {
		_PlayerGold += g;
	}
	bool DrawInterface() {
		
		if (_PlayerHp <= 0) return true;
		else {

			_Window->draw(_BackGroundSprite);
			_MousePos = Vector2f(Mouse::getPosition(*_Window)); //pobieranie pozycji myszki wzgledem okna gry

			for (int i = 0; i < _PlayerHp; i++) //rysowanie paskow zdrowia w zaleznosci od posiadanego hp przez gracza
			{
				_Window->draw(*_HpBar[i]);
			}

			//wyswietlanie hp oraz golda czcionka
			string s = to_string(_PlayerHp);
			_PlayerHpTxt.setString(s);
			_PlayerHpTxt.setCharacterSize(15);
			_PlayerHpTxt.setPosition(89, 15);
			_Window->draw(_PlayerHpTxt);

			s = to_string(_PlayerGold);
			_PlayerGoldTxt.setString("Gold : " + s);
			_PlayerGoldTxt.setCharacterSize(15);
			_PlayerGoldTxt.setPosition(815, 20);
			_Window->draw(_PlayerGoldTxt);

			s = to_string(_PlayerScore);
			_PlayerScoreTxt.setString(s);
			_PlayerScoreTxt.setCharacterSize(15);
			_PlayerScoreTxt.setPosition(1135, 20);
			_Window->draw(_PlayerScoreTxt);

			//rysowanie ikon wiezyczek w menu
			for (auto itr = _GunInterface.begin(); itr != _GunInterface.end(); itr++)
			{

				_Window->draw((*itr)->getSprite());
			}
			//sprawdzanie czy gracz najechal myszka na ktorys z elementow menu, zmiana rodzaju kursora w przypadku najechania 
			//oraz "przyklejenie" wybranej broni do kursora podczas klikniecia LPM
			if ((_GunInterface[0])->collision(_MousePos)&&(_GunInterface[0]->getCost()<=_PlayerGold)) {

				changeCursor(true);
				if (Mouse::isButtonPressed(Mouse::Left)) {

					_ChosenTower = new Gun(_MousePos.x, _MousePos.y, *_Timer);
				}
			}
			else if ((_GunInterface[1])->collision(_MousePos) && (_GunInterface[1]->getCost() <= _PlayerGold)) {

				changeCursor(true);
				if (Mouse::isButtonPressed(Mouse::Left)) {

					_ChosenTower = new Rocket(_MousePos.x, _MousePos.y, *_Timer);
				}
			}
			else if ((_GunInterface[2])->collision(_MousePos) && (_GunInterface[2]->getCost() <= _PlayerGold)) {

				changeCursor(true);
				if (Mouse::isButtonPressed(Mouse::Left)) {

					_ChosenTower = new Plasma(_MousePos.x, _MousePos.y, *_Timer);
				}
			}
			else {
				changeCursor(false);
				if (Mouse::isButtonPressed(Mouse::Right)) {
					_ChosenTower = NULL;
				}
			}
			//w przypadku gdy jaka wieza jest wybrana nastepuje wyswietlenie sprite oraz podazanie za kursorem


			if (_QuitButtonSprite.getGlobalBounds().contains(_MousePos)) {

				changeCursor(true);
				_QuitButtonSprite.setTexture(_QuitButtonTextureOn);
				_QuitButtonSprite.setScale(1.2, 1.2);
				if (Mouse::isButtonPressed(Mouse::Left)) {
					_Window->close();

				}
			}
			else {

				_QuitButtonSprite.setTexture(_QuitButtonTextureOff);
				_QuitButtonSprite.setScale(1.0, 1.0);
			}
			_Window->draw(_QuitButtonSprite);
			return false;
		}

	}
	void buyTower(int g) {
		_PlayerGold -= g;
	}
	void HandleChosenTower() {
		if (_ChosenTower != NULL) {
			_IsChosen = true;
			_ChosenTower->setPosition(_MousePos);
			_Window->draw(_ChosenTower->getSprite());
		}
		else _IsChosen = false;
	}


	bool collision(Sprite s1, Sprite s2) {
		if (s1.getGlobalBounds().intersects(s2.getGlobalBounds())) return true;
		else return false;
	}
	bool collision(Sprite s, Vector2f v) {
		if (s.getGlobalBounds().contains(v)) return true;
		else return false;
	}
	void changeCursor(bool b) {
		Cursor c;
		c.loadFromSystem(Cursor::Hand);

		if (b) _Window->setMouseCursor(c);
		else {
			c.loadFromSystem(Cursor::Arrow);
			_Window->setMouseCursor(c);
		}
	}
	int isChosen() {
		if (_IsChosen) return _ChosenTower->getType();
		else return 0;
	}
	void deleteChosenTower() {
		_ChosenTower = NULL;
	}
	void killMonster(int g) {
		_PlayerGold += g;
		_PlayerScore++;
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
		Gun *g = new Gun(1325, 104, *_Timer);
		_GunInterface.push_back(g);
		Rocket *r = new Rocket(1405, 104, *_Timer);
		_GunInterface.push_back(r);
		Plasma *p = new Plasma(1485, 104, *_Timer);
		_GunInterface.push_back(p);


	}
	Sound _Sound;
	SoundBuffer _SoundBuffer;
	
	int* _Timer = 0;
	Vector2f _MousePos;
	RenderWindow* _Window;
	int _PlayerHp = 0;
	int _PlayerGold = 50;
	int _PlayerScore = 0;
	Text _PlayerHpTxt, _PlayerGoldTxt, _PlayerScoreTxt;
	Font _InterfaceFont;
	vector<Sprite*> _HpBar;
	vector<Tower*> _GunInterface;
	Tower* _ChosenTower;
	bool _IsChosen = false;
	Texture _PlayerHpTexture, _QuitButtonTextureOff, _QuitButtonTextureOn, _BackGroundTexture;
	Sprite _QuitButtonSprite, _BackGroundSprite;
	
};

