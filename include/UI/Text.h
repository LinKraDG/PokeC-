#pragma once
#include <string>
#include <vector>
#include <Utils/Constants.h>

namespace sf
{
	class RenderWindow;
}
class Pokemon;

void write_text(int x, int y, const std::string& text, sf::RenderWindow& window);

void write_rival_name(const std::string& text, sf::RenderWindow& window);

void write_player_name(const std::string& text, sf::RenderWindow& window);

void write_player_hp(Pokemon* player, sf::RenderWindow& window);

void write_mayus_text(int x, int y, const std::string& text, sf::RenderWindow& window);

void write_stat_text(int x, int y, const std::string& text, sf::RenderWindow& window);

void write_pkmn_menu_hp(int x, int y, Pokemon* pkmn, sf::RenderWindow& window);

void draw_textbox(const std::string& text, int last_row, sf::RenderWindow& window);

std::vector<std::string> split_text(std::string text);

int get_lines_num(std::string text);

std::string stat_text(stats s);

std::string type_text(type t);