#include <SFML/Graphics.hpp>
#include <time.h>
#include "tetrisset.h"


int main()
{
	
	// rendering window, setting textures from constant settings
	sf::RenderWindow window(sf::VideoMode(constants::sizeofpixelcube * constants::fieldwidth, constants::sizeofpixelcube * constants::fieldhigh), "TETRIS GAME");
	srand(time(0));
	sf::Clock clock;
	sf::Texture background;
	sf::Texture texture;
	texture.loadFromFile(constants::texturepath);
	background.loadFromFile(constants::backgroundpath);
	sf::Sprite sprite(texture);
	sf::Sprite sprite_background(background);

	sprite.setTextureRect(sf::IntRect(0, 0, constants::sizeofpixelcube, constants::sizeofpixelcube)); //sprite in size of tetromino block
	

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer::timer += time;

		sf::Event ev;

		//Handling events that depend on the user
		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			//Control from the keyboard
			case sf::Event::KeyPressed: 
				if (ev.key.code == sf::Keyboard::A || ev.key.code == sf::Keyboard::Left) //keys "A", "<-" make tetromino move to the left
				{
					gameset::horisontal = -1;
				}
				else if (ev.key.code == sf::Keyboard::D || ev.key.code == sf::Keyboard::Right) //keys "D", "->" make tetromino move to the right
				{
					gameset::horisontal = 1;
				}
				else if (ev.key.code == sf::Keyboard::W || ev.key.code == sf::Keyboard::Space || ev.key.code == sf::Keyboard::Up) // with keys "W", "Arrow up", "Space" tetromino rotates
				{
					gameset::rotation = true;
				}
				break;
			}	
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) //keys "S", "Arrow Down" speed up tetromino
		{
			timer::delayoftime = 0.06f;
		}

		// horisontal move
		for (int k = 0; k < 4; k++)
		{
			helper[k] = f[k];
			f[k].x += gameset::horisontal;
		}
		
		if (collisionchecking()) //returns last coordinates in case of collision
		{
			for (int i = 0; i < 4; i++)
				f[i] = helper[i];
		}
		

		//90 degree rotation
		if (gameset::rotation)
		{
			coord centerrotation = f[1]; //setting center of tetromino rotation
			for (int k = 0; k < 4; k++)
			{
				int y = f[k].x - centerrotation.x;
				int x = f[k].y - centerrotation.y;
				f[k].y = centerrotation.y + y;
				f[k].x = centerrotation.x - x;
			}
			//tetromino won't rotate if there will be collision
			if (collisionchecking()) 
			{
				for (int k = 0; k < 4; k++)
					f[k] = helper[k];
			}
		}

		if (timer::timer > timer::delayoftime) //for each tick of time
		{
			// tetromino moving down 
			for (int k = 0; k < 4; k++)
			{
				helper[k] = f[k];
				f[k].y += 1;
			}
			if (collisionchecking())
			{
				for (int k = 0; k < 4; k++) field[helper[k].y][helper[k].x] = gameset::colorNum;
				gameset::colorNum = 1 + rand() % 7;
				gameset::n = rand() % 7;
				for (int k = 0; k < 4; k++)
				{
					f[k].x = tetrisfigure[gameset::n][k] % constants::coordsize;
					f[k].y = tetrisfigure[gameset::n][k] / constants::coordsize;
				}
			}
			timer::timer = 0; //value of timer sets back to 0, the cycle starts again
		}

		//this part of code deletes a filled line
		int a = constants::fieldhigh - 1;
		for (int k = constants::fieldhigh - 1; k > 0; k--)
		{
			int count = 0;
			for (int i = 0; i < constants::fieldwidth; i++)
			{
				if (field[k][i])
				{
					count++;
				}
				field[a][i] = field[k][i];
			}
			if (count < constants::fieldwidth)
			{
				a--;
			}
		}

		//case of the first appearence of tetromino, program does this part of code only once
		if (gameset::Gamestart)
		{
			gameset::Gamestart = false;
			gameset::n = rand() % 7;
			for (int k = 0; k < 4; k++)
			{
				f[k].y = tetrisfigure[gameset::n][k] / constants::coordsize;
				f[k].x = tetrisfigure[gameset::n][k] % constants::coordsize;
				
			}
		}
		// values set to normal
		timer::delayoftime = 0.5f;
		gameset::horisontal = 0;
		gameset::rotation = false;
		

		//window.clear(sf::Color::White);
		window.draw(sprite_background);

		//Drawing part that became static
		for (int k = 0; k < constants::fieldhigh; k++)
			for (int i = 0; i < constants::fieldwidth; i++)
			{
				if (field[k][i] == 0) continue;
				sprite.setTextureRect(sf::IntRect(field[k][i] * constants::sizeofpixelcube, 0, constants::sizeofpixelcube, constants::sizeofpixelcube));
				sprite.setPosition(i * constants::sizeofpixelcube, k * constants::sizeofpixelcube);
				window.draw(sprite);
			}

		//drawing
		for (int k = 0; k < 4; k++)
		{
			if (collisionchecking()) //losing condition, the window closes automatically
			{
				window.close();
			}
			sprite.setTextureRect(sf::IntRect(gameset::colorNum * constants::sizeofpixelcube, 0, constants::sizeofpixelcube, constants::sizeofpixelcube));
			sprite.setPosition(f[k].x * constants::sizeofpixelcube, f[k].y * constants::sizeofpixelcube);
			window.draw(sprite);
		}
		
		window.display();
	}

	return 0;
}