#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<vector>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(800, 600), "doge game");
	window.setFramerateLimit(60);
	Sprite cat;
	Texture catTex;
	catTex.loadFromFile("Templates/cat.png");
	cat.setTexture(catTex);
	cat.setScale(0.3f, 0.3f);


	//doge
	int hp = 10;
	Sprite doge;
	Texture dogTex;
	dogTex.loadFromFile("Templates/doge.png");
	doge.setTexture(dogTex);
	doge.setScale(0.4f, 0.4f);
	vector<Sprite>cats;
	int catspawn = 0;
	cats.push_back(cat);

	RectangleShape hpbar;
	hpbar.setFillColor(Color::Red);
	hpbar.setSize(Vector2f(hp * 20.f, 20.f));
	hpbar.setPosition(Vector2f(300.f, 10.f));

	while (window.isOpen() && hp>0)
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed())
			{
				window.close();
			}
		}
		//update 
		catspawn++;
		if (catspawn >= 29)
		{
			cat.setPosition(window.getSize().x, rand() % int(window.getSize().y-cat.getGlobalBounds().height));
			cats.push_back(cat);
			catspawn = 0;
		}
		for (size_t i = 0;i < cats.size();i++)
		{
			cats[i].move(Vector2f(-5.f, 0.f));
			if (cats[i].getPosition().x < 0)
			{
				cats.erase(cats.begin() + i);
			}
		}

		//update doge
		doge.setPosition(doge.getPosition().x, Mouse::getPosition(window).y);
		if (doge.getPosition().y > window.getSize().y-doge.getGlobalBounds().height)
		{
			doge.setPosition(doge.getPosition().x, window.getSize().y-doge.getGlobalBounds().height);
		}
		if (doge.getPosition().y < 0)
		{
			doge.setPosition(doge.getPosition().x, 0);
		}

		//collision
		for (size_t i = 0;i < cats.size();i++)
		{
			if (doge.getGlobalBounds().intersects(cats[i].getGlobalBounds()))
			{
				--hp;
				cats.erase(cats.begin() + i);
			}
		}
		hpbar.setSize(Vector2f(hp * 20.f, 20.f));
		window.clear();



		window.draw(doge);
		for (int i = 0;i < cats.size();i++)
		{
			window.draw(cats[i]);
		}
		window.draw(hpbar);
		window.display();
	}
}