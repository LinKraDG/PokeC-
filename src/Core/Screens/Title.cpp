#include <Core/AssetManager.h>
#include <Core/Screens/Title.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Utils/Constants.h>
#include <UI/Text.h>

void draw_title_screen(sf::RenderWindow& window, int selectioned)
{
	draw_title_background(window);
	draw_title(window);
	draw_selections(window, selectioned);
}

void draw_title_background(sf::RenderWindow& window)
{
	sf::Sprite background;
	sf::Texture* background_texture = AssetManager::getInstance()->loadTexture(BLANK_BACKGROUND_TEXTURE);

	background.setTexture(*background_texture);
	background.setPosition(0, 0);

	window.draw(background);
}

void draw_title(sf::RenderWindow& window)
{
	sf::Sprite title;
	sf::Texture* title_texture = AssetManager::getInstance()->loadTexture(TITLE_TEXTURE);

	title.setTexture(*title_texture);
	title.setPosition(64, 32);

	window.draw(title);
}

void draw_selections(sf::RenderWindow& window, int selectioned)
{
	sf::Sprite selection;
	sf::Texture* selection_texture = AssetManager::getInstance()->loadTexture(SELECTION_SPRITE);
	selection.setTexture(*selection_texture);

	switch (selectioned) 
	{
		case 1:
			selection.setPosition(128, 270);
			break;
		case 2:
			selection.setPosition(128, 320);
			break;
	}

	selection.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	window.draw(selection);

	write_text(160, 270, "La liga ", window);
	write_text(160, 320, "Salir", window);
}
