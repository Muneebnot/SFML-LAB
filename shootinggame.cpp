#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(800, 600), "SFML SETUP");
	window.setFramerateLimit(60);
	//basic
	CircleShape player;
	CircleShape projectile;
	RectangleShape enemy;

	//player
	player.setRadius(50.f);
	player.setPosition(window.getSize().x / 2 - player.getRadius(), window.getSize().y - player.getRadius() * 2 - 10.f);
	player.setFillColor(Color::White);

	//projectile
	int shootime = 0;
	projectile.setRadius(10.f);
	projectile.setFillColor(Color::Red);

	//enemy
	enemy.setSize(Vector2f(50.f, 50.f));
	enemy.setFillColor(Color::Yellow);
	int enemyspawn = 0;
	//vectors
	vector<CircleShape>projectiles;
	vector<RectangleShape>enemies;
	projectiles.push_back(CircleShape(projectile));
	enemies.push_back(RectangleShape(enemy));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		//update
		Vector2f playercenter;
		playercenter = Vector2f(player.getPosition().x + player.getRadius()-projectile.getRadius(), player.getPosition().y + player.getRadius());
		
		//movement by moouse
		/*float mousex = Mouse::getPosition(window).x;
		if (mousex < 0)
		{
			mousex = 0;
		}
		if (mousex > window.getSize().x - player.getRadius() * 2)
		{
			mousex = window.getSize().x - player.getRadius() * 2;
		}
		player.setPosition(mousex, player.getPosition().y);*/
		//update projectiles
		
		//movement by keyboard
		float speed = 8.f; // player move speed

		// move left
		if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.move(-speed, 0.f);
		}

		// move right
		if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(speed, 0.f);
		}

		if (player.getPosition().x < 0)
		{
			player.setPosition(0, player.getPosition().y);
		}
		if (player.getPosition().x > window.getSize().x - player.getRadius() * 2)
		{
			player.setPosition(window.getSize().x - player.getRadius() * 2, player.getPosition().y);
		}

		
		
		
		
		
		
		if (shootime < 5)
		{
			shootime++;
		}
		if (Mouse::isButtonPressed(Mouse::Left) && shootime >= 5)
		{
			shootime = 0;
			projectile.setPosition(playercenter);
			projectiles.push_back(CircleShape(projectile));
			
		}
		for (size_t i = 0;i < projectiles.size();i++)
		{
			projectiles[i].move(Vector2f(0.f, -10.f));
			if (projectiles[i].getPosition().y < 0)
			{
				projectiles.erase(projectiles.begin() + i);
			}
			
		}
		//update enemies
		
			enemyspawn++;
		
		if (enemyspawn >= 20)
		{
			float xpos = static_cast<float>(rand() % static_cast<int>(window.getSize().x - enemy.getSize().x));
			enemy.setPosition(xpos, 0.f);
			enemies.push_back(RectangleShape(enemy));
			enemyspawn = 0; // reset timer so it spawns again
		}

		for (size_t i = 0;i < enemies.size();i++)
		{
			enemies[i].move(Vector2f(0.f, 5.f));
			if (enemies[i].getPosition().y > window.getSize().y-enemies[i].getSize().y)
			{
				enemies.erase(enemies.begin() + i);
			}
		}


		//collision
		for (size_t i = 0;i < projectiles.size();i++)
		{
			for (size_t k = 0;k < enemies.size();k++)
			{
				if (projectiles[i].getGlobalBounds().intersects(enemies[k].getGlobalBounds()))
				{
					projectiles.erase(projectiles.begin() + i);
					enemies.erase(enemies.begin() + k);
					break;
				}
			}
		}

		window.clear();

		//draw

		window.draw(player);
		for (size_t i = 0;i < projectiles.size();i++)
		{
			window.draw(projectiles[i]);
		}

		for (size_t i = 0;i < enemies.size();i++)
		{
			window.draw(enemies[i]);
		}
		window.display();
	}
}
