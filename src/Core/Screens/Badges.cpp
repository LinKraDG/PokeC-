#include <Core/AssetManager.h>
#include <Core/Screens/Badges.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Utils/Constants.h>
#include <UI/Text.h>

void draw_badges_screen(sf::RenderWindow& window, int selectioned, std::map<int, bool> winned_badges)
{
	draw_background(window);

	draw_status_box(window);

	draw_status(window);

	draw_badges_box(window);

	draw_badges(window, selectioned, winned_badges);
}

void draw_background(sf::RenderWindow& window)
{
	sf::Sprite background;
	sf::Texture* background_texture = AssetManager::getInstance()->loadTexture(BADGET_BACKGROUND_TEXTURE);
	
	background.setTexture(*background_texture);
	background.setPosition(0, 0);

	window.draw(background);
}

void draw_status_box(sf::RenderWindow& window)
{
	short x = 16;
	short y = 12;
	sf::Sprite box_sprite;
	sf::Texture* box_texture = AssetManager::getInstance()->loadTexture(BOX_SPRITES);

	char text_width = box_texture->getSize().x / 7;

	box_sprite.setTexture(*box_texture);

	for (int i = 1;i <= 7; i++) {
		for (int j = 1; j <= 19; j++) {

			box_sprite.setPosition(x, y);
			box_sprite.setTextureRect(sf::IntRect(text_width * 0, 0, text_width, SPRITE_SIZE));

			if ((i == 1) && (j == 1))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 1, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 1) && (j == 19))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 2, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 7) && (j == 1))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 3, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 7) && (j == 19))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 4, 0, text_width, SPRITE_SIZE));
			}

			if ((i == 1 || i == 7) && (j != 1 && j != 19)) {
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 5, 0, text_width, SPRITE_SIZE));
			}

			if ((i != 1 && i != 7) && (j == 1 || j == 19)) {
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 6, 0, text_width, SPRITE_SIZE));
			}

			window.draw(box_sprite);
			x += text_width;
		}
		x = 16;
		y += text_width;
	}
}

void draw_status(sf::RenderWindow& window)
{
	write_text(48, 58, "Medallas: 0/8", window);
	write_text(48, 110, "Alto mando: 0/4", window);
	write_text(48, 162, "Campeones: 0/2", window);
}

void draw_badges_box(sf::RenderWindow& window)
{
	short x = 48;
	short y = 12 + (8 * SPRITE_SIZE);
	sf::Sprite box_sprite;
	sf::Texture* box_texture = AssetManager::getInstance()->loadTexture(BOX_SPRITES);

	char text_width = box_texture->getSize().x / 7;

	box_sprite.setTexture(*box_texture);

	for (int i = 1;i <= 7; i++) {
		for (int j = 1; j <= 17; j++) {

			box_sprite.setPosition(x, y);
			box_sprite.setTextureRect(sf::IntRect(text_width * 0, 0, text_width, SPRITE_SIZE));

			if ((i == 1) && (j == 1))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 1, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 1) && (j == 17))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 2, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 7) && (j == 1))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 3, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 7) && (j == 17))
			{
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 4, 0, text_width, SPRITE_SIZE));
			}

			if ((i == 1 || i == 7) && (j != 1 && j != 17)) {
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 5, 0, text_width, SPRITE_SIZE));
			}

			if ((i != 1 && i != 7) && (j == 1 || j == 17)) {
				box_sprite.setPosition(x, y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 6, 0, text_width, SPRITE_SIZE));
			}

			window.draw(box_sprite);
			x += text_width;
		}
		x = 48;
		y += text_width;
	}
}

void draw_badges(sf::RenderWindow& window, int selectioned, std::map<int, bool> winned_badges)
{
	short x = 96;
	short y = 300;
	
	sf::Sprite badget_sprite;
	sf::Texture* badget_texture;

	for (int i = 1; i <= 8; i++)
	{
		if (selectioned == 10) {
			int a = 5;
		}
		switch (i) 
		{
			case 1:
				if (selectioned == i) 
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i-1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BOULDER_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_BOULDER_BADGET);
				}
				break;
			case 2:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(CASCADE_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_CASCADE_BADGET);
				}
				break;
			case 3:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(THUNDER_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_THUNDER_BADGET);
				}
				break;
			case 4:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(RAINBOW_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_RAINBOW_BADGET);
				}
				break;
			case 5:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(SOUL_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_SOUL_BADGET);
				}
				break;
			case 6:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(MARSH_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_MARSH_BADGET);
				}
				break;
			case 7:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(VOLCANO_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_VOLCANO_BADGET);
				}
				break;
			case 8:
				if (selectioned == i)
				{
					draw_frame(x, y, window);
				}
				if (winned_badges[i - 1])
				{
					badget_texture = AssetManager::getInstance()->loadTexture(EARTH_BADGET);
				}
				else
				{
					badget_texture = AssetManager::getInstance()->loadTexture(BLOCKED_EARTH_BADGET);
				}
				break;
		}

		badget_sprite.setTexture(*badget_texture);
		badget_sprite.setPosition(x, y);

		window.draw(badget_sprite);

		if (i == 4)
		{
			x = 96;
			y = 388;
		}
		else 
		{
			x += 128;
		}
	}
}

void draw_frame(int x, int y, sf::RenderWindow& window)
{
	sf::Sprite frame_sprite;
	sf::Texture* frame_texture;

	frame_texture = AssetManager::getInstance()->loadTexture(BADGET_SELECTION_FRAME);
	frame_sprite.setTexture(*frame_texture);

	frame_sprite.setPosition(x-4.f, y-4.f);
	window.draw(frame_sprite);
}