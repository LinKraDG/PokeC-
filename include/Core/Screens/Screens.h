#pragma once

#include <Gameplay/GameObject.h>
#include <map>
//#include <Gameplay/Combat.h>

class Combat;

class Screens
{
	public:
		~Screens() = default;

		bool Init();

		void update();
		void render(sf::RenderWindow& window);

		void selection_confirmed();

	private:

		Combat* combat{nullptr};

		int selectioned_mode = 0;
		int marked_selection = 0;
		int selectioned_badge = 0;

		std::map<int, bool> badges;

};