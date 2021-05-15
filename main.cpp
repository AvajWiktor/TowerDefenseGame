#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Tower.h"
#include "Map.h"
#include "SzczerbiakBagienny.h"
#include "Interface.h"

using namespace sf;
using namespace std;

Texture btnT1, btnT2, btnE1, btnE2;
Sprite btnSprite, btnESprite ;
bool isMenu = true;

void makeMenu() {
	btnT1.loadFromFile("grafiki/start.png");
	btnT2.loadFromFile("grafiki/start-on.png");
	btnE1.loadFromFile("grafiki/EXIT.png");
	btnE2.loadFromFile("grafiki/EXIT-on.png");

	btnSprite.setTexture(btnT1);
	btnSprite.setOrigin(btnT1.getSize().x/2.0, btnT1.getSize().y/2.0);
	btnSprite.setPosition(1546/2.0, 720/3.0);
	btnSprite.setScale(1.5,1.5);

	btnESprite.setTexture(btnE1);
	btnESprite.setOrigin(btnE1.getSize().x / 2.0, btnT1.getSize().y / 2.0);
	btnESprite.setPosition(1546 / 2.0, 720 / 2.0);
	btnESprite.setScale(1.5, 1.5);
}
void handleMenu(RenderWindow &w) 
{
	Cursor c;
	if (btnSprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(w)))) 
	{
		btnSprite.setTexture(btnT2);
		c.loadFromSystem(Cursor::Hand);
		
		if (Mouse::isButtonPressed(Mouse::Left)) 
		{
			isMenu = false;
		}
	}
	else if (btnESprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(w)))) 
	{
		btnESprite.setTexture(btnE2);
		c.loadFromSystem(Cursor::Hand);

		if (Mouse::isButtonPressed(Mouse::Left)) 
		{
			w.close();
		}
	}
	else 
	{
		btnSprite.setTexture(btnT1);
		btnESprite.setTexture(btnE1);
		c.loadFromSystem(Cursor::Arrow);
	}

	w.setMouseCursor(c);
	w.draw(btnSprite);
	w.draw(btnESprite);
}


int main() {
	RenderWindow window(sf::VideoMode(1545, 720), "Tower Defense");

	makeMenu();

	int timer = 0;
	int playerHP = 10;
	Interface infce(playerHP, "Starjedi.ttf", window, timer, isMenu);
	Map mapa(window, infce, timer);

	while (window.isOpen()) 
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
		}

		if (isMenu) 
		{
			handleMenu(window);
		}
		else 
		{
			//rysowanie
			if (infce.DrawInterface()) break;

			mapa.HandleWholeMap();
			timer++;
		}
		window.display();
	}
	return 0;
}