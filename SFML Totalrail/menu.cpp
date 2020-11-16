#include "menu.h"
menu::menu(float width, float height)
{
	if (!font.loadFromFile("font/Metal Slug.ttf"))
	{
		cout << "Error font" << endl;
	}
	mainmenu[0].setFont(font);
	mainmenu[0].setCharacterSize(60);
	mainmenu[0].setFillColor(Color::Red);
	mainmenu[0].setString("Play");
	mainmenu[0].setOrigin(mainmenu[0].getLocalBounds().width / 2, mainmenu[0].getLocalBounds().height / 2);
	mainmenu[0].setPosition(Vector2f(width / 2, height / (max_item + 1) * 1));

	mainmenu[1].setFont(font);
	mainmenu[1].setCharacterSize(60);
	mainmenu[1].setFillColor(Color::White);
	mainmenu[1].setString("LeaderBoard");
	mainmenu[1].setOrigin(mainmenu[1].getLocalBounds().width / 2, mainmenu[1].getLocalBounds().height / 2);
	mainmenu[1].setPosition(Vector2f(width / 2, height / (max_item + 1) * 2));

	mainmenu[2].setFont(font);
	mainmenu[2].setCharacterSize(60);
	mainmenu[2].setFillColor(Color::White);
	mainmenu[2].setString("Exit");
	mainmenu[2].setOrigin(mainmenu[2].getLocalBounds().width / 2, mainmenu[2].getLocalBounds().height / 2);
	mainmenu[2].setPosition(Vector2f(width / 2, height / (max_item + 1) * 3));
}

menu::~menu()
{

}

void menu::draw(RenderWindow& window)
{
	for (int i = 0; i < max_item ; i++)
	{
		window.draw(mainmenu[i]);
	}
}


void menu::Movedown()
{
	if (selecteditem + 1 < max_item)
	{
		mainmenu[selecteditem].setFillColor(Color::White);
		selecteditem++;
		mainmenu[selecteditem].setFillColor(Color::Red);
	}
}

void menu::Moveup()
{
	if (selecteditem - 1 >= 0)
	{
		mainmenu[selecteditem].setFillColor(Color::White);
		selecteditem --;
		mainmenu[selecteditem].setFillColor(Color::Red);
	}
}