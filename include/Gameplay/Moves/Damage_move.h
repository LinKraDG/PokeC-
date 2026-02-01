#pragma once
#include <Gameplay/Moves/Move.h>
#include <map>

class Damage_Move : virtual public Move
{
	public:

		~Damage_Move() override = default;

		Damage_Move(std::string archive);

		// Combat
		std::string damage_use(Pokemon* aggressor, Pokemon* defensor, bool crit = false) override;


		// Getters/Setters
		void set_category(move_category m_category);
		move_category get_category();

		void set_power(int m_power);
		int get_power();

		void set_contact(bool m_contact);
		bool get_contact();

		void set_critical_bonus(bool m_crit_bonus);
		bool get_critical_bonus();

		void set_have_additional_effect(bool m_have_addit_effect);
		bool get_have_additional_effect();

		void set_additional_effect(move_effect m_addit_effect);
		move_effect get_additional_effect();

		void set_status_effect(status_problems m_problem);
		status_problems get_status_problem_effect();

		void set_status_effect(status_changes m_change);
		status_changes get_status_change_effect();

		void set_additional_effect_amount(std::map<stats, int> m_stats_amount);
		std::map<stats, int>  get_additional_effect_amount();

		void set_additional_effect_prob(int m_addit_effect_prob);
		int get_additional_effect_prob();

		void set_have_recoil(bool m_have_recoil);
		bool get_have_recoil();

		void set_recoil_heal_base(recoil_heal_type m_base);
		recoil_heal_type get_recoil_heal_base();

		void set_recoil_heal_amount(int m_amount);
		int get_recoil_heal_amount();

		void set_multi_turn(bool m_multi_turn);
		bool get_multi_turn();
		
		void set_max_turn(int m_max_turn);
		int get_max_turn();

		void set_multi_hit(bool m_multi_hit);
		bool get_multi_hit();

		void set_max_hit(int m_max_hit);
		int get_max_hit();

		void set_special_case(special_cases m_special_case);
		special_cases get_special_case();

		void set_special_case_damage(int m_sp_damage);
		int get_special_case_damage();

		float get_effectiveness(Pokemon* poke);

	private:
		move_category category;

		int power;

		bool contact;

		bool critical_bonus;

		bool have_additional_effect;
		move_effect additional_effect;
		status_problems status_problem_effect;
		status_changes status_change_effect;
		std::map<stats, int> additional_effect_stats_amount;
		int additional_effect_prob;

		bool have_recoil;
		recoil_heal_type recoil_heal_base;
		int recoil_heal_amount;

		bool multi_turn;
		int max_turn;

		bool multi_hit;
		int max_hit;

		special_cases special_case;
		int special_case_damage;
};
