#pragma once

#include <Gameplay/GameObject.h>
#include <map>


void draw_badges_screen(sf::RenderWindow& window, int selectioned, std::map<int, bool> winned_badges);

void draw_background(sf::RenderWindow& window);

void draw_status_box(sf::RenderWindow& window);

void draw_status(sf::RenderWindow& window);

void draw_badges_box(sf::RenderWindow& window);

void draw_badges(sf::RenderWindow& window, int selectioned, std::map<int, bool> winned_badges);

void draw_frame(int x, int y, sf::RenderWindow& window);