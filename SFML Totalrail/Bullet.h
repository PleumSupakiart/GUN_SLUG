#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include "Animation.h"
#include "Collider.h"



class Bullet
{
private:
	sf::RectangleShape body;
	sf::RectangleShape texture;
	Animation animation;
	unsigned int row;
	sf::Vector2f velocity;

public:
    
	Bullet(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void SetPosition(sf::Vector2f(position)) {
		body.setPosition(position);
	}

};

