#pragma once

#include <cstdint>
#include <SFML/Graphics/Sprite.hpp>
//#include <Core/Screens/Screens.h>
//#include <Gameplay/Pokemons/Pokemon.h>
//#include <Gameplay/Combat.h>

class Pokemon;
class Combat;
class Screens;

namespace sf
{
	class RenderWindow;
}

class World
{
	public:

		~World();

		// TO-DO: Ideally the scene should be read from file.
		bool load();

		void update(uint32_t deltaMilliseconds);
		void render(sf::RenderWindow& window);

	private:

		// This is just an example. Think a good way to group the actors of your game. If they need any type of manager, etc...
		Screens* s_manager{ nullptr };
		Combat* c_manager{nullptr};
		
		sf::Sprite background;
		sf::Texture* background_texture{ nullptr };

		Pokemon* test_pokemon{ nullptr };

		void draw_background(sf::RenderWindow& window);

};