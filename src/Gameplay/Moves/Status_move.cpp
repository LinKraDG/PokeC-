#include <Gameplay/Moves/Status_move.h>
#include <Gameplay/Pokemons/Pokemon.h>
#include <nlohmann/json.hpp>
#include <Gameplay/JsonsConv.h>

using json = nlohmann::json;

Status_Move::Status_Move(std::string archive)
{
	std::ifstream mf(MOVES_ARCHIVES + archive +".json");

	json j;
	mf >> j;

	set_name(j["name"]);
	set_type(json_type(j["type"]));
	set_objective(json_objective(j["objective"]));
	if (get_objective() == objective_type::enemy)
	{
		if (j["accuracy"] == "null")
		{
			set_accuracy(1000);
		}
		else
		{
			set_accuracy(j["accuracy"]);
		}
	}
	set_max_pp(j["max_pp"]);
	set_priority(j["priority"]);

	set_effect(json_effect(j["effect_type"]));
	std::map<stats, int> st;
	switch (get_effect())
	{
		case move_effect::status_problem:
			set_status_effect(json_s_problem(j["effect"]));
			break;
		case move_effect::status_change:
			set_status_effect(json_s_change(j["effect"]));
			break;
		case move_effect::user_stat:
		case move_effect::enemy_stat:
			for (int i = 0; i < 8; i++)
			{
				st[static_cast<stats>(i)] = j["effect"][i];
			}
			set_effect_stats_amount(st);
			break;
		case move_effect::heal:
			set_heal_base(json_recoil_heal(j["heal_base"]));
			set_heal_amount(j["heal_amount"]);
			break;
	}


	mf.close();
}

move_category Status_Move::get_category()
{
	return category;
}

void Status_Move::set_effect(move_effect m_effect)
{
	effect = m_effect;
}

move_effect Status_Move::get_effect()
{
	return effect;
}

void Status_Move::set_status_effect(status_problems m_problem)
{
	status_problem_effect = m_problem;
}

status_problems Status_Move::get_status_problem_effect()
{
	return status_problem_effect;
}

void Status_Move::set_status_effect(status_changes m_change)
{
	status_change_effect = m_change;
}

status_changes Status_Move::get_status_change_effect()
{
	return status_change_effect;
}

void Status_Move::set_heal_base(recoil_heal_type m_base)
{
	heal_base = m_base;
}

recoil_heal_type Status_Move::get_heal_base()
{
	return heal_base;
}

void Status_Move::set_heal_amount(int m_amount)
{
	heal_amount = m_amount;
}

int Status_Move::get_heal_amount()
{
	return heal_amount;
}

void Status_Move::set_effect_stats_amount(std::map<stats, int> m_stats_amount)
{
	for (int i = 0; i < 8; i++)
	{
		effect_stats_amount[static_cast<stats>(i)] = m_stats_amount[static_cast<stats>(i)];
	}
}

std::map<stats, int> Status_Move::get_effect_stats_amount()
{
	return effect_stats_amount;
}

std::string Status_Move::status_use(Pokemon* aggressor, Pokemon* defensor)
{
	switch (get_objective())
	{
	case objective_type::user:
			switch (get_effect())
			{
				case move_effect::user_stat:
					for (int i = 1; i < 8; i++)
					{
						if (effect_stats_amount[static_cast<stats>(i)] != 0)
						{
							if (aggressor->get_stat_change(i) == 6)
							{
								return get_stat_name(static_cast<stats>(i)) + " de " + aggressor->get_name() + " no puede subir más.";
							}
							else
							{
								aggressor->set_stat_change(i, effect_stats_amount[static_cast<stats>(i)]);
								return get_stat_name(static_cast<stats>(i)) + " de " + aggressor->get_name() + " aumentó.";
							}
						}
					}
					break;
				case move_effect::heal:
					aggressor->recover_hp(get_heal_amount(), get_heal_base());
					return aggressor->get_name() + " restableció salud.";
					break;
			}
			break;
	case objective_type::enemy:
			switch (get_effect())
			{
				case move_effect::status_problem:
					if (defensor->get_status_problem() == status_problems::null_problem)
					{
						defensor->set_status_problem(get_status_problem_effect());
						return defensor->get_name() + " está " + get_problem_name(get_status_problem_effect()) + ".";
					}
					else
					{
						return defensor->get_name() + " ya estaba " + get_problem_name(defensor->get_status_problem()) + ".";
					}
					break;
				case move_effect::status_change:
					if (!defensor->get_status_changes()[get_status_change_effect()])
					{
						defensor->set_status_changes(get_status_change_effect());
						return defensor->get_name() + " está " + get_change_name(get_status_change_effect()) + ".";
					}
					else
					{
						return defensor->get_name() + " ya estaba " + get_change_name(get_status_change_effect()) + ".";
					}
					break;
				case move_effect::enemy_stat:
					for (int i = 1; i < 8; i++)
					{
						if (effect_stats_amount[static_cast<stats>(i)] != 0)
						{
							if (defensor->get_stat_change(i) == -6)
							{
								return get_stat_name(static_cast<stats>(i)) + " de " + defensor->get_name() + " no puede bajar más.";
							}
							else
							{
								defensor->set_stat_change(i, effect_stats_amount[static_cast<stats>(i)]);
								return get_stat_name(static_cast<stats>(i)) + " de " + defensor->get_name() + " bajó.";
							}
						}
					}
					break;
			}
			break;
	}
	return "";
}
