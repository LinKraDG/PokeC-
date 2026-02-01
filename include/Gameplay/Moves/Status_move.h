#pragma once
#include <Gameplay/Moves/Move.h>
#include <map>



class Status_Move : virtual public Move
{
	public:

		~Status_Move() override = default;

		Status_Move(std::string archive);

		// Combat
		std::string status_use(Pokemon* aggressor, Pokemon* defensor = nullptr) override;


		// Getters/Setters
		move_category get_category();

		void set_effect(move_effect m_effect);
		move_effect get_effect();

		void set_status_effect(status_problems m_problem);
		status_problems get_status_problem_effect();

		void set_status_effect(status_changes m_change);
		status_changes get_status_change_effect();

		void set_heal_base(recoil_heal_type m_base);
		recoil_heal_type get_heal_base();

		void set_heal_amount(int m_amount);
		int get_heal_amount();

		void set_effect_stats_amount(std::map<stats, int> m_stats_amount);
		std::map<stats, int>  get_effect_stats_amount();

	private:
		move_category category = static_cast<move_category>(2);

		move_effect effect;

		status_problems status_problem_effect;
		status_changes status_change_effect;

		recoil_heal_type heal_base;
		int heal_amount;

		std::map<stats, int> effect_stats_amount;

};