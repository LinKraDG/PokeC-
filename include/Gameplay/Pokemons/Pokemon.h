#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Utils/Constants.h>
#include <array>
#include <map>

class Move;


class Pokemon
{
public:

	~Pokemon();

	Pokemon(int id);

	void Init();

	// Combat changes
	bool status_problem_effect();
	void reset_poison_turns();

	bool status_change_effect();
	void confuse_damage();

	void change_negative_hp(int amount);
	void change_positive_hp(int amount);
	void recoil_damage(int amount, recoil_heal_type base, int damage = 0);
	void recover_hp(int amount, recoil_heal_type base, int damage = 0);

	void end_turn_changes();


	// Getters/Setters
	void set_sprites();
	sf::Sprite get_front_sprite();
	sf::Sprite get_back_sprite();
	sf::Sprite get_icon_sprite();

	int get_pokedex();

	void set_level(int lvl);
	int get_level();

	void set_EVs();
	void set_IVs();

	void set_nature();

	void set_stats();
	std::map<stats, float> get_stats();

	void set_stat_change(int stat, int amount);
	int get_stat_change(int stat);

	void set_act_stats();
	std::map<stats, float> get_act_stats();

	void set_name(std::string pokemon_name);
	std::string get_name();

	void set_icon(std::string pokemon_icon);
	void set_icon_position(int x, int y);
	void set_icon_texture(char frame);
	char* get_icon();

	void set_pokemon_types(type primary, type secondary);
	type get_pokemon_types(int number_type);

	void set_base_stats(std::map<stats, int> base);
	std::map<stats, int> get_base_stats();

	void set_status_problem(status_problems status);
	status_problems get_status_problem();

	void set_sleep_turns(int turns);

	void set_status_changes(status_changes status);
	void init_status_changes();
	void remove_status_changes(status_changes status);
	std::map<status_changes, bool> get_status_changes();

	void set_moves(std::vector<std::string> possible_moves);
	std::array<Move*, 4> get_moves();

	void set_hp(int amount);
	int get_max_hp();
	int get_hp();

	void set_fainted(bool fainted);
	bool get_fainted();

private:
	sf::Sprite pokemon_sprite;
	sf::Texture* pokemon_texture{nullptr};
	sf::Sprite pokemon_back_sprite;
	sf::Texture* pokemon_back_texture{nullptr};
	sf::Sprite menu_sprite;
	sf::Texture* menu_texture{nullptr};

	int pokedex;
	std::string name;
	char* icon;
	int level;

	type pokemon_primary_type;
	type pokemon_secondary_type;

	status_problems status_problem;
	int b_poisoned_turns;
	int sleeped_turns;
	std::map<status_changes, bool> status_change;
	int confused_turns;

	nature pokemon_nature;

	std::map<stats, int> pokemon_base_stats;
	std::map<stats, float> pokemon_stats;
	std::map<stats, int> stat_change;
	std::map<stats, float> pokemon_act_stats;
	std::map<stats, int> pokemon_EVs;
	std::map<stats, int> pokemon_IVs;
	std::map<stats, float> pokemon_nature_stat;

	std::array<Move*, 4> moves;

	int act_hp;

	bool is_fainted;

};

