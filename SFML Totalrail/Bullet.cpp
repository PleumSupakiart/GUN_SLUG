#include "Bullet.h"

Bullet::Bullet(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	body.setSize(sf::Vector2f(62.0f, 24.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
}

void Bullet::Update(float deltaTime)
{
	velocity.x = 1500.0f;
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
