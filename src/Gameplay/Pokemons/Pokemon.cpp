#include <fstream>
#include <Core/AssetManager.h>
#include <Gameplay/Pokemons/Pokemon.h>
#include <nlohmann/json.hpp>
#include <Gameplay/JsonsConv.h>
#include <Gameplay/Moves/Status_move.h>
#include <Gameplay/Moves/Damage_move.h>


using json = nlohmann::json;

Pokemon::~Pokemon()
{
	for each(Move* move in moves)
	{
		delete move;
	}
}

Pokemon::Pokemon(int id) : pokedex(id)
{
	
	std::string archive = POKEMON_ARCHIVES + std::to_string(id) + ".json";
	std::ifstream pf(archive);
	
	json j;
	pf >> j;
	
	set_name(j["name"]);
	set_icon(j["icon"]);
	set_pokemon_types(json_type(j["primary_type"]), json_type(j["secondary_type"]));
	std::map<stats, int> st;
	for (int i = 0; i < 6; i++)
	{
		st[static_cast<stats>(i)] = j["base_stats"][i];
	}
	set_base_stats(st);
	std::vector<std::string> m_vector;
	for each(std::string str in j["moves"])
	{
		m_vector.push_back(str);
	}
	set_moves(m_vector);

	pf.close();

	Init();
}

void Pokemon::Init()
{
	set_sprites();
	set_level(50);
	set_EVs();
	set_IVs();
	set_nature();

	set_status_problem(status_problems::null_problem);
	init_status_changes();

	set_stats();
	set_fainted(false);
}

void Pokemon::set_sprites()
{
	std::string texture_archive = POKEMON_SPRITES;
	std::string front_archive;
	std::string back_archive;
	//archive += static_cast<char>(get_pokedex());
	front_archive = texture_archive + "1" + FRONT_SPRITES;
	back_archive = texture_archive + "1" + BACK_SPRITES;

	pokemon_texture = AssetManager::getInstance()->loadTexture(front_archive.c_str());
	pokemon_back_texture = AssetManager::getInstance()->loadTexture(back_archive.c_str());

	//menu_texture = AssetManager::getInstance()->loadTexture(POKEMON_MENU_SPRITES + *get_icon());
	std::string test_icon = "flower.png";
	std::string test_icon_archive = POKEMON_MENU_SPRITES + test_icon;
	menu_texture = AssetManager::getInstance()->loadTexture(test_icon_archive.c_str());
	
	pokemon_sprite.setTexture(*pokemon_texture);
	pokemon_back_sprite.setTexture(*pokemon_back_texture);
	menu_sprite.setTexture(*menu_texture);
	menu_sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
	

	pokemon_sprite.setPosition(385,0);
	pokemon_back_sprite.setPosition(17,161);

}

sf::Sprite Pokemon::get_front_sprite()
{
	return pokemon_sprite;
}

sf::Sprite Pokemon::get_back_sprite()
{
	return pokemon_back_sprite;
}

sf::Sprite Pokemon::get_icon_sprite()
{
	return menu_sprite;
}

int Pokemon::get_pokedex()
{
	return pokedex;
}

void Pokemon::set_level(int lvl)
{
	level = lvl;
}

int Pokemon::get_level()
{
	return level;
}

void Pokemon::set_EVs()
{
	int max_EVs = 510;
	int ev = 0;

	while (max_EVs!=0) {
		for (int i = 0; i < 6; i++)
		{
			if (max_EVs == 0)
			{
				break;
			}
				if (max_EVs > 254) {
					ev = rand() % 255;
				}
				else
				{
					ev = rand() % (max_EVs + 1);
				}

				if (pokemon_EVs.find(static_cast<stats>(i)) != pokemon_EVs.end())
				{
					pokemon_EVs[static_cast<stats>(i)] += ev;
				}
				else
				{
					pokemon_EVs[static_cast<stats>(i)] = ev;
				}

				max_EVs -= ev;
		}
	}
}

void Pokemon::set_IVs()
{

	for (int i = 0; i < 6; i++)
	{
		
		int iv = rand() % 32;

		pokemon_IVs[static_cast<stats>(i)] = iv;
		
	}

}

void Pokemon::set_nature()
{
	pokemon_nature = static_cast<nature>(rand() % 25);

	for (int i = 0; i < 6; i++)
	{
		pokemon_nature_stat[static_cast<stats>(i)] = 1.f;
	}

	switch (pokemon_nature)
	{
	case nature::lonely:
			pokemon_nature_stat[stats::attack] = 1.1f;
			pokemon_nature_stat[stats::defense] = 0.9f;
			break;
		case nature::brave:
			pokemon_nature_stat[stats::attack] = 1.1f;
			pokemon_nature_stat[stats::velocity] = 0.9f;
			break;
		case nature::adamant:
			pokemon_nature_stat[stats::attack] = 1.1f;
			pokemon_nature_stat[stats::special_attack] = 0.9f;
			break;
		case nature::naughty:
			pokemon_nature_stat[stats::attack] = 1.1f;
			pokemon_nature_stat[stats::special_defense] = 0.9f;
			break;
		case nature::bold:
			pokemon_nature_stat[stats::defense] = 1.1f;
			pokemon_nature_stat[stats::attack] = 0.9f;
			break;
		case nature::relaxed:
			pokemon_nature_stat[stats::defense] = 1.1f;
			pokemon_nature_stat[stats::velocity] = 0.9f;
			break;
		case nature::impish:
			pokemon_nature_stat[stats::defense] = 1.1f;
			pokemon_nature_stat[stats::special_attack] = 0.9f;
			break;
		case nature::lax:
			pokemon_nature_stat[stats::defense] = 1.1f;
			pokemon_nature_stat[stats::special_defense] = 0.9f;
			break;
		case nature::timid:
			pokemon_nature_stat[stats::velocity] = 1.1f;
			pokemon_nature_stat[stats::attack] = 0.9f;
			break;
		case nature::hasty:
			pokemon_nature_stat[stats::velocity] = 1.1f;
			pokemon_nature_stat[stats::defense] = 0.9f;
			break;
		case nature::jolly:
			pokemon_nature_stat[stats::velocity] = 1.1f;
			pokemon_nature_stat[stats::special_attack] = 0.9f;
			break;
		case nature::naive:
			pokemon_nature_stat[stats::velocity] = 1.1f;
			pokemon_nature_stat[stats::special_defense] = 0.9f;
			break;
		case nature::modest:
			pokemon_nature_stat[stats::special_attack] = 1.1f;
			pokemon_nature_stat[stats::attack] = 0.9f;
			break;
		case nature::mild:
			pokemon_nature_stat[stats::special_attack] = 1.1f;
			pokemon_nature_stat[stats::defense] = 0.9f;
			break;
		case nature::quiet:
			pokemon_nature_stat[stats::special_attack] = 1.1f;
			pokemon_nature_stat[stats::velocity] = 0.9f;
			break;
		case nature::rash:
			pokemon_nature_stat[stats::special_attack] = 1.1f;
			pokemon_nature_stat[stats::special_defense] = 0.9f;
			break;
		case nature::calm:
			pokemon_nature_stat[stats::special_defense] = 1.1f;
			pokemon_nature_stat[stats::attack] = 0.9f;
			break;
		case nature::gentle:
			pokemon_nature_stat[stats::special_defense] = 1.1f;
			pokemon_nature_stat[stats::defense] = 0.9f;
			break;
		case nature::sassy:
			pokemon_nature_stat[stats::special_defense] = 1.1f;
			pokemon_nature_stat[stats::velocity] = 0.9f;
			break;
		case nature::careful:
			pokemon_nature_stat[stats::special_defense] = 1.1f;
			pokemon_nature_stat[stats::special_attack] = 0.9f;
			break;
		default:
			break;
	}

}

void Pokemon::set_stats()
{
	int stat_ps = 0;
	int stat = 0;
	for (int i = 0; i < 6; i++)
	{
		if (i == 0) {
			pokemon_stats[stats::hp] = static_cast<float>((((2 * get_base_stats()[static_cast<stats>(0)]) + pokemon_IVs[static_cast<stats>(0)] + (pokemon_EVs[static_cast<stats>(0)] / 4)) * get_level() / 100) + get_level() + 10);
			set_hp(static_cast<int>(pokemon_stats[stats::hp]));
		}
		else 
		{ 
			pokemon_stats[static_cast<stats>(i)] = ((((2 * get_base_stats()[static_cast<stats>(i)]) + pokemon_IVs[static_cast<stats>(i)] + (pokemon_EVs[static_cast<stats>(i)] / 4)) * get_level() / 100) + 5) * pokemon_nature_stat[static_cast<stats>(i)];
		}
	}
	for (int i = 0; i < 8; i++)
	{
		stat_change[static_cast<stats>(i)] = 0;
	}
	pokemon_stats[stats::accuracy] = 100;
	pokemon_stats[stats::evasion] = 100;
	pokemon_act_stats = pokemon_stats;
}

std::map<stats, float> Pokemon::get_stats()
{
	return pokemon_stats;
}

void Pokemon::set_stat_change(int stat, int amount)
{
	if (stat_change[static_cast<stats>(stat)] + amount >= -6 || stat_change[static_cast<stats>(stat)] + amount <= 6)
	{
		stat_change[static_cast<stats>(stat)] += amount;
	}
	else
	{
		if (amount < 0) 
		{
			stat_change[static_cast<stats>(stat)] = -6;

		}

		if (amount > 0)
		{
			stat_change[static_cast<stats>(stat)] = 6;

		}
	}
	set_act_stats();
}

int Pokemon::get_stat_change(int stat)
{
	return stat_change[static_cast<stats>(stat)];
}

void Pokemon::set_act_stats()
{
	for (int i = 1; i < 8; i++)
	{
		if(i<6)
		{
			//ataque, ataque especial, defensa, defensa especial y velocidad
			if(stat_change[static_cast<stats>(i)] > 0)
			{
				pokemon_act_stats[static_cast<stats>(i)] = pokemon_stats[static_cast<stats>(i)] * ((2.f + stat_change[static_cast<stats>(i)]) / 2.f);
			}
			else if (stat_change[static_cast<stats>(i)] < 0)
			{
				pokemon_act_stats[static_cast<stats>(i)] = pokemon_stats[static_cast<stats>(i)] * (2.f / (2.f + -(stat_change[static_cast<stats>(i)])));
			}
			else
			{
				pokemon_act_stats[static_cast<stats>(i)] = pokemon_stats[static_cast<stats>(i)] * (2.f / 2.f);
			}
		}
		else
		{
			//precision y evasion
			if (stat_change[static_cast<stats>(i)] > 0)
			{
				pokemon_act_stats[static_cast<stats>(i)] = pokemon_stats[static_cast<stats>(i)] * ((3.f + stat_change[static_cast<stats>(i)]) / 3.f);
			}
			else if (stat_change[static_cast<stats>(i)] < 0)
			{
				pokemon_act_stats[static_cast<stats>(i)] = pokemon_stats[static_cast<stats>(i)] * (3.f / (3.f + -(stat_change[static_cast<stats>(i)])));
			}
			else
			{
				pokemon_act_stats[static_cast<stats>(i)] = pokemon_stats[static_cast<stats>(i)] * (3.f / 3.f);
			}
		}
	}
	
}

std::map<stats, float> Pokemon::get_act_stats()
{
	return pokemon_act_stats;
}

void Pokemon::set_name(std::string pokemon_name)
{
	name = pokemon_name;
}

std::string Pokemon::get_name()
{
	return name;
}

void Pokemon::set_icon(std::string pokemon_icon)
{
	icon = (char*)pokemon_icon.c_str() + *PNG;
}

void Pokemon::set_icon_position(int x, int y)
{
	menu_sprite.setPosition(float(x), float(y));
}

void Pokemon::set_icon_texture(char frame)
{
	menu_sprite.setTextureRect(sf::IntRect(64 * frame, 0, 64, 64));
}

char* Pokemon::get_icon()
{
	return icon;
}

void Pokemon::set_pokemon_types(type primary,type secondary = type::null_type)
{
	pokemon_primary_type = primary;
	
	pokemon_secondary_type = secondary;
}

type Pokemon::get_pokemon_types(int number_type)
{
	switch (number_type)
	{
		case 0:
			return pokemon_primary_type;
			break;
		case 1:
			return pokemon_secondary_type;
			break;
		default:
			return type::null_type;
			break;
	}
}

void Pokemon::set_base_stats(std::map<stats, int> base)
{
	for (int i = 0; i < 6; i++)
	{
		pokemon_base_stats[static_cast<stats>(i)] = base[static_cast<stats>(i)];
	}
}

std::map<stats, int> Pokemon::get_base_stats()
{
	return pokemon_base_stats;
}

void Pokemon::set_status_problem(status_problems status)
{
	status_problem = status;
	if (status == status_problems::badly_poisoned)
	{
		b_poisoned_turns = 0;
	}
	if (status == status_problems::asleep)
	{
		srand(static_cast<unsigned int>(time(0)));

		sleeped_turns = 1 + (rand() % 3);
	}
}

status_problems Pokemon::get_status_problem()
{
	return status_problem;
}

bool Pokemon::status_problem_effect()
{
	int result;
	switch (get_status_problem())
	{
		case status_problems::paralyzed:
			srand(static_cast<unsigned int>(time(0)));

			result = rand() % (100 + 1);

			if (result <= 25)
			{
				return false;
			}
			break;
		case status_problems::burned:
			change_negative_hp(static_cast<int>((6.25f*get_max_hp())/100));
			break;
		case status_problems::poisoned:
			change_negative_hp(static_cast<int>(0.125f * get_max_hp()));
			break;
		case status_problems::badly_poisoned:
			b_poisoned_turns += 1;
			change_negative_hp(static_cast<int>((0.0625f * b_poisoned_turns) * get_max_hp()));
			break;
		case status_problems::asleep:
			set_sleep_turns(sleeped_turns - 1);
			if (sleeped_turns > 0)
			{
				return false;
			}
			else
			{
				set_status_problem(status_problems::null_problem);
			}
			break;
		case status_problems::frozen:
			srand(static_cast<unsigned int>(time(0)));

			result = rand() % (100 + 1);

			if (result <= 20)
			{
				return false;
			}
			break;
	}
	return true;
}

void Pokemon::reset_poison_turns()
{
	b_poisoned_turns = 0;
}

void Pokemon::set_sleep_turns(int turns)
{
	sleeped_turns = turns;
}

void Pokemon::set_status_changes(status_changes status)
{
	
	status_change[status] = true;
	
	if (status == status_changes::confused)
	{
		srand(static_cast<unsigned int>(time(0)));

		confused_turns = 1 + (rand() % 4);
	}
}

void Pokemon::init_status_changes()
{
	for (int i = 0; i < 5; i++)
	{
		status_change[static_cast<status_changes>(i)] = false;
	}
}

void Pokemon::remove_status_changes(status_changes status)
{
	status_change[status] = false;
}

std::map<status_changes, bool> Pokemon::get_status_changes()
{
	return status_change;
}

bool Pokemon::status_change_effect()
{
	if (get_status_changes()[status_changes::flinch])
	{
		return false;
	}

	if (get_status_changes()[status_changes::confused])
	{
		if (confused_turns > 0)
		{
			int result;
			srand(static_cast<unsigned int>(time(0)));

			result = rand() % (100 + 1);

			confused_turns -= 1;

			if (result <= 33)
			{
				return false;
			}
		}
		else
		{
			remove_status_changes(status_changes::confused);
		}
	}
	
	return true;
}

void Pokemon::confuse_damage()
{
	int damage;
	int v; //variation
	srand(static_cast<unsigned int>(time(0)));
	v = 85 + (rand() % 16);

	damage = static_cast<int>( 0.01 * 1 * 1 * v * (((0.2 * get_level() + 1) * (get_act_stats()[stats::attack] * 40)) / (25 * get_act_stats()[stats::defense]) + 2));
	change_negative_hp(damage);
}

void Pokemon::end_turn_changes()
{

	if (get_status_changes()[status_changes::flinch])
	{
		remove_status_changes(status_changes::flinch);
	}
	
}

void Pokemon::set_moves(std::vector<std::string> possible_moves)
{
	
	std::array<std::string, 4> move_names;
	if (possible_moves.size() < 4)
	{
		for (int i = 0; i < 4; i++)
		{
			if (i > possible_moves.size())
			{
				move_names[i] = "null";

			}
			else
			{
				move_names[i] = possible_moves[1];
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			bool included = true;
			while (included)
			{
				int m = rand() % (possible_moves.size()/* + 1*/);
				
				if (std::find(move_names.begin(), move_names.end(), possible_moves[m]) != move_names.end())
				{
					continue;
				}
				else
				{
					move_names[i] = possible_moves[m];
					included = false;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (move_names[i] == "null")
		{
			moves[i] = nullptr;
			continue;
		}
		std::string m_archive = MOVES_ARCHIVES + move_names[i] + ".json";
		std::ifstream pmf(m_archive);

		json j;
		pmf >> j;
		if (json_category(j["category"]) == move_category::status)
		{
			moves[i] = new Status_Move(move_names[i]);
		}
		else
		{
			moves[i] = new Damage_Move(move_names[i]);
		}

		pmf.close();
	}
	
}

std::array<Move*, 4> Pokemon::get_moves()
{
	return moves;
}

void Pokemon::set_hp(int amount)
{
	act_hp = amount;
}

void Pokemon::change_negative_hp(int amount)
{
	set_hp(get_hp() - amount);

	if (get_hp() <= 0)
	{
		set_hp(0);
		set_fainted(true);
	}

}

void Pokemon::change_positive_hp(int amount)
{
	set_hp(get_hp() + amount);

	if (get_hp() > get_max_hp())
	{
		set_hp(get_max_hp());
	}
}

void Pokemon::recoil_damage(int amount, recoil_heal_type base, int damage)
{
	switch (base)
	{
		case recoil_heal_type::max:
			change_negative_hp(static_cast<int>((amount / 100.f) * get_stats()[static_cast<stats>(0)]));
			break;
		case recoil_heal_type::objective:
			change_negative_hp(static_cast<int>((amount / 100.f) * damage));
			break;
	}
}

void Pokemon::recover_hp(int amount, recoil_heal_type base, int damage)
{
	switch (base) 
	{
		case recoil_heal_type::max:
			change_positive_hp(static_cast<int>((amount / 100.f) * get_max_hp()));
			break;
		case recoil_heal_type::objective:
			change_positive_hp(static_cast<int>((amount / 100.f) * damage));
			break;
	}
}

int Pokemon::get_max_hp()
{
	return int(get_stats()[static_cast<stats>(0)]);
}

int Pokemon::get_hp()
{
	return act_hp;
}

void Pokemon::set_fainted(bool fainted)
{
	is_fainted = fainted;
}

bool Pokemon::get_fainted()
{
	return is_fainted;
}

