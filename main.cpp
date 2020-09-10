#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "Tower.h"
#include "Map.h"
#include "SzczerbiakBagienny.h"
#include "Interface.h"


using namespace sf;
using namespace std;

int main() {
	Music music;
	music.openFromFile("nuta.ogg");
	music.play();
	RenderWindow window(sf::VideoMode(1545, 720), "Tower Defense");
	int timer = 0;
	int playerHP = 10;
	Interface infce(playerHP, "Starjedi.ttf", window, timer);
	Map mapa(window, infce, timer);

	while (window.isOpen()) {
		
		
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//rysowanie
			
		if(infce.DrawInterface()) break;
		mapa.HandleWholeMap();
		window.display();
		timer++;
	}

	
	return 0;
}