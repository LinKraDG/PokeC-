#include "Core/Selections.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Utils/Constants.h>
#include <SFML/System/Sleep.hpp>

int change_menu_selection(int selection)
{
	int act_select = selection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (act_select - 1 >= 1) {
			selection -= 1;
		}
		else
		{
			selection = 2;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (act_select + 1 <= 2) {
			selection += 1;
		}
		else
		{
			selection = 1;
		}
		sf::sleep(sf::seconds(.2f));
	}

	
	return selection;
}

int change_badge_selection(int selection)
{
	int act_select = selection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (act_select + 1 <= 8) {
			selection += 1;
		}
		else
		{
			selection = 1;
		}
		sf::sleep(sf::seconds(.2f));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (act_select - (8 / 2) >= 1) {
			selection -= 8 / 2;
		}
		else
		{
			selection = 8 - (8/2)+ act_select;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (act_select - 1 >= 1) {
			selection -= 1;
		}
		else
		{
			selection = 8;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (act_select + (8/2) <= 8) {
			selection += 8/2;
		}
		else
		{
			selection = 1 + (8 / 2) - (8 - act_select) - 1;
		}
		sf::sleep(sf::seconds(.2f));
	}

	return selection;
}

int change_combat_selection(int selection)
{
	int act_select = selection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (act_select + 1 <= 4) {
			selection += 1;
		}
		else
		{
			selection = 1;
		}
		sf::sleep(sf::seconds(.2f));

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (act_select - (4 / 2) >= 1) {
			selection -= 4 / 2;
		}
		else
		{
			selection = 4 - (4 / 2) + act_select;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (act_select - 1 >= 1) {
			selection -= 1;
		}
		else
		{
			selection = 4;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (act_select + (4 / 2) <= 4) {
			selection += 4 / 2;
		}
		else
		{
			selection = 1 + (4 / 2) - (4 - act_select) - 1;
		}
		sf::sleep(sf::seconds(.2f));
	}

	return selection;
}

int change_combat_move(int selection)
{
	int act_select = selection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (act_select - 1 >= 1) {
			selection -= 1;
		}
		else
		{
			selection = 4;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (act_select + 1 <= 4) {
			selection += 1;
		}
		else
		{
			selection = 1;
		}
		sf::sleep(sf::seconds(.2f));
	}


	return selection;
}

int change_combat_poke(int selection)
{
	int act_select = selection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (act_select - 1 >= 1) {
			selection -= 1;
		}
		else
		{
			selection = 6;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (act_select + 1 <= 6) {
			selection += 1;
		}
		else
		{
			selection = 1;
		}
		sf::sleep(sf::seconds(.2f));
	}


	return selection;
}

int change_combat_poke_action(int selection)
{
	int act_select = selection;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (act_select - 1 >= 1) {
			selection -= 1;
		}
		else
		{
			selection = 3;
		}
		sf::sleep(sf::seconds(.2f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (act_select + 1 <= 3) {
			selection += 1;
		}
		else
		{
			selection = 1;
		}
		sf::sleep(sf::seconds(.2f));
	}


	return selection;
}