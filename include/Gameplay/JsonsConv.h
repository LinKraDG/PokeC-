#pragma once

#include <Utils/Constants.h>

inline extern type json_type(std::string typ)
{
	
	if (typ == "steel")
	{
		return type::steel;
	}
	if (typ == "bug")
	{
		return type::bug;
	}
	if (typ == "dark")
	{
		return type::dark;
	}
	if (typ == "dragon")
	{
		return type::dragon;
	}
	if (typ == "electric")
	{
		return type::electric;
	}
	if (typ == "fairy")
	{
		return type::fairy;
	}
	if (typ == "fighting")
	{
		return type::fighting;
	}
	if (typ == "fire")
	{
		return type::fire;
	}
	if (typ == "flying")
	{
		return type::flying;
	}
	if (typ == "ghost")
	{
		return type::ghost;
	}
	if (typ == "grass")
	{
		return type::grass;
	}
	if (typ == "ground")
	{
		return type::ground;
	}
	if (typ == "ice")
	{
		return type::ice;
	}
	if (typ == "normal")
	{
		return type::normal;
	}
	if (typ == "poison")
	{
		return type::poison;
	}
	if (typ == "psychic")
	{
		return type::psychic;
	}
	if (typ == "rock")
	{
		return type::rock;
	}
	if (typ == "water")
	{
		return type::water;
	}
	return type::null_type;
}

inline extern stats json_stat(std::string sta)
{
	if (sta == "hp")
	{
		return stats::hp;
	}
	if (sta == "attack")
	{
		return stats::attack;
	}
	if (sta == "defense")
	{
		return stats::defense;
	}
	if (sta == "special_attack")
	{
		return stats::special_attack;
	}
	if (sta == "special_defense")
	{
		return stats::special_defense;
	}
	if (sta == "velocity")
	{
		return stats::velocity;
	}
	return stats::hp;
}

inline extern move_category json_category(std::string mc)
{
	if (mc == "physical")
	{
		return move_category::physical;
	}
	if (mc == "special")
	{
		return move_category::special;
	}
	if (mc == "status")
	{
		return move_category::status;
	}
	return move_category::status;
}

inline extern objective_type json_objective(std::string ot)
{
	if (ot == "user")
	{
		return objective_type::user;
	}
	if (ot == "enemy")
	{
		return objective_type::enemy;
	}
	return objective_type::user;
}

inline extern move_effect json_effect(std::string me)
{
	if (me == "status_problem")
	{
		return move_effect::status_problem;
	}
	if (me == "status_change")
	{
		return move_effect::status_change;
	}
	if (me == "user_stat")
	{
		return move_effect::user_stat;
	}
	if (me == "enemy_stat")
	{
		return move_effect::enemy_stat;
	}
	if (me == "heal")
	{
		return move_effect::heal;
	}
	return move_effect::status_problem;
}

inline extern status_problems json_s_problem(std::string sp)
{
	if (sp == "paralyzed")
	{
		return status_problems::paralyzed;
	}
	if (sp == "burned")
	{
		return status_problems::burned;
	}
	if (sp == "poisoned")
	{
		return status_problems::poisoned;
	}
	if (sp == "badly_poisoned")
	{
		return status_problems::badly_poisoned;
	}
	if (sp == "asleep")
	{
		return status_problems::asleep;
	}
	if (sp == "frozen")
	{
		return status_problems::frozen;
	}
	return status_problems::asleep;
}

inline extern status_changes json_s_change(std::string sc)
{
	if (sc == "flinch")
	{
		return status_changes::flinch;
	}
	if (sc == "confused")
	{
		return status_changes::confused;
	}
	if (sc == "trapped")
	{
		return status_changes::trapped;
	}
	return status_changes::flinch;
}

inline extern recoil_heal_type json_recoil_heal(std::string rht)
{
	if (rht == "max")
	{
		return recoil_heal_type::max;
	}
	if (rht == "objective")
	{
		return recoil_heal_type::objective;
	}
	return recoil_heal_type::max;
}