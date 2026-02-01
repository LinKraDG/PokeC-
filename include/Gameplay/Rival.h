#pragma once
#include <Gameplay/GameObject.h>
#include <SFML/Graphics/Sprite.hpp>
#include <Gameplay/Pokemons/Pokemon.h>
#include <string>

class GameObject;
class Pokemon;

class Rival
{
	public:

		~Rival();

		Rival(std::string name);

		// Visual
		void sprite_update();


		// Getters/Setters
		sf::Sprite get_sprite();

		void set_name(std::string name);
		std::string get_name();

		void set_pokemons(std::array<int, 6> poke_num);
		std::array<Pokemon*, 6> get_pokemons();

	private:
		std::string rival_name;
		sf::Sprite rival_sprite;
		sf::Texture* rival_texture{nullptr};
		std::array<Pokemon*, 6> pokemons;
};