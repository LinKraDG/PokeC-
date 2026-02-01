#include <Core/AssetManager.h>
#include <Core/World.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Panels/Interfaces.h>
#include <Core/Screens/Badges.h>
#include <Utils/Constants.h>
#include <Gameplay/Pokemons/Pokemon.h>
#include <Core/Screens/Screens.h>

World::~World()
{
	delete s_manager;
}

bool World::load()
{
	background_texture = AssetManager::getInstance()->loadTexture(BLANK_BACKGROUND_TEXTURE);
	background.setTexture(*background_texture);

	Screens* screens = new Screens();

	const bool initOk = screens->Init();

	s_manager = screens;

	return initOk;

	return true;
}

void World::update(uint32_t deltaMilliseconds)
{
	s_manager->update();

}

void World::render(sf::RenderWindow& window)
{
	draw_background(window);
	
	s_manager->render(window);

}

void World::draw_background(sf::RenderWindow& window)
{
	background.setPosition(0,0);
	window.draw(background);
}