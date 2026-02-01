#pragma once
#include <Core/AssetManager.h>
#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Gameplay/Moves/Damage_move.h>
#include <array>

class Rival;
class Pokemon;

class Combat
{
public:

	~Combat();

	Combat(int id);

	void Init();
	void update();
	void render(sf::RenderWindow& window);


	// Combat updates
	void turn();

	void select_move();
	void move_confirmed();

	void select_action();
	void action_confirmed();

	void select_poke();
	void select_poke_action();
	void change_pokemon();
	void poke_confirmed();
	void poke_action_confirmed();

	bool calc_hit(Move* attack, Pokemon* aggressor, Pokemon* defensor);
	bool calc_crit(Damage_Move* attack);

	void turn_order();

	void player_attack();
	void rival_attack();

	void rival_poke_change();
	void player_first_poke();
	void player_poke_change();

	void end_turn_actions();
	void reset_turn_param();


	// Visual
	void draw_hud(sf::RenderWindow& window);

	void draw_presentation(sf::RenderWindow& window);
	void draw_transition(sf::RenderWindow& window);
	void draw_poke_change(sf::RenderWindow& window);

	void draw_turn(sf::RenderWindow& window);

	void draw_frames(sf::RenderWindow& window);
	void draw_levels(sf::RenderWindow& window);
	std::string problem_spr(Pokemon* poke);

	void pokemon_preview(sf::RenderWindow& window, bool is_first);

	void change_text_state();
	void update_text();

	void player_sprite_update();

	void draw_text(sf::RenderWindow& window);
	void draw_battle_text(sf::RenderWindow& window, std::string text);


	// Getters/Setters
	std::string get_text();
	void set_text(std::string new_text);
	std::string get_rival_text();
	void set_rival_text(std::string new_text);
	std::string get_player_text();
	void set_player_text(std::string new_text);

	short get_current_animation_time();
	void set_current_animation_time(short current_time);

	bool get_victory();
	void set_victory(bool winned);

	bool get_defeated();
	void set_defeated(bool defeat);

	int get_accuracy(Pokemon* poke);
	int get_evasion(Pokemon* poke);

private:
	sf::Sprite player_sprite;
	sf::Texture* player_texture{ nullptr };

	sf::Sprite player_ps_text_sprite;
	sf::Sprite rival_ps_text_sprite;
	sf::Sprite player_level_text_sprite;
	sf::Sprite rival_level_text_sprite;
	sf::Texture* ps_text_texture{ nullptr };
	sf::Texture* level_text_texture{ nullptr };

	sf::Sprite rival_frame;
	sf::Sprite player_pres_frame;
	sf::Sprite player_frame;
	sf::Texture* rival_frame_texture{ nullptr };
	sf::Texture* player_pres_frame_texture{ nullptr };
	sf::Texture* player_frame_texture{ nullptr };


	sf::Sprite player_bar_sprite;
	sf::Sprite rival_bar_sprite;
	sf::Texture* health_bar_texture{ nullptr };
	sf::RectangleShape rival_bar;
	sf::RectangleShape rival_hp_bar;
	sf::RectangleShape player_bar;
	sf::RectangleShape player_hp_bar;

	sf::Sprite preview_sprite;
	sf::Texture* have_preview_texture{ nullptr };
	sf::Texture* null_preview_texture{ nullptr };
	sf::Texture* fainted_preview_texture{ nullptr };

	Rival* rival;

	Pokemon* act_rival_pokemon{ nullptr };
	Pokemon* act_player_pokemon{ nullptr };

	std::array<int, 6> rival_pokemon_preview;
	std::array<int, 6> player_pokemon_preview;

	std::array<Pokemon*, 6> player_pokemons;

	Move* rival_move{ nullptr };
	Move* player_move{ nullptr };

	int marked_selection;
	int selectioned_action;

	int marked_move;
	int selectioned_move;

	int marked_poke;
	int marked_poke_action;
	int selectioned_poke;
	int selectioned_poke_action;

	int status_screen;

	bool turn_confirmed = false;
	bool turn_completed = false;
	bool poke_changed = false;
	bool end_turn = false;
	bool rival_presentation = true;
	bool poke_transition = false;
	bool first_poke_transition = false;

	int move_text = 0;

	int fainted_pokes;

	bool victory;
	bool defeated;

	bool text_state;
	int act_text_row;

	int order;
	bool player_turn = false;
	bool rival_turn = false;

	char current_time;
	short current_animation_time;

	std::string general_texts;
	std::string player_texts;
	std::string rival_texts;
};