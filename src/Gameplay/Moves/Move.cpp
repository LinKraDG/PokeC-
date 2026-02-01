#include "Gameplay/Moves/Move.h"

void Move::set_name(std::string m_name)
{
	name = m_name;
}

std::string Move::get_name()
{
	return name;
}

void Move::set_type(type m_type)
{
	move_type = m_type;
}

type Move::get_type()
{
	return move_type;
}

std::string Move::get_problem_name(status_problems problem)
{
	std::string problem_name;

	switch (static_cast<status_problems>(problem))
	{
	case status_problems::paralyzed:
			problem_name = "paralizado";
			break;
		case status_problems::burned:
			problem_name = "quemado";
			break;
		case status_problems::poisoned:
			problem_name = "envenenado";
			break;
		case status_problems::badly_poisoned:
			problem_name = "gravemente envenenado";
			break;
		case status_problems::asleep:
			problem_name = "dormido";
			break;
		case status_problems::frozen:
			problem_name = "congelado";
			break;
	}

	return problem_name;
}

std::string Move::get_change_name(status_changes change)
{
	std::string change_name;

	switch (static_cast<status_changes>(change))
	{
		case status_changes::flinch:
			change_name = "amedrentado";
			break;
		case status_changes::confused:
			change_name = "confuso";
			break;
		case status_changes::trapped:

			break;
		case status_changes::bound:

			break;
		case status_changes::seeded:

			break;
	}

	return change_name;
}

std::string Move::get_stat_name(stats stat)
{
	std::string stat_name;
	switch (static_cast<stats>(stat))
	{
	case stats::hp:
		stat_name = "vida";
		break;
	case stats::attack:
		stat_name = " El ataque";
		break;
	case stats::defense:
		stat_name = "La defensa";
		break;
	case stats::special_attack:
		stat_name = " El ataque especial";
		break;
	case stats::special_defense:
		stat_name = "La defensa especial";
		break;
	case stats::velocity:
		stat_name = "La velocidad";
		break;
	case stats::accuracy:
		stat_name = "La precisión";
		break;
	case stats::evasion:
		stat_name = "La evasión";
		break;
	}

	return stat_name;;
}

void Move::set_objective(objective_type m_objective)
{
	objective = m_objective;
}

objective_type Move::get_objective()
{
	return objective;
}

void Move::set_accuracy(int m_accuracy)
{
	accuracy = m_accuracy;
}

int Move::get_accuracy()
{
	return accuracy;
}

void Move::set_max_pp(int m_max_pp)
{
	max_pp = m_max_pp;
	set_pp(max_pp);
}

int Move::get_max_pp()
{
	return max_pp;
}

void Move::set_pp(int m_pp)
{
	pp = m_pp;
}

void Move::reduce_pp()
{
	pp -= 1;
}

int Move::get_pp()
{
	return pp;
}

void Move::set_priority(int m_priority)
{
	priority = m_priority;
}

int Move::get_priority()
{
	return priority;
}

std::string Move::status_use(Pokemon* aggressor, Pokemon* defensor)
{
	return "";
}

std::string Move::damage_use(Pokemon* aggressor, Pokemon* defensor, bool crit)
{
	return "";
}
