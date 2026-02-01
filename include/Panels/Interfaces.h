#pragma once
#include <array>
#include <string>
//#include <Gameplay/Moves/Move.h>

class Pokemon;
class Move;

namespace sf
{
	class RenderWindow;
}

void draw_box_interface(int x, int y, int width, int height, sf::RenderWindow& window);

void draw_combat_select_interface(sf::RenderWindow& window, int selectioned);

void draw_combat_move_interface(sf::RenderWindow& window, std::array<Move*, 4> moves, int selectioned);

void draw_combat_change_poke_interface(sf::RenderWindow& window, std::array<Pokemon*, 6> pokemons, int selectioned, bool selected, char time, int action = 0);

void draw_pokemon_status_interface(sf::RenderWindow& window, Pokemon* pokemon, int screen);

void draw_stat_status_interface(sf::RenderWindow& window, Pokemon* pokemon);

void draw_moves_status_interface(sf::RenderWindow& window, Pokemon* pokemon);
