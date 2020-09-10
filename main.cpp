#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Tower.h"
#include "Map.h"
#include "SzczerbiakBagienny.h"
#include "Interface.h"

using namespace sf;
using namespace std;

//Obiekty i zmienne
RenderWindow window(sf::VideoMode(1545, 720), "Tower Defense");

vector<Map*> mapGround;
vector<SzczerbiakBagienny*> mobs;
int timer = 0;
int playerHP = 10;
int playerGold = 0;
Interface infce(playerHP, "Starjedi.ttf");





//Funkcje
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
				Map* ground = new Map(72 + j * 44, 83 + i * 51, map[i][j]);

				mapGround.push_back(ground);

			}

			else {

			}
		}
	}
}
void SpawnMobs() {
	if (timer % 180 == 0) {
		Vector2f xy = Vector2f(mapGround[19]->getPosition());
		SzczerbiakBagienny* m = new SzczerbiakBagienny(Vector2f(xy.x, xy.y));
		mobs.push_back(m);
	}

	
}
void HandleMoving() {


	for (int i = 0; i < mapGround.size(); i++)
	{
		for (auto itr = mobs.begin(); itr != mobs.end(); itr++)
		{
			(*itr)->animate(mapGround[i]->whatToDo(), mapGround[i]->getPosition(), mapGround[i]->getMapSprite());
		}

	}
	for (auto itr = mobs.begin(); itr != mobs.end();)
	{
		(*itr)->animate();
		if ((*itr)->ifSurvive()) {

				playerHP -= 1;
				infce.LoseHp(); 
				itr = mobs.erase(itr);
			
		}
		else itr++;
		
	}



}
void DrawMap() {

	for (int i = 0; i != mapGround.size(); i++)
	{
		window.draw(mapGround[i]->getMapSprite());
	}

}
void DrawinEnemies() {

	for (auto itr = mobs.begin(); itr != mobs.end(); itr++)
	{
		(*itr)->draw(window);
	}
}



int main() {
	
	ReadMapFile();
	window.setFramerateLimit(60);
	sf::Texture background;
	background.loadFromFile("grafiki/tlo1.png");
	sf::Sprite backgroundSprite(background);
	


	while (window.isOpen()) {
		if (timer == 181) timer = 1;
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//obsluga gry
		SpawnMobs();
		HandleMoving();
		//rysowanie
		window.draw(backgroundSprite);
		DrawMap();
		infce.DrawInterface(window);
		DrawinEnemies();
		window.display();
		timer++;
	}








	return 0;
}