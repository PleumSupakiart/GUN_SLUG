#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
#define max_item 3
class menu
{
public:
	menu(float width, float height);
	~menu();

	void draw(RenderWindow& window);

	void Moveup();
	void Movedown();
	int GetPressItem() { return selecteditem; }

private:
	int selecteditem = 0;
	Font font;
	Text mainmenu[max_item]; // start leaderboard exit

};

