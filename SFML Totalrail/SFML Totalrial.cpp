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
#include<SFML/Audio.hpp>
#include <time.h>
#include "Player.h"
#include "Platform.h"
#include "enemy.h"
#include "menu.h"

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

    menu menu(window.getSize().x, window.getSize().y);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("sprite/player/standrunjump.png");

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("sprite/enemy/shock.png");

    Texture background;
    background.loadFromFile("sprite/background/bg1.png");
     sf::RectangleShape bg1(Vector2f(1520, 720));
    bg1.setTexture(&background);

    Texture bgmenu;
    bgmenu.loadFromFile("sprite/background/mainmenu.png");
    sf::RectangleShape Bgmenu(Vector2f(1520, 720));
    Bgmenu.setTexture(&bgmenu);


    SoundBuffer soundback;
    if (!soundback.loadFromFile("sound/Metal Slug.wav"))
    {
        cout << "ERROR LOAD SOUND" << endl;
    }
    Sound sound;
    sound.setBuffer(soundback);
    sound.setVolume(20);
    sound.setLoop(true);
    //sound.play();


    Player player(&playerTexture, sf::Vector2u(8, 3), 0.1f, 100.0f, 300.0f); // rate of picture sprite a little dramatically >> so fast (speed in x, jump high in y)
    enemy enemy(&enemyTexture, sf::Vector2u(10, 1), 0.1f, 100.0f, 300.0f);

    std::vector<Platform> platforms;
 
   /*01*/ platforms.push_back(Platform(nullptr, sf::Vector2f(2000.0f, 3.0f), sf::Vector2f(800.0f, 700.0f)));  // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up 
   /*02*/ platforms.push_back(Platform(nullptr, sf::Vector2f(160.0f, 3.0f), sf::Vector2f(140.0f, 520.0f)));  // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up
   /*03*/ platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 3.0f), sf::Vector2f(600.0f, 390.0f)));  // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up
   /*04*/ platforms.push_back(Platform(nullptr, sf::Vector2f(160.0f, 3.0f), sf::Vector2f(980.0f, 525.0f)));
   /*05*/ platforms.push_back(Platform(nullptr, sf::Vector2f(500.0f, 3.0f), sf::Vector2f(1350.0f, 390.0f)));
   
   
    
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
            case Event::KeyReleased:
                switch (event.key.code)
                { 
              
                case Keyboard::Up:
                    menu.Moveup();
                    break;
                case Keyboard::Down:
                    menu.Movedown();
                    break;
                case Keyboard::Return:
                    switch (menu.GetPressItem())
                    {
                    case 0:
                        cout << "Play has been preesed" << endl;
                        break;

                    case 1:
                        cout << "Leaderboard has been preesed" << endl;
                        break;

                    case 2:
                        window.close();
                        break;
                    }
           
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                ResizeView(window, view);
                break;
            }
        }

        player.Update(deltaTime);
        enemy.Update(deltaTime);

        sf::Vector2f direction;

        for (Platform& platform : platforms)
            if (platform.GetCollider().CheckCollision(&player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);

        for (Platform& platform : platforms)
            if (platform.GetCollider().CheckCollision(&enemy.GetCollider(), direction, 1.0f))
                enemy.OnCollision(direction);

       
       view.setCenter(player.GetPosition().x,450);
      
        
        window.clear(sf::Color(150, 150, 150));
     
          window.draw(bg1);
        player.Draw(window);
        enemy.Draw(window);

        Event::KeyReleased;
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.draw(Bgmenu);
             menu.draw(window);
      
        }
        
       window.setView(view); 
        
       
      
        for (Platform& platform : platforms)
        platform.Draw(window);
      
        window.display();
    }
    
    return 0;
}

