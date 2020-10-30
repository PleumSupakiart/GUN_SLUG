#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspecRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspecRatio, VIEW_HEIGHT);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "GUN SLUG", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("standrun.png");

    Player player(&playerTexture, sf::Vector2u(8, 2), 0.11f, 100.0f, 400.0f); // rate of picture sprite a little dramatically >> so fast (speed in x, jump high in y)

    std::vector<Platform> platforms;
 
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));      // (wild,high)  (left,right)
    platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(700.0f, 200.0f)));       // (wild,high)  ((left,right),(up,down)) point+ box right/down ,point- box left/up 
    platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 100.0f), sf::Vector2f(500.0f, 500.0f))); //floor   // (wild,high)  (left,right)
    
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



        view.setCenter(player.GetPosition());

        window.clear(/*sf::Color(150, 150, 150)*/);
        window.setView(view);
        player.Draw(window);
        
        for (Platform& platform : platforms)
        platform.Draw(window);
      
        window.display();
    }
    
    return 0;
}

