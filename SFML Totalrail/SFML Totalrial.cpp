#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/OpenGL.hpp>
#include<thread>
#include<math.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<typeinfo>
#include<random>
#include<windows.h>
#include<unordered_map> 
#include <time.h>
#include "Player.h"
#include "Platform.h"

using namespace sf;
using namespace std;


static const float VIEW_HEIGHT = 800.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspecRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspecRatio, VIEW_HEIGHT);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1520, 720), "GUN SLUG", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(1520.0f, 720.0f));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("sprite/player/standrunjump.png");

    Texture background;
    background.loadFromFile("sprite/background/bg1.png");
     sf::RectangleShape bg1(Vector2f(1520, 720));
    bg1.setTexture(&background);

    Player player(&playerTexture, sf::Vector2u(8, 3), 0.1f, 100.0f, 400.0f); // rate of picture sprite a little dramatically >> so fast (speed in x, jump high in y)

    std::vector<Platform> platforms;
 
   /*01*/ platforms.push_back(Platform(nullptr, sf::Vector2f(2000.0f, 3.0f), sf::Vector2f(800.0f, 700.0f)));  // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up 
   /*02*/ platforms.push_back(Platform(nullptr, sf::Vector2f(160.0f, 3.0f), sf::Vector2f(140.0f, 520.0f)));  // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up
   /*03*/ platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 3.0f), sf::Vector2f(600.0f, 390.0f)));  // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up
   /*04*/ platforms.push_back(Platform(nullptr, sf::Vector2f(160.0f, 3.0f), sf::Vector2f(980.0f, 525.0f)));
   //platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));      // (wild,high)  (left,right)
   // platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(700.0f, 200.0f)));       // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up 
   // platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 100.0f), sf::Vector2f(0.0f, 60.0f))); //floor   // (wild,high)  (left,right)
    
    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        player.Update(deltaTime);

        sf::Vector2f direction;

        for (Platform& platform : platforms)
            if (platform.GetCollider().CheckCollision(&player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);



       // view.setCenter(player.GetPosition());
        
        window.clear(sf::Color(150, 150, 150));
       // window.setView(view);
          window.draw(bg1);
        player.Draw(window);
      
        for (Platform& platform : platforms)
        platform.Draw(window);
      
        window.display();
    }
    
    return 0;
}

