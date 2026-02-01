#include <Core/AssetManager.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <UI/Text.h>
#include <Utils/Constants.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>
#include <Panels/Interfaces.h>
#include <Gameplay/Pokemons/Pokemon.h>

void write_text(int x, int y, const std::string& text, sf::RenderWindow& window)
{
	short text_x;
	short text_y;

	sf::Sprite text_sprite;

	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);

	text_x = x;
	text_y = y;
	

	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(text_x, text_y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (*i - 32), 0, text_width, SPRITE_SIZE));

		text_x += text_width;

		window.draw(text_sprite);
	}

}

void write_rival_name(const std::string& text, sf::RenderWindow& window)
{

	short rival_x = 33;
	short rival_y = 0;

	sf::Sprite text_sprite;
	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);

	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(rival_x, rival_y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (std::toupper(*i) - 32), 0, text_width, SPRITE_SIZE));

		rival_x += text_width;

		window.draw(text_sprite);
	}

}

void write_player_name(const std::string& text, sf::RenderWindow& window)
{

	short player_x = 321;
	short player_y = 225;

	sf::Sprite text_sprite;
	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);


	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(player_x, player_y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (std::toupper(*i) - 32), 0, text_width, SPRITE_SIZE));

		player_x += text_width;

		window.draw(text_sprite);
	}
}

void write_player_hp(Pokemon* player, sf::RenderWindow& window)
{

	short x;
	
	if (player->get_hp() >= 100)
	{
		x = 353;
	}
	else if (player->get_hp() >= 10 && player->get_hp() < 100)
	{
		x = 385;
	}
	else
	{
		x = 417;
	}

	short y = 321;

	std::string text;
	
	if(player->get_max_hp() >= 100)
	{
		text += std::to_string(player->get_hp()) + "/" + std::to_string(player->get_max_hp());
	}
	else if(player->get_max_hp() >= 10 && player->get_max_hp() < 100)
	{
		text = std::to_string(player->get_hp()) + "/ " + std::to_string(player->get_max_hp());
	}
	else
	{
		text = std::to_string(player->get_hp()) + "/  " + std::to_string(player->get_max_hp());
	}

	sf::Sprite text_sprite;
	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);

	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(x, y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (std::toupper(*i) - 32), 0, text_width, SPRITE_SIZE));

		x += text_width;

		window.draw(text_sprite);
	}
}

void write_mayus_text(int x, int y, const std::string& text, sf::RenderWindow& window)
{
	short player_x = x;
	short player_y = y;

	sf::Sprite text_sprite;
	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);


	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(player_x, player_y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (std::toupper(*i) - 32), 0, text_width, SPRITE_SIZE));

		player_x += text_width;

		window.draw(text_sprite);
	}
}

void write_stat_text(int x, int y, const std::string& text, sf::RenderWindow& window)
{
	short player_x = x;
	short player_y = y;

	sf::Sprite text_sprite;
	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);


	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(player_x, player_y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (std::toupper(*i) - 32), 0, text_width, SPRITE_SIZE));

		player_x += text_width;

		text_sprite.setScale(1.f, 0.7f);
		window.draw(text_sprite);
	}//sprite.setScale(0.8f, 0.8f); Reducido al 80%
}

void write_pkmn_menu_hp(int x, int y, Pokemon* pkmn, sf::RenderWindow& window)
{
	short text_x;
	if (pkmn->get_hp() >= 100)
	{
		text_x = x + 385;
	}
	else if (pkmn->get_hp() >= 10 && pkmn->get_hp() < 100)
	{
		text_x = 417;
	}
	else
	{
		text_x = 449;
	}

	short text_y = y + 33;

	std::string text;

	if (pkmn->get_max_hp() >= 100)
	{
		text += std::to_string(pkmn->get_hp()) + "/" + std::to_string(pkmn->get_max_hp());
	}
	else if (pkmn->get_max_hp() >= 10 && pkmn->get_max_hp() < 100)
	{
		text = std::to_string(pkmn->get_hp()) + "/ " + std::to_string(pkmn->get_max_hp());
	}
	else
	{
		text = std::to_string(pkmn->get_hp()) + "/  " + std::to_string(pkmn->get_max_hp());
	}

	sf::Sprite text_sprite;
	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);

	for (std::string::const_iterator i = text.begin(); i != text.end(); i++)
	{

		text_sprite.setPosition(text_x, text_y);
		text_sprite.setTextureRect(sf::IntRect(text_width * (*i - 32), 0, text_width, SPRITE_SIZE));

		text_x += text_width;

		window.draw(text_sprite);
	}
}

void draw_textbox(const std::string& text, int last_row, sf::RenderWindow& window)
{
	draw_box_interface(0, TEXT_BOX_Y * SPRITE_SIZE, TEXT_BOX_X, 20, window);
	sf::Sprite text_sprite;

	sf::Texture* font_texture = AssetManager::getInstance()->loadTexture(FONT_SPRITES);

	char text_width = font_texture->getSize().x / 202;

	text_sprite.setTexture(*font_texture);

	short text_x = 33;
	short text_y = 449;

	//std::string parsed = parseEscapes(text);

	std::vector<std::string> texts = split_text(text);

	bool waiting = false;

	for (int i = 0; i < texts.size(); ++i) 
	{
		if (i==last_row || i==last_row-1)
		{
				float currentX = text_x;

				for (std::string::const_iterator j = texts[i].begin(); j != texts[i].end(); j++)
				{
					char c = *j;
					if (c != ' ')
					{
						text_sprite.setPosition(currentX, text_y + ((i % 2) * (text_width * 2.f)));

						text_sprite.setTextureRect(sf::IntRect(text_width * (c - 32), 0, text_width, SPRITE_SIZE));
						window.draw(text_sprite);
					}
					currentX += text_width;
				}
			
		}
		
	}

}

std::vector<std::string> split_text(std::string text)
{
	std::vector<std::string> lines;
	std::string currentLine;
	int currentLineLength = 0;

	std::string word;
	for (size_t i = 0; i < text.size(); ++i) 
	{
		char c = text[i];

		if (c == ' ' || c == '\n' || c == '\t') 
		{
		
			if (!word.empty())
			{
				if (currentLineLength + word.length() <= 17) 
				{
					if (!currentLine.empty()) 
					{
						currentLine += " ";
						currentLineLength += 1;
					}
					currentLine += word;
					currentLineLength += static_cast<int>(word.length());
				}
				else 
				{
					lines.push_back(currentLine);
					currentLine = word;
					currentLineLength = static_cast<int>(word.length());
				}
				word.clear();
			}
			else
			{
				currentLineLength = 17;
			}

			if (c != '\n')
			{
				continue;
			}

		}
		else 
		{
			word += c;
		}
	}

	if (!word.empty()) {
		if (currentLineLength + word.length() <= 17)
		{
			if (!currentLine.empty()) 
			{
				currentLine += " ";
			}
			currentLine += word;
		}
		else 
		{
			lines.push_back(currentLine);
			currentLine = word;
		}
	}

	if (!currentLine.empty())
	{
		lines.push_back(currentLine);
	}

	return lines;
}

int get_lines_num(std::string text)
{
	std::vector<std::string> lines;
	std::string currentLine;
	int currentLineLength = 0;

	std::string word;
	for (size_t i = 0; i < text.size(); ++i)
	{
		char c = text[i];

		if (c == ' ' || c == '\n' || c == '\t')
		{

			if (!word.empty())
			{
				if (currentLineLength + word.length() <= 17)
				{
					if (!currentLine.empty())
					{
						currentLine += " ";
						currentLineLength += 1;
					}
					currentLine += word;
					currentLineLength += static_cast<int>(word.length());
				}
				else
				{
					lines.push_back(currentLine);
					currentLine = word;
					currentLineLength = static_cast<int>(word.length());
				}
				word.clear();
			}
			else
			{
				currentLineLength = 17;
			}

			if (c != '\n')
			{
				continue;
			}

		}
		else
		{
			word += c;
		}
	}

	if (!word.empty()) {
		if (currentLineLength + word.length() <= 17)
		{
			if (!currentLine.empty())
			{
				currentLine += " ";
			}
			currentLine += word;
		}
		else
		{
			lines.push_back(currentLine);
			currentLine = word;
		}
	}

	if (!currentLine.empty())
	{
		lines.push_back(currentLine);
	}
	return static_cast<int>(lines.size());
}

std::string stat_text(stats s)
{
	switch (s)
	{
		case stats::attack:
			return "ATAQUE";
			break;
		case stats::defense:
			return "DEFENSA";
			break;
		case stats::special_attack:
			return "AT.ESP.";
			break;
		case stats::special_defense:
			return "DEF.ESP.";
			break;
		case stats::velocity:
			return "VELOCID.";
			break;

		default:
			return "";
			break;
	}


}

std::string type_text(type t)
{
	std::string type_name;

	switch (t)
	{
	case type::steel:
		type_name = "ACERO";
		break;
	case type::water:
		type_name = "AGUA";
		break;
	case type::bug:
		type_name = "BICHO";
		break;
	case type::dragon:
		type_name = "DRAGÓN";
		break;
	case type::electric:
		type_name = "ELÉCTRIC";
		break;
	case type::ghost:
		type_name = "FANTASMA";
		break;
	case type::fairy:
		type_name = "HADA";
		break;
	case type::fire:
		type_name = "FUEGO";
		break;
	case type::ice:
		type_name = "HIELO";
		break;
	case type::fighting:
		type_name = "LUCHA";
		break;
	case type::normal:
		type_name = "NORMAL";
		break;
	case type::grass:
		type_name = "PLANTA";
		break;
	case type::psychic:
		type_name = "PSÍQUICO";
		break;
	case type::rock:
		type_name = "ROCA";
		break;
	case type::dark:
		type_name = "SINIESTR";
		break;
	case type::ground:
		type_name = "TIERRA";
		break;
	case type::poison:
		type_name = "VENENO";
		break;
	case type::flying:
		type_name = "VOLADOR";
		break;
	case type::null_type:
		type_name = "-";
		break;

	}

	return type_name;
}