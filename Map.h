#pragma once
#include "MapField.h"
#include "Interface.h"
#include "SzczerbiakBagienny.h"
#include "Tower.h"


class Map
{
public:
	Map(RenderWindow &w, Interface &i, int &t) {
		_Window = &w;
		_Interface = &i;
		_Timer = &t;
		ReadMapFile();
	}

	void HandleWholeMap() {
		_MousePosition = Vector2f(Mouse::getPosition(*_Window));
		
		SpawnMobs();
		HandleMoving();
		HandleTowers();

		DrawMap();
		DrawTowers();
		DrawEnemies();
		DrawBullets();

		_Interface->HandleChosenTower();
		HandlePlacingTower();
	}

	void ReadMapFile() {
		vector<string> map;
		fstream file;
		file.open("map.txt", std::ios::in);

		while (!file.eof()) {
			string line;
			getline(file, line);
			if (line[0] == '*') break;
			else map.push_back(line);
		}
		file.close();

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 27; j++)
			{
				/*if (map[i][j] == '2') {
					cTowerPlace* towerPlace = new cTowerPlace(Vector2f(20 + j * 40, 20 + i * 40));
					towerPlaces.push_back(towerPlace);
				}*/
				if (map[i][j] != '0') {
					MapField* ground = new MapField(72 + j * 44, 83 + i * 51, map[i][j]);

					_MapGround.push_back(ground);

				}

				else {

				}
			}
		}
	}

	void SpawnMobs() {
		if ((*_Timer) % 180 == 0) {
			Vector2f xy = Vector2f(_MapGround[0]->getPosition());
			SzczerbiakBagienny* m = new SzczerbiakBagienny(Vector2f(xy.x, xy.y), *_Timer);
			_Mobs.push_back(m);
		}


	}

	void HandleMoving() {


		for (int i = 0; i < _MapGround.size(); i++)
		{
			for (auto itr = _Mobs.begin(); itr != _Mobs.end(); itr++)
			{
				(*itr)->animate(_MapGround[i]->whatToDo(), _MapGround[i]->getPosition(), _MapGround[i]->getMapSprite());
			}

		}
		for (auto itr = _Mobs.begin(); itr != _Mobs.end();)
		{
			(*itr)->animate();
			if ((*itr)->ifSurvive()) {

				_Interface->LoseHp();
				itr = _Mobs.erase(itr);

			}
			else if ((*itr)->getHp() <= 0) {
				_Interface->killMonster((*itr)->getGold());
				itr = _Mobs.erase(itr);
			}
			else itr++;

		}



	}

	void DrawMap() {

		for (int i = 0; i != _MapGround.size(); i++)
		{
			_Window->draw(_MapGround[i]->getMapSprite());
		}

	}

	void DrawEnemies() {

		for (auto itr = _Mobs.begin(); itr != _Mobs.end(); itr++)
		{
			(*itr)->draw(*_Window);
		}
	}

	void DrawTowers() {
		for (auto itr = _Towers.begin(); itr != _Towers.end(); itr++)
		{
			(*itr)->draw(*_Window);
		}
	}

	void DrawBullets() {
		for (auto itr = _Bullets.begin(); itr != _Bullets.end(); )
		{
			(*itr)->draw(*_Window);
			if ((*itr)->animate()) {
				itr = _Bullets.erase(itr);
			}
			else itr++;
			

		}
	}

	void HandlePlacingTower() {
		int x = _Interface->isChosen();
		if (x) {
			for (auto itr = _MapGround.begin(); itr != _MapGround.end(); itr++)
			{
				if (((*itr)->whatToDo() == 2)&&((*itr)->isFree())) {
					if ((*itr)->collision(_MousePosition)&&(Mouse::isButtonPressed(Mouse::Left))) {
						switch (x) {
						case 1: {
							Gun *g = new Gun((*itr)->getPosition().x, (*itr)->getPosition().y, *_Timer);
							_Towers.push_back(g);
							_Interface->buyTower(g->getCost());
							break; }
						case 2: {
							Rocket* r = new Rocket((*itr)->getPosition().x, (*itr)->getPosition().y, *_Timer);
							_Towers.push_back(r);
							_Interface->buyTower(r->getCost());
							break; }
						case 3: { 
							Plasma* p = new Plasma((*itr)->getPosition().x, (*itr)->getPosition().y, *_Timer);
							_Towers.push_back(p);
							_Interface->buyTower(p->getCost());
							break; }
						}
						(*itr)->place();
						_Interface->deleteChosenTower();
					}
				}
			}
		}
	}

	void HandleBullets() {
		for (auto itr = _Bullets.begin(); itr != _Bullets.end(); itr++)
		{

		}
	}

	void HandleTowers() {
		//cout << "Naboi: " << _Bullets.size() << endl;
		for (auto itr = _Towers.begin(); itr != _Towers.end(); itr++)
		{
			for (auto it = _Mobs.begin(); it != _Mobs.end() ; it++)
			{

				(*itr)->shoot(*(*it),(*it)->getPos(), _Bullets);
			}
			
		}
	}

private: 
	int* _Timer;
	RenderWindow* _Window;
	Interface* _Interface;
	list<Bullet*> _Bullets;
	vector<MapField*> _MapGround;
	list<SzczerbiakBagienny*> _Mobs;
	vector<Tower*> _Towers;
	Vector2f _MousePosition = Vector2f(0,0);
};

