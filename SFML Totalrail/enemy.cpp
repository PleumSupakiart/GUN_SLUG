#include "enemy.h"

enemy::enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed * 3;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;



	body.setSize(sf::Vector2f(110.0f, 130.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(1300, 400);
	body.setTexture(texture);
}

enemy::~enemy()
{

}

void enemy::Update(float deltaTime)
{
	velocity.x = 0.0f;
	int WINDOW_WIDTH = 1580;

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x -= speed * 0.5;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x += speed * 0.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		row = 1;
		velocity.x -= speed;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		row = 1;
		velocity.x += speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump)
	{
		if (canJump == 1)
		{
			row = 2;
		}

		canJump = false;
		velocity.y = -sqrtf(6.0f * 980.0f * jumpHeight);
		// squar root ( 2.0f * gravity * jumpHeight);

	}

	velocity.y += 4 * 981.0f * deltaTime;


	if (velocity.x == 0.0f)
	{
		row = 0;
	}


	else
	{


		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}*/

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

	// left window collition
	if (body.getPosition().x < 0)
	{
		body.setPosition(0, body.getPosition().y);
	}
	if (body.getPosition().x + body.getGlobalBounds().width > WINDOW_WIDTH)
	{
		body.setPosition(WINDOW_WIDTH - body.getGlobalBounds().width, body.getPosition().y);
	}

}

void enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void enemy::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		// Collision on the left.
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		// Collision on the right.
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		// Collision on the bottom.
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		// Collision on the top.
		velocity.y = 0.0f;
	}
}
