#include <Gameplay/Moves/Damage_move.h>
#include <Gameplay/Pokemons/Pokemon.h>
#include <nlohmann/json.hpp>
#include <Gameplay/JsonsConv.h>

using json = nlohmann::json;

Damage_Move::Damage_Move(std::string archive)
{
	std::ifstream mf(MOVES_ARCHIVES + archive + ".json");

	json j;
	mf >> j;

	set_name(j["name"]);
	set_type(json_type(j["type"]));
	set_objective(json_objective(j["objective"]));
	if (j["accuracy"] == "null") 
	{
		set_accuracy(1000);
	}
	else
	{
		set_accuracy(j["accuracy"]);
	}
	set_max_pp(j["max_pp"]);
	set_priority(j["priority"]);

	set_category(json_category(j["category"]));
	set_power(j["power"]);
	set_contact(j["contact"]);
	set_critical_bonus(j["critical_bonus"]);
	set_have_additional_effect(j["have_additional_effect"]);
	if (j["have_additional_effect"] == true)
	{
		set_additional_effect(json_effect(j["additional_effect"]));
		std::map<stats, int> st;
		switch (get_additional_effect())
		{
			case move_effect::status_problem:
				set_status_effect(json_s_problem(j["status_effect"]));
				set_additional_effect_prob(j["additional_effect_prob"]);
				break;
			case move_effect::status_change:
				set_status_effect(json_s_change(j["status_effect"]));
				set_additional_effect_prob(j["additional_effect_prob"]);
				break;
			case move_effect::user_stat:
			case move_effect::enemy_stat:
				for (int i = 0; i < 8; i++)
				{
					st[static_cast<stats>(i)] = j["additional_effect_stats_amount"][i];
				}
				set_additional_effect_amount(st);
				set_additional_effect_prob(j["additional_effect_prob"]);
				break;
			case move_effect::heal:
				set_recoil_heal_base(json_recoil_heal(j["recoil_base_damage"]));
				set_recoil_heal_amount(j["recoil_amount"]);
				break;
		}

		
	}

	set_have_recoil(j["have_recoil"]);
	if (get_have_recoil())
	{
		set_recoil_heal_base(json_recoil_heal(j["recoil_base_damage"]));
		set_recoil_heal_amount(j["recoil_amount"]);
	}

	// Posible continue
	/*
	set_multi_turn(j["multi_turn"]);

	if (get_multi_turn() != NULL)
	{
		set_max_turn(j["max_turn"]);
	}

	set_multi_hit(j["multi_hit"]);

	if (get_multi_hit() != NULL)
	{
		set_max_hit(j["max_hit"]);
	}

	if (j["special_case"] != NULL) 
	{
		set_special_case(j["special_case"]);
		set_special_case_damage(j["special_case_damage"]);
	}

	*/

	mf.close();
}

void Damage_Move::set_category(move_category m_category)
{
	category = m_category;
}

move_category Damage_Move::get_category()
{
	return category;
}

void Damage_Move::set_power(int m_power)
{
	power = m_power;
}

int Damage_Move::get_power()
{
	return power;
}

void Damage_Move::set_contact(bool m_contact)
{
	contact = m_contact;
}

bool Damage_Move::get_contact()
{
	return contact;
}

void Damage_Move::set_critical_bonus(bool m_crit_bonus)
{
	critical_bonus = m_crit_bonus;
}

bool Damage_Move::get_critical_bonus()
{
	return critical_bonus;
}

void Damage_Move::set_have_additional_effect(bool m_have_addit_effect)
{
	have_additional_effect = m_have_addit_effect;
}

bool Damage_Move::get_have_additional_effect()
{
	return have_additional_effect;
}

void Damage_Move::set_additional_effect(move_effect m_addit_effect)
{
	additional_effect = m_addit_effect;
}

move_effect Damage_Move::get_additional_effect()
{
	return additional_effect;
}

void Damage_Move::set_status_effect(status_problems m_problem)
{
	status_problem_effect = m_problem;
}

status_problems Damage_Move::get_status_problem_effect()
{
	return status_problem_effect;
}

void Damage_Move::set_status_effect(status_changes m_change)
{
	status_change_effect = m_change;
}

status_changes Damage_Move::get_status_change_effect()
{
	return status_change_effect;
}

void Damage_Move::set_additional_effect_amount(std::map<stats, int> m_stats_amount)
{
	for (int i = 0; i < 8; i++)
	{
		additional_effect_stats_amount[static_cast<stats>(i)] = m_stats_amount[static_cast<stats>(i)];
	}
}

std::map<stats, int> Damage_Move::get_additional_effect_amount()
{
	return additional_effect_stats_amount;
}

void Damage_Move::set_additional_effect_prob(int m_addit_effect_prob)
{
	additional_effect_prob = m_addit_effect_prob;
}

int Damage_Move::get_additional_effect_prob()
{
	return additional_effect_prob;
}

void Damage_Move::set_have_recoil(bool m_have_recoil)
{
	have_recoil = m_have_recoil;
}

bool Damage_Move::get_have_recoil()
{
	return have_recoil;
}

void Damage_Move::set_recoil_heal_base(recoil_heal_type m_base)
{
	recoil_heal_base = m_base;
}

recoil_heal_type Damage_Move::get_recoil_heal_base()
{
	return recoil_heal_base;
}

void Damage_Move::set_recoil_heal_amount(int m_amount)
{
	recoil_heal_amount = m_amount;
}

int Damage_Move::get_recoil_heal_amount()
{
	return recoil_heal_amount;
}

void Damage_Move::set_multi_turn(bool m_multi_turn)
{
	multi_turn = m_multi_turn;
}

bool Damage_Move::get_multi_turn()
{
	return multi_turn;
}

void Damage_Move::set_max_turn(int m_max_turn)
{
	max_turn = m_max_turn;
}

int Damage_Move::get_max_turn()
{
	return max_turn;
}

void Damage_Move::set_multi_hit(bool m_multi_hit)
{
	multi_hit = m_multi_hit;
}

bool Damage_Move::get_multi_hit()
{
	return multi_hit;
}

void Damage_Move::set_max_hit(int m_max_hit)
{
	max_hit = m_max_hit;
}

int Damage_Move::get_max_hit()
{
	return max_hit;
}

void Damage_Move::set_special_case(special_cases m_special_case)
{
	special_case = m_special_case;
}

special_cases Damage_Move::get_special_case()
{
	return special_case;
}

void Damage_Move::set_special_case_damage(int m_sp_damage)
{
	special_case_damage = m_sp_damage;
}

int Damage_Move::get_special_case_damage()
{
	return special_case_damage;
}

float Damage_Move::get_effectiveness(Pokemon* poke)
{
	float multiplicator = 1.f;
	for (int i = 0; i <= 1; i++)
	{
		switch (get_type())
		{
			case type::bug:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ghost:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fire:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fairy:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fighting:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::grass:
						multiplicator = multiplicator * 2;
						break;
					case type::psychic:
						multiplicator = multiplicator * 2;
						break;
					case type::dark:
						multiplicator = multiplicator * 2;
						break;
					case type::poison:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::flying:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::dark:
				switch (poke->get_pokemon_types(i))
				{
					case type::ghost:
						multiplicator = multiplicator * 2;
						break;
					case type::fairy:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fighting:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::psychic:
						multiplicator = multiplicator * 2;
						break;
					case type::dark:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::dragon:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::dragon:
						multiplicator = multiplicator * 2;
						break;
					case type::fairy:
						multiplicator = multiplicator * 0;
						break;
					default:
						break;
				}
				break;
			case type::electric:
				switch (poke->get_pokemon_types(i))
				{
					case type::water:
						multiplicator = multiplicator * 2;
						break;
					case type::dragon:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::electric:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::grass:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ground:
						multiplicator = multiplicator * 0;
						break;
					case type::flying:
						multiplicator = multiplicator * 2;
						break;
					default:
						break;
				}
				break;
			case type::fairy:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::dragon:
						multiplicator = multiplicator * 2;
						break;
					case type::fire:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fighting:
						multiplicator = multiplicator * 2;
						break;
					case type::dark:
						multiplicator = multiplicator * 2;
						break;
					case type::poison:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::fighting:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 2;
						break;
					case type::bug:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ghost:
						multiplicator = multiplicator * 0;
						break;
					case type::fairy:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ice:
						multiplicator = multiplicator * 2;
						break;
					case type::normal:
						multiplicator = multiplicator * 2;
						break;
					case type::psychic:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::rock:
						multiplicator = multiplicator * 2;
						break;
					case type::dark:
						multiplicator = multiplicator * 2;
						break;
					case type::poison:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::flying:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::fire:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 2;
						break;
					case type::water:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::bug:
						multiplicator = multiplicator * 2;
						break;
					case type::dragon:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fire:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ice:
						multiplicator = multiplicator * 2;
						break;
					case type::grass:
						multiplicator = multiplicator * 2;
						break;
					case type::rock:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::flying:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::bug:
						multiplicator = multiplicator * 2;
						break;
					case type::electric:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fighting:
						multiplicator = multiplicator * 2;
						break;
					case type::grass:
						multiplicator = multiplicator * 2;
						break;
					case type::rock:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::ghost:
				switch (poke->get_pokemon_types(i))
				{
					case type::ghost:
						multiplicator = multiplicator * 2;
						break;
					case type::normal:
						multiplicator = multiplicator * 0;
						break;
					case type::psychic:
						multiplicator = multiplicator * 2;
						break;
					case type::dark:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::grass:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::water:
						multiplicator = multiplicator * 2;
						break;
					case type::bug:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::dragon:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fire:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::grass:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::rock:
						multiplicator = multiplicator * 2;
						break;
					case type::ground:
						multiplicator = multiplicator * 2;
						break;
					case type::poison:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::flying:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::ground:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 2;
						break;
					case type::bug:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::electric:
						multiplicator = multiplicator * 2;
						break;
					case type::fire:
						multiplicator = multiplicator * 2;
						break;
					case type::grass:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::rock:
						multiplicator = multiplicator * 2;
						break;
					case type::poison:
						multiplicator = multiplicator * 2;
						break;
					case type::flying:
						multiplicator = multiplicator * 0;
						break;
					default:
						break;
				}
				break;
			case type::ice:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::water:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::dragon:
						multiplicator = multiplicator * 2;
						break;
					case type::fire:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ice:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::grass:
						multiplicator = multiplicator * 2;
						break;
					case type::ground:
						multiplicator = multiplicator * 2;
						break;
					case type::flying:
						multiplicator = multiplicator * 2;
						break;
					default:
						break;
				}
				break;
			case type::normal:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ghost:
						multiplicator = multiplicator * 0;
						break;
					case type::rock:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::poison:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0;
						break;
					case type::ghost:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fairy:
						multiplicator = multiplicator * 2;
						break;
					case type::grass:
						multiplicator = multiplicator * 2;
						break;
					case type::rock:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ground:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::poison:
						multiplicator = multiplicator * 0.5f;
						break;
					default:
						break;
				}
				break;
			case type::psychic:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fighting:
						multiplicator = multiplicator * 2;
						break;
					case type::psychic:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::dark:
						multiplicator = multiplicator * 0;
						break;
					case type::poison:
						multiplicator = multiplicator * 2;
						break;
					default:
						break;
				}
				break;
			case type::rock:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::bug:
						multiplicator = multiplicator * 2;
						break;
					case type::fire:
						multiplicator = multiplicator * 2;
						break;
					case type::ice:
						multiplicator = multiplicator * 2;
						break;
					case type::fighting:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::ground:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::flying:
						multiplicator = multiplicator * 2;
						break;
					default:
						break;
				}
				break;
			case type::steel:
				switch (poke->get_pokemon_types(i))
				{
					case type::steel:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::water:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::electric:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fire:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fairy:
						multiplicator = multiplicator * 2;
						break;
					case type::ice:
						multiplicator = multiplicator * 2;
						break;
					case type::rock:
						multiplicator = multiplicator * 2;
						break;
					default:
						break;
				}
				break;
			case type::water:
				switch (poke->get_pokemon_types(i))
				{
					case type::water:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::dragon:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::fire:
						multiplicator = multiplicator * 2;
						break;
					case type::grass:
						multiplicator = multiplicator * 0.5f;
						break;
					case type::rock:
						multiplicator = multiplicator * 2;
						break;
					case type::ground:
						multiplicator = multiplicator * 2;
						break;
					default:
						break;
				}
				break;
		}

		if (poke->get_pokemon_types(1) == type::null_type)
		{
			i++;
		}
	}
	

	return multiplicator;
}

std::string Damage_Move::damage_use(Pokemon* aggressor, Pokemon* defensor, bool crit)
{
	std::string text = "";
	float e; //effectiveness
	e = get_effectiveness(defensor);

	if (e != 0)
	{
		int damage;
		
		float b; //bonus STAB
		if (get_type() == aggressor->get_pokemon_types(0) || get_type() == aggressor->get_pokemon_types(1))
		{
			b = 1.5f;
		}
		else
		{
			b = 1.f;
		}

		int v; //variation
		srand(static_cast<unsigned int>(time(0)));
		v = 85 + (rand() % 16);

		int l = aggressor->get_level(); //level

		int a; //attack
		if (get_category() == move_category::physical)
		{
			a = static_cast<int>(aggressor->get_act_stats()[stats::attack]);
			if (aggressor->get_status_problem() == status_problems::burned)
			{
				a = a / 2;
			}
		}
		else
		{
			a = static_cast<int>(aggressor->get_act_stats()[stats::special_attack]);
		}

		int p = get_power(); //power

		int d; //defense
		if (get_category() == move_category::physical)
		{
			d = static_cast<int>(defensor->get_act_stats()[stats::defense]);
		}
		else
		{
			d = static_cast<int>(defensor->get_act_stats()[stats::special_defense]);
		}

		damage = static_cast<int>(0.01f * b * e * v * (((0.2f * l + 1) * (a * p)) / (25 * d) + 2));

		if (crit)
		{
			damage = static_cast<int>(damage * 1.5f);
		}

		defensor->change_negative_hp(damage);


		if (e == 0)
		{
			text += "¡No afectó a " + defensor->get_name() + "! \n";
		}
		if (e == 0.25)
		{
			text += "Es muy poco efectivo... \n \n";
			if (crit)
			{
				text += "¡Ataque crítico! \n \n";
			}
		}
		if (e == 0.5)
		{
			text += "No es muy efectivo... \n \n";
			if (crit)
			{
				text += "¡Ataque crítico! \n \n";
			}
		}
		if (e == 1)
		{
			if (crit)
			{
				text += "¡Ataque crítico! \n \n";
			}
		}
		if (e == 2)
		{
			text += "¡Es muy efectivo! \n \n";
			if (crit)
			{
				text += "¡Ataque crítico! \n \n";
			}
		}
		if (e == 4)
		{
			text += "¡Es súper efectivo! \n \n";
			if (crit)
			{
				text += "¡Ataque crítico! \n \n";
			}
		}

		if (get_have_recoil())
		{
			switch (get_recoil_heal_base())
			{
			case recoil_heal_type::max:
				aggressor->recoil_damage(get_recoil_heal_amount(), get_recoil_heal_base());
				break;
			case recoil_heal_type::objective:
				aggressor->recoil_damage(get_recoil_heal_amount(), get_recoil_heal_base(), damage);
				break;
			}

			text += aggressor->get_name() + " se hizo daño. \n";
		}

		if (defensor->get_fainted())
		{
			text += "¡" + defensor->get_name() + " se debilitó! \n";
		}

		if (aggressor->get_fainted())
		{
			text += "¡" + aggressor->get_name() + " se debilitó! \n";
		}

		if (get_have_additional_effect())
		{
			int effect_prob = get_additional_effect_prob();
			int total_effect_prob = 100;
			int result;
			switch (get_additional_effect())
			{
			case move_effect::status_problem:
				srand(static_cast<unsigned int>(time(0)));

				result = rand() % (total_effect_prob + 1);

				if (result <= effect_prob)
				{
					defensor->set_status_problem(get_status_problem_effect());
					text += defensor->get_name() + " está " + get_problem_name(get_status_problem_effect()) + ".";
				}

				break;
			case move_effect::status_change:
				srand(static_cast<unsigned int>(time(0)));

				result = rand() % (total_effect_prob + 1);

				if (result <= effect_prob)
				{
					if (!defensor->get_status_changes()[get_status_change_effect()])
					{
						defensor->set_status_changes(get_status_change_effect());
						text += defensor->get_name() + " está " + get_change_name(get_status_change_effect()) + ".";
					}
					else
					{
						text += defensor->get_name() + " ya estaba " + get_change_name(get_status_change_effect()) + ".";
					}
					

				}
				break;
			case move_effect::user_stat:
				srand(static_cast<unsigned int>(time(0)));

				result = rand() % (total_effect_prob + 1);

				if (result <= effect_prob)
				{
					for (int i = 1; i < 8; i++)
					{
						if (get_additional_effect_amount()[static_cast<stats>(i)] != 0)
						{
							if (aggressor->get_stat_change(i) == 6)
							{
								text += get_stat_name(static_cast<stats>(i)) + " de " + aggressor->get_name() + " no puede subir más.";
							}
							else
							{
								aggressor->set_stat_change(i, get_additional_effect_amount()[static_cast<stats>(i)]);
								text += get_stat_name(static_cast<stats>(i)) + " de " + aggressor->get_name() + " aumentó.";
							}
						}
					}
				}
				break;
			case move_effect::enemy_stat:
				srand(unsigned int(time(0)));

				result = rand() % (total_effect_prob + 1);

				if (result <= effect_prob)
				{
					for (int i = 1; i < 8; i++)
					{
						if (get_additional_effect_amount()[static_cast<stats>(i)] != 0)
						{
							if (defensor->get_stat_change(i) == -6)
							{
								text += get_stat_name(static_cast<stats>(i)) + " de " + defensor->get_name() + " no puede bajar más.";
							}
							else
							{
								defensor->set_stat_change(i, get_additional_effect_amount()[static_cast<stats>(i)]);
								text += get_stat_name(static_cast<stats>(i)) + " de " + defensor->get_name() + " bajó.";
							}
						}
					}
				}
				break;
			case move_effect::heal:
				aggressor->recover_hp(get_recoil_heal_amount(), get_recoil_heal_base(), damage);
				text += aggressor->get_name() + " restableció salud.";
				break;
			}
		}



		if (text == "")
		{
			text += "A";
		}


		return text;
	}
	else
	{

		text += "¡No afectó a " + defensor->get_name() + "! \n";
		return text;
	}
}
