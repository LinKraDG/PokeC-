#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Panels/Interfaces.h>
#include <Gameplay/Moves/Move.h>
#include <Utils/Constants.h>
#include <UI/Text.h>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <algorithm>
#include <cctype>
#include <Gameplay/Pokemons/Pokemon.h>
#include <Core/AssetManager.h>


void draw_box_interface(int x, int y, int width, int height, sf::RenderWindow& window)
{

	short sprite_x = x;
	short sprite_y = y;
	sf::Sprite box_sprite;
	sf::Texture* box_texture = AssetManager::getInstance()->loadTexture(BOX_SPRITES);

	char text_width = box_texture->getSize().x / 7;

	box_sprite.setTexture(*box_texture);

	for (int i = 1;i <= width; i++) {
		for (int j = 1; j <= height; j++) {

			box_sprite.setPosition(sprite_x, sprite_y);
			box_sprite.setTextureRect(sf::IntRect(text_width * 0,0, text_width, SPRITE_SIZE));

			if ((i == 1) && (j == 1))
			{
				box_sprite.setPosition(sprite_x, sprite_y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 1, 0, text_width, SPRITE_SIZE));
			}
			if ((i == 1) && (j == height))
			{
				box_sprite.setPosition(sprite_x, sprite_y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 2, 0, text_width, SPRITE_SIZE));
			}
			if ((i == width) && (j == 1))
			{
				box_sprite.setPosition(sprite_x, sprite_y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 3, 0, text_width, SPRITE_SIZE));
			}
			if ((i == width) && (j == height))
			{
				box_sprite.setPosition(sprite_x, sprite_y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 4, 0, text_width, SPRITE_SIZE));
			}

			if ((i == 1 || i == width) && (j != 1 && j != height)) {
				box_sprite.setPosition(sprite_x, sprite_y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 5, 0, text_width, SPRITE_SIZE));
			}

			if ((i != 1 && i != width) && (j == 1 || j == height)) {
				box_sprite.setPosition(sprite_x, sprite_y);
				box_sprite.setTextureRect(sf::IntRect(text_width * 6, 0, text_width, SPRITE_SIZE));
			}

			window.draw(box_sprite);
			sprite_x +=text_width;
		}
		sprite_x = x;
		sprite_y +=text_width;
	}

}

void draw_combat_select_interface(sf::RenderWindow& window, int selectioned)
{
	draw_box_interface(0, TEXT_BOX_Y*SPRITE_SIZE, TEXT_BOX_X, TEXT_BOX_Y, window);

	draw_box_interface(257, TEXT_BOX_Y*SPRITE_SIZE, 6, 12, window);

	sf::Sprite selection;
	sf::Texture* selection_texture = AssetManager::getInstance()->loadTexture(SELECTION_SPRITE);
	selection.setTexture(*selection_texture);

	switch (selectioned)
	{
	case 1:
		selection.setPosition(291, 449);
		break;
	case 2:
		selection.setPosition(483, 449);
		break;
	case 3:
		selection.setPosition(291, 513);
		break;
	case 4:
		selection.setPosition(483, 513);
		break;
	}

	selection.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	window.draw(selection);

	write_text(323, 449, "LUCHA", window);
	write_text(515, 449, "PK", window);
	write_text(323, 513, "OBJ.", window);
	write_text(515, 513, "ESC", window);

}

void draw_combat_move_interface(sf::RenderWindow& window, std::array<Move*, 4> moves, int selectioned)
{
	draw_box_interface(0, TEXT_BOX_Y * SPRITE_SIZE, TEXT_BOX_X, TEXT_BOX_Y, window);

	draw_box_interface(129, TEXT_BOX_Y * SPRITE_SIZE, 6, 16, window);

	sf::Sprite selection;
	sf::Texture* selection_texture = AssetManager::getInstance()->loadTexture(SELECTION_SPRITE);
	selection.setTexture(*selection_texture);

	switch (selectioned)
	{
	case 1:
		selection.setPosition(161, 417);
		break;
	case 2:
		selection.setPosition(161, 449);
		break;
	case 3:
		selection.setPosition(161, 481);
		break;
	case 4:
		selection.setPosition(161, 513);
		break;
	}

	selection.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	window.draw(selection);
	
	
	write_text(193, 417, moves[0]->get_name(), window);
	if (moves[1] == NULL) 
	{
		write_text(193, 449, "-", window);
	}
	else
	{
		write_text(193, 449, moves[1]->get_name(), window);
	}
	if (moves[2] == NULL)
	{
		write_text(193, 481, "-", window);
	}
	else
	{
		write_text(193, 481, moves[2]->get_name(), window);
	}
	if (moves[3] == NULL)
	{
		write_text(193, 513, "-", window);
	}
	else
	{
		write_text(193, 513, moves[3]->get_name(), window);
	}
	draw_box_interface(0, 257, 5, 11, window);
	
	write_text(33, 289, "TIPO/", window);
	if (moves[selectioned-1] == NULL)
	{
		write_text(65, 321, "-", window);
	}
	else
	{
		write_text(65, 321, type_text(moves[selectioned-1]->get_type()), window);
	}

	if (moves[selectioned - 1] == NULL)
	{
		write_text(193, 353, "-", window);
		write_text(225, 353, "/", window);
		write_text(257, 353, "-", window);
	}
	else
	{
		if(moves[selectioned - 1]->get_pp()>=10)
		{
			write_text(161, 353, std::to_string(moves[selectioned - 1]->get_pp()), window);
		}
		else
		{
			write_text(193, 353, std::to_string(moves[selectioned - 1]->get_pp()), window);
		}

		write_text(225, 353, "/", window);
		write_text(257, 353, std::to_string(moves[selectioned - 1]->get_max_pp()), window);
	}

}

void draw_combat_change_poke_interface(sf::RenderWindow& window, std::array<Pokemon*, 6> pokemons, int selectioned, bool selected, char time, int action)
{
	window.clear();
	sf::Texture* background_texture = AssetManager::getInstance()->loadTexture(BLANK_BACKGROUND_TEXTURE);
	sf::Sprite background;
	background.setTexture(*background_texture);
	background.setPosition(0, 0);
	window.draw(background);
	draw_textbox("Elige un POKéMON.", 1, window);

	sf::Sprite poke_selected;
	sf::Sprite action_selected;
	sf::Texture* selection_texture = AssetManager::getInstance()->loadTexture(SELECTION_SPRITE);
	poke_selected.setTexture(*selection_texture);
	action_selected.setTexture(*selection_texture);

	sf::Texture* health_bar_texture = AssetManager::getInstance()->loadTexture(HEALTH_BAR_TEXTURE);
	sf::Texture* ps_text_texture = AssetManager::getInstance()->loadTexture(PS_TEXT_TEXTURE);
	sf::Texture* level_text_texture = AssetManager::getInstance()->loadTexture(LEVEL_TEXT_TEXTURE);
	
	sf::Sprite health_bar_sprite;
	health_bar_sprite.setTexture(*health_bar_texture);
	sf::Sprite ps_text_sprite;
	ps_text_sprite.setTexture(*ps_text_texture);;
	sf::Sprite level_text_sprite;
	level_text_sprite.setTexture(*level_text_texture);;
	
	sf::RectangleShape bar;
	bar.setSize(sf::Vector2f(192, 8));
	bar.setFillColor(sf::Color::White);
	sf::RectangleShape hp_bar;
	
	
	int x = 33;
	int y = 1;

	for (int i = 0; i < 6; i++)
	{
		pokemons[i]->set_icon_position(x, y);
		pokemons[i]->set_icon_texture(time);
		window.draw(pokemons[i]->get_icon_sprite());
		std::string name = pokemons[i]->get_name();
		std::string upper_name = "";
		for (std::string::const_iterator j = name.begin(); j != name.end(); j++)
		{
			upper_name += std::toupper(*j);
		}
		write_text(x + 64, y, upper_name, window);
		level_text_sprite.setPosition(x + 384.f, static_cast<float>(y));
		window.draw(level_text_sprite);
		write_text(x + 416, y, std::to_string(pokemons[i]->get_level()), window);
		ps_text_sprite.setPosition(x + 96.f, y + 32.f);
		window.draw(ps_text_sprite);
		health_bar_sprite.setPosition(x + 156.f, y + 40.f);
		window.draw(health_bar_sprite);
		bar.setPosition(x + 160.f,y + 44.f);

		int ps_percent = (100 * pokemons[i]->get_hp()) / pokemons[i]->get_max_hp();

		hp_bar.setSize(sf::Vector2f((ps_percent * 192.f) / 100.f, 8.f));
		if (ps_percent > 50)
		{
			hp_bar.setFillColor(sf::Color::Green);
		}
		else if (ps_percent > 25 && ps_percent <= 50)
		{
			hp_bar.setFillColor(sf::Color::Yellow);
		}
		else
		{
			hp_bar.setFillColor(sf::Color::Red);
		}

		hp_bar.setPosition(x + 160.f, y + 44.f);
		window.draw(bar);
		window.draw(hp_bar);

		write_pkmn_menu_hp(x, y, pokemons[i], window);

		y += 64;
	}
	
	poke_selected.setPosition(0.f, 33.f + ((selectioned - 1.f) * 64.f));
	
	if (selected)
	{
		poke_selected.setTextureRect(sf::IntRect(33, 0, SPRITE_SIZE, SPRITE_SIZE));
	}
	else
	{
		poke_selected.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	window.draw(poke_selected);

	if (selected)
	{
		draw_box_interface(353, (TEXT_BOX_Y - 1) * SPRITE_SIZE, 7, 9, window);
		
		write_text(417, 385, "CAMBIO", window);
		write_text(417, 449, "ESTAD.", window);
		write_text(417, 513, "SALIR", window);
		
		switch (action)
		{
			case 1:
				action_selected.setPosition(385, 385);
				break;
			case 2:
				action_selected.setPosition(385, 449);
				break;
			case 3:
				action_selected.setPosition(385, 513);
				break;
		}
		action_selected.setTextureRect(sf::IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
		window.draw(action_selected);
	}

}

void draw_pokemon_status_interface(sf::RenderWindow& window, Pokemon* pokemon, int screen)
{
	window.clear();
	sf::Texture* background_texture = AssetManager::getInstance()->loadTexture(BLANK_BACKGROUND_TEXTURE);
	sf::Texture* s_frame_texture = AssetManager::getInstance()->loadTexture(S_STATUS_FRAME_TEXTURE);
	sf::Texture* pokemon_no_texture = AssetManager::getInstance()->loadTexture(NO_TEXTURE);

	sf::Sprite background;
	sf::Sprite s_frame_sprite;
	sf::Sprite pokemon_no_sprite;
	background.setTexture(*background_texture);
	background.setPosition(0, 0);
	window.draw(background);

	sf::Sprite status_sprite = pokemon->get_front_sprite();
	sf::IntRect rect = pokemon->get_front_sprite().getTextureRect();
	status_sprite.setPosition(32, 0);
	status_sprite.setTextureRect(sf::IntRect(rect.width, 0, -rect.width, rect.height));

	s_frame_sprite.setTexture(*s_frame_texture);
	s_frame_sprite.setPosition(256,0);
	pokemon_no_sprite.setTexture(*pokemon_no_texture);
	pokemon_no_sprite.setPosition(32,224);

	window.draw(status_sprite);
	window.draw(pokemon_no_sprite);
	if (pokemon->get_pokedex() >= 100)
	{
		write_text(64, 224, "." + std::to_string(pokemon->get_pokedex()), window);
	}
	else if (pokemon->get_pokedex() >= 10) 
	{
		write_text(64, 224, ".0" + std::to_string(pokemon->get_pokedex()), window);
	}
	else
	{
		write_text(64, 224, ".00" + std::to_string(pokemon->get_pokedex()), window);
	}

	window.draw(s_frame_sprite);

	write_mayus_text(288, 32, pokemon->get_name(), window);

	switch (screen)
	{
		case 1:
			draw_stat_status_interface(window, pokemon);
			break;
		case 2:
			draw_moves_status_interface(window, pokemon);
			break;
	}
	

}

void draw_stat_status_interface(sf::RenderWindow& window, Pokemon* pokemon)
{
	// Up Right side
	sf::Texture* level_texture = AssetManager::getInstance()->loadTexture(LEVEL_TEXT_TEXTURE);
	sf::Texture* ps_texture = AssetManager::getInstance()->loadTexture(PS_TEXT_TEXTURE);
	sf::Texture* id_texture = AssetManager::getInstance()->loadTexture(ID_TEXTURE);
	sf::Texture* no_texture = AssetManager::getInstance()->loadTexture(NO_TEXTURE);
	sf::Texture* hp_bar_texture = AssetManager::getInstance()->loadTexture(HEALTH_BAR_TEXTURE);

	sf::Sprite level_sprite;
	sf::Sprite ps_sprite;
	sf::Sprite id_sprite;
	sf::Sprite no_sprite;

	sf::Sprite hp_bar_sprite;
	sf::RectangleShape background_bar;
	sf::RectangleShape hp_bar;

	std::string hp_text = "";
	std::string status_text = "";

	background_bar.setSize(sf::Vector2f(192, 8));
	hp_bar.setSize(sf::Vector2f(192, 8));
	background_bar.setPosition(416, 108);
	hp_bar.setPosition(416, 108);

	int hp_percent = (100 * pokemon->get_hp()) / pokemon->get_max_hp();
	hp_bar.setSize(sf::Vector2f((hp_percent * 192.f) / 100.f, 8.f));
	background_bar.setFillColor(sf::Color::White);
	if (hp_percent > 50)
	{
		hp_bar.setFillColor(sf::Color::Green);
	}
	else if (hp_percent > 25 && hp_percent <= 50)
	{
		hp_bar.setFillColor(sf::Color::Yellow);
	}
	else
	{
		hp_bar.setFillColor(sf::Color::Red);
	}
	
	level_sprite.setTexture(*level_texture);
	ps_sprite.setTexture(*ps_texture);
	id_sprite.setTexture(*id_texture);
	no_sprite.setTexture(*no_texture);
	hp_bar_sprite.setTexture(*hp_bar_texture);

	level_sprite.setPosition(448, 64);
	window.draw(level_sprite);
	write_text(480, 64, std::to_string(pokemon->get_level()), window);

	ps_sprite.setPosition(352, 96);
	hp_bar_sprite.setPosition(412, 104);

	if (pokemon->get_hp()>=100)
	{
		hp_text += std::to_string(pokemon->get_hp());
	}
	else if (pokemon->get_hp() >= 10)
	{
		hp_text += " " + std::to_string(pokemon->get_hp());
	}
	else
	{
		hp_text += "  " + std::to_string(pokemon->get_hp());
	}
	hp_text += "/";
	if (pokemon->get_max_hp() >= 100)
	{
		hp_text += std::to_string(pokemon->get_max_hp());
	}
	else if (pokemon->get_max_hp() >= 10)
	{
		hp_text += " " + std::to_string(pokemon->get_max_hp());
	}
	else
	{
		hp_text += "  " + std::to_string(pokemon->get_max_hp());
	}

	if (pokemon->get_fainted())
	{
		status_text += "ESTADO/DEB";
	}
	else if (pokemon->get_status_problem() != status_problems::null_problem)
	{
		switch (pokemon->get_status_problem())
		{
			case status_problems::asleep:
				status_text += "ESTADO/DOR";
				break;
			case status_problems::poisoned:
				status_text += "ESTADO/ENV";
				break;
			case status_problems::badly_poisoned:
				status_text += "ESTADO/ENV";
				break;
			case status_problems::burned:
				status_text += "ESTADO/QUE";
				break;
			case status_problems::paralyzed:
				status_text += "ESTADO/PAR";
				break;
			case status_problems::frozen:
				status_text += "ESTADO/CON";
				break;
		}
	}
	else
	{
		status_text += "ESTADO/OK";
	}

	window.draw(ps_sprite);
	window.draw(hp_bar_sprite);
	window.draw(background_bar);
	window.draw(hp_bar);
	write_mayus_text(384, 128, hp_text, window);
	write_mayus_text(288, 192, status_text, window);

	// Down Left side
	draw_box_interface(0, 8 * SPRITE_SIZE, 10, 10, window);
	for (int i = 1; i <= 5; i++)
	{
		switch (i)
		{
			case 1:
				write_stat_text(32, (8 + 1) * 32 - 5, stat_text(static_cast<stats>(i)), window);
				write_stat_text(192, (8 + 2) * 32 - 10, std::to_string(static_cast<int>(pokemon->get_stats()[static_cast<stats>(i)])), window);
				break;

			case 2:
				write_stat_text(32, (8 + 3) * 32 - 15, stat_text(static_cast<stats>(i)), window);
				write_stat_text(192, (8 + 4) * 32 - 20, std::to_string(static_cast<int>(pokemon->get_stats()[static_cast<stats>(i)])), window);
				break;

			case 3:
				write_stat_text(32, (8 + 5) * 32 - 25, stat_text(static_cast<stats>(i)), window);
				write_stat_text(192, (8 + 6) * 32 - 30, std::to_string(static_cast<int>(pokemon->get_stats()[static_cast<stats>(i)])), window);
				break;

			case 4:
				write_stat_text(32, (8 + 7) * 32 - 35, stat_text(static_cast<stats>(i)), window);
				write_stat_text(192, (8 + 8) * 32 - 40, std::to_string(static_cast<int>(pokemon->get_stats()[static_cast<stats>(i)])), window);
				break;

			case 5:
				write_stat_text(32, (8 + 9) * 32 - 45, stat_text(static_cast<stats>(i)), window);
				write_stat_text(192, (8 + 10) * 32 - 50, std::to_string(static_cast<int>(pokemon->get_stats()[static_cast<stats>(i)])), window);
				break;

		}
	}

	//Down Right side
	sf::Texture* i_frame_texture = AssetManager::getInstance()->loadTexture(I_STATUS_FRAME_TEXTURE);
	sf::Sprite i_frame_sprite;
	i_frame_sprite.setTexture(*i_frame_texture);
	i_frame_sprite.setPosition(384, 288);
	window.draw(i_frame_sprite);

	write_mayus_text(10 * SPRITE_SIZE, 9 * SPRITE_SIZE, "TIPO1/", window);
	write_mayus_text(11 * SPRITE_SIZE, 10 * SPRITE_SIZE, type_text(pokemon->get_pokemon_types(0)), window);
	if (pokemon->get_pokemon_types(1) != type::null_type)
	{
		write_mayus_text(10 * SPRITE_SIZE, 11 * SPRITE_SIZE, "TIPO2/", window);
		write_mayus_text(11 * SPRITE_SIZE, 12 * SPRITE_SIZE, type_text(pokemon->get_pokemon_types(1)), window);
	}
}

void draw_moves_status_interface(sf::RenderWindow& window, Pokemon* pokemon)
{
	// Up Right side
	sf::Texture* level_texture = AssetManager::getInstance()->loadTexture(LEVEL_TEXT_TEXTURE);
	sf::Texture* a_texture = AssetManager::getInstance()->loadTexture(A_TEXTURE);

	sf::Sprite level_sprite;
	sf::Sprite a_sprite;

	level_sprite.setTexture(*level_texture);
	a_sprite.setTexture(*a_texture);


	write_mayus_text(288, 96, "PUNTOS EXP", window);
	write_mayus_text(288, 160, "SIG.NIVEL", window);

	a_sprite.setPosition(480, 192);
	level_sprite.setPosition(512, 192);

	write_mayus_text(416, 192, "0", window);
	window.draw(a_sprite);
	window.draw(level_sprite);
	write_mayus_text(544, 192, std::to_string(pokemon->get_level()+1), window);

	// Down side
	draw_box_interface(0, 8 * SPRITE_SIZE, 10, 20, window);

	for (int i = 0; i <= 3; i++)
	{
		std::string pp_text = "PP ";
		pp_text += std::to_string(pokemon->get_moves()[i]->get_pp()) + "/" + std::to_string(pokemon->get_moves()[i]->get_max_pp());
		
		switch (i)
		{
			case 0:
				write_mayus_text(64, 9 * SPRITE_SIZE, pokemon->get_moves()[i]->get_name(), window);
				write_mayus_text(352, 10 * SPRITE_SIZE, pp_text, window);
				break;
			case 1:
				write_mayus_text(64, 11 * SPRITE_SIZE, pokemon->get_moves()[i]->get_name(), window);
				write_mayus_text(352, 12 * SPRITE_SIZE, pp_text, window);
				break;
			case 2:
				write_mayus_text(64, 13 * SPRITE_SIZE, pokemon->get_moves()[i]->get_name(), window);
				write_mayus_text(352, 14 * SPRITE_SIZE, pp_text, window);
				break;
			case 3:
				write_mayus_text(64, 15 * SPRITE_SIZE, pokemon->get_moves()[i]->get_name(), window);
				write_mayus_text(352, 16 * SPRITE_SIZE, pp_text, window);
				break;
		}
		
		
	}
}
