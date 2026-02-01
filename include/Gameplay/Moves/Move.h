#pragma once

#ifndef MOVE_H
#define MOVE_H

class Pokemon;

#endif

#include <Utils/Constants.h>
#include <string>
#include <fstream>

class Move
{
	public:

		virtual ~Move() = default;

		// Combat
		virtual std::string status_use(Pokemon* aggressor, Pokemon* defensor = nullptr);
		virtual std::string damage_use(Pokemon* aggressor, Pokemon* defensor, bool crit = false);

		// Getters/Setters
		void set_name(std::string m_name);
		std::string get_name();

		void set_type(type m_type);
		type get_type();

		std::string get_problem_name(status_problems problem);

		std::string get_change_name(status_changes change);

		std::string get_stat_name(stats stat);

		void set_objective(objective_type m_objective);
		objective_type get_objective();

		void set_accuracy(int m_accuracy);
		int get_accuracy();

		void set_max_pp(int m_max_pp);
		int get_max_pp();

		void set_pp(int m_pp);
		void reduce_pp();
		int get_pp();

		void set_priority(int m_priority);
		int get_priority();

	private:

		std::string name;

		type move_type;

		objective_type objective;

		int accuracy = 0;
		int max_pp = 0;
		int pp = 0;
		int priority = 0;
		
};