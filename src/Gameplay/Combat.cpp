#include <Gameplay/Combat.h>
#include <Core/Selections.h>
#include <UI/Text.h>
#include <SFML/System/Sleep.hpp>
#include <SFML/Window/Event.hpp>
#include <type_traits>
#include <Panels/Interfaces.h>
#include <Gameplay/Rival.h>

Combat::~Combat()
{
	delete rival;
	for each(Pokemon* poke in player_pokemons)
	{
		delete poke;
	}
}

Combat::Combat(int id)
{
	std::string rival_name;
	switch (id)
	{
		case 1:
			rival_name = "brock";
			break;
		case 2:
			rival_name = "misty";
			break;
		case 3:
			rival_name = "surge";
			break;
		case 4:
			rival_name = "erika";
			break;
		case 5:
			rival_name = "koga";
			break;
		case 6:
			rival_name = "sabrina";
			break;
		case 7:
			rival_name = "blaine";
			break;
		case 8:
			rival_name = "giovanni";
			break;
		/*case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;*/
	}

	rival = new Rival(rival_name);
	
	Init();
}

void Combat::Init()
{
	player_texture = AssetManager::getInstance()->loadTexture(PLAYER_SPRITE);
	player_sprite.setTexture(*player_texture);
	player_sprite.setPosition(609, 161);

	rival_frame_texture = AssetManager::getInstance()->loadTexture(RIVAL_COMBAT_FRAME);
	player_pres_frame_texture = AssetManager::getInstance()->loadTexture(PLAYER_PRESENTATION_FRAME);
	player_frame_texture = AssetManager::getInstance()->loadTexture(PLAYER_COMBAT_FRAME);

	health_bar_texture = AssetManager::getInstance()->loadTexture(HEALTH_BAR_TEXTURE);
	ps_text_texture = AssetManager::getInstance()->loadTexture(PS_TEXT_TEXTURE);
	level_text_texture = AssetManager::getInstance()->loadTexture(LEVEL_TEXT_TEXTURE);

	have_preview_texture = AssetManager::getInstance()->loadTexture(POKEMON_PREVIEW_HAVE);
	null_preview_texture = AssetManager::getInstance()->loadTexture(POKEMON_PREVIEW_NULL);
	fainted_preview_texture = AssetManager::getInstance()->loadTexture(POKEMON_PREVIEW_FAINTED);

	rival_frame.setTexture(*rival_frame_texture);
	player_pres_frame.setTexture(*player_pres_frame_texture);
	player_frame.setTexture(*player_frame_texture);

	player_bar_sprite.setTexture(*health_bar_texture);
	rival_bar_sprite.setTexture(*health_bar_texture);
	player_ps_text_sprite.setTexture(*ps_text_texture);
	rival_ps_text_sprite.setTexture(*ps_text_texture);
	player_level_text_sprite.setTexture(*level_text_texture);
	rival_level_text_sprite.setTexture(*level_text_texture);

	rival_bar.setSize(sf::Vector2f(192, 8));
	rival_hp_bar.setSize(sf::Vector2f(192, 8));
	player_bar.setSize(sf::Vector2f(192, 8));
	player_hp_bar.setSize(sf::Vector2f(192, 8));

	rival_bar_sprite.setPosition(125, 77);
	player_bar_sprite.setPosition(381, 297);
	rival_frame.setPosition(33, 65);
	player_pres_frame.setPosition(289, 321);
	player_frame.setPosition(289, 289);
	player_ps_text_sprite.setPosition(321, 289);
	rival_ps_text_sprite.setPosition(65, 69);
	player_level_text_sprite.setPosition(449, 261);
	rival_level_text_sprite.setPosition(129, 33);

	rival_bar.setPosition(129, 81);
	rival_hp_bar.setPosition(129, 81);
	player_bar.setPosition(385, 301);
	player_hp_bar.setPosition(385, 301);

	set_victory(false);
	set_defeated(false);

	fainted_pokes = 0;

	rival_presentation = true;
	marked_selection = 1;
	marked_move = 1;
	marked_poke = 1;
	marked_poke_action = 1;

	selectioned_move = 0;
	selectioned_action = 0;
	selectioned_poke = 0;
	selectioned_poke_action = 0;

	status_screen = 1;

	turn_confirmed = false;
	turn_completed = false;

	poke_transition = false;
	first_poke_transition = false;

	text_state = false;
	
	std::array<int, 6> possible_poke;
	srand(unsigned int(time(NULL)));
	for (int i = 0; i < 6; i++)
	{
		
		int num = 1 + (rand() % 151);
		

		if (num == 132)
		{
			i--;
			continue;
		}else if(std::find(possible_poke.begin(), possible_poke.end(), num) != possible_poke.end())
		{
			i--;
			continue;
		}
		else
		{
			possible_poke[i] = num;
			Pokemon* poke_num = new Pokemon(num);
			player_pokemons[i] = poke_num;
		}
	}
}

void Combat::update()
{
	if (text_state)
	{
		update_text();
	}
	else if (poke_transition || rival_presentation)
	{
		if (poke_transition && !rival_presentation)
		{
			rival_poke_change();
		}

		if (rival_presentation && !poke_transition)
		{
			rival->sprite_update();
			player_sprite_update();
		}
	}
	else
	{
		if (!turn_confirmed)
		{

			if (act_player_pokemon->get_fainted())
			{
				if (fainted_pokes >= 5)
				{
					set_defeated(true);
				}
				change_pokemon();
			}
			else
			{
				switch (selectioned_action)
				{
					default: //select action
						select_action();

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							action_confirmed();
						}
						break;
					case 1: //fight
						select_move();

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						{
							selectioned_action = 0;
							sf::sleep(sf::seconds(.2f));
						}
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
						{
							move_confirmed();
						}
						break;
					case 2: //pokemon

						change_pokemon();

						break;
					case 3: //bag
						set_text("No tienes objetos.");
						break;
					case 4: //run
						set_text("No puedes huir de un combate contra un entrenador.");
						break;
				}
			}
		}
		else
		{
			turn();
		}
	}
}

void Combat::render(sf::RenderWindow& window)
{
	draw_box_interface(0, TEXT_BOX_Y * SPRITE_SIZE, TEXT_BOX_X, 20, window);
	if(rival_presentation || poke_transition || first_poke_transition)
	{

		if (poke_transition || first_poke_transition)
		{
			draw_transition(window);
		}

		if (rival_presentation)
		{
			draw_presentation(window);
		}

	}
	else
	{
		draw_hud(window);

		if (!turn_completed)
		{
			if (act_rival_pokemon->get_fainted())
			{
				rival_poke_change();
			}
			
			if (act_player_pokemon->get_fainted())
			{
				current_time = static_cast<char>(floor(get_current_animation_time() / 16));
				draw_combat_change_poke_interface(window, player_pokemons, marked_poke, false, current_time);
				if (selectioned_poke != 0)
				{
					draw_combat_change_poke_interface(window, player_pokemons, marked_poke, true, current_time, marked_poke_action);
				}
				set_current_animation_time((get_current_animation_time() + 1) % (2 * 16));
			}
			else if (poke_changed)
			{
				draw_poke_change(window);
			}
			else
			{
				switch (selectioned_action)
				{
					case 0: //Selecct action
						draw_combat_select_interface(window, marked_selection);
						break;
					case 1: //Fight
						draw_combat_move_interface(window, act_player_pokemon->get_moves(), marked_move);
						break;
					case 2: //Change pokemon
						current_time = char(floor(get_current_animation_time() / 16));
						switch (selectioned_poke)
						{
							default:
								
								switch (selectioned_poke_action)
								{
									case 0:
										draw_combat_change_poke_interface(window, player_pokemons, marked_poke, true, current_time, marked_poke_action);
										break;
									case 2:
										draw_pokemon_status_interface(window, player_pokemons[selectioned_poke-1], status_screen);
										break;

								}
								
								break;
							case 0:
								draw_combat_change_poke_interface(window, player_pokemons, marked_poke, false, current_time);
								break;
						}

						set_current_animation_time((get_current_animation_time() + 1) % (2 * 16));
						break;
					case 3: //Bag
						set_text("No tienes objetos.");
						draw_text(window);
						break;
					case 4: //Run
						set_text("No puedes huir de un combate contra un entrenador.");
						draw_text(window);
						break;
				}
			}

			
		}
		else
		{
			draw_turn(window);
		}
		
		

	}

}

void Combat::turn()
{
	int m = rand() % 4;
	rival_move = act_rival_pokemon->get_moves()[m];

	turn_order();

	selectioned_action = 0;
	turn_confirmed = false;
	turn_completed = true;
}

void Combat::select_move()
{
	marked_move = change_combat_move(marked_move);
}

void Combat::move_confirmed()
{
	selectioned_move = marked_move;
	player_move = act_player_pokemon->get_moves()[selectioned_move-1];

	turn_confirmed = true;
	sf::sleep(sf::seconds(.2f));
}

void Combat::select_action()
{
	marked_selection = change_combat_selection(marked_selection);
}

void Combat::action_confirmed()
{
	selectioned_action = marked_selection;
	sf::sleep(sf::seconds(.2f));
}

void Combat::select_poke()
{
	marked_poke = change_combat_poke(marked_poke);
}

void Combat::select_poke_action()
{
	marked_poke_action = change_combat_poke_action(marked_poke_action);
}

void Combat::change_pokemon()
{
	switch (selectioned_poke)
	{
		case 0:
			select_poke();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				selectioned_action = 0;
				sf::sleep(sf::seconds(.2f));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				poke_confirmed();
			}

			break;
		default:
			switch (selectioned_poke_action)
			{
				case 0:
					select_poke_action();

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						selectioned_poke = 0;
						sf::sleep(sf::seconds(.2f));
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
					{
						poke_action_confirmed();
					}
					break;

				case 1:
					player_poke_change();
					break;

				case 2:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					{
						status_screen = 1;
						selectioned_poke_action = 0;
						sf::sleep(sf::seconds(.2f));
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						switch (status_screen)
						{
							case 1:
								status_screen = 2;
								break;
							case 2:
								status_screen = 1;
								break;
						}
						sf::sleep(sf::seconds(.2f));
					}
					break;

				case 3:
					selectioned_poke_action = 0;
					marked_poke_action = 1;
					selectioned_poke = 0;
					sf::sleep(sf::seconds(.2f));
					break;

				
			}
	}
}

void Combat::poke_confirmed()
{
	selectioned_poke = marked_poke;
	sf::sleep(sf::seconds(.2f));
}

void Combat::poke_action_confirmed()
{
	selectioned_poke_action = marked_poke_action;
	sf::sleep(sf::seconds(.2f));
}

bool Combat::calc_hit(Move* attack, Pokemon* aggressor, Pokemon* defensor)
{
	
	bool hit;
	if (defensor->get_fainted())
	{
		hit = false;
		return hit;
	}
	int aggressor_accuracy = get_accuracy(aggressor) / 100;
	int defensor_evasion = get_evasion(defensor) / 100;

	int prob = (attack->get_accuracy() / 100) * (aggressor_accuracy / defensor_evasion);

	if (prob >= 1) 
	{
		hit = true;
	} 
	else
	{
		int calc = (1 + rand() % 100) / 100;
		if (calc > prob)
		{
			hit = false;
		}
		else
		{
			hit = true;
		}
	}
	return hit;
}

bool Combat::calc_crit(Damage_Move* attack)
{
	srand(static_cast<unsigned int>(time(0)));

	float crit_prob;
	int total_crit_prob = 100;

	if(attack->get_critical_bonus())
	{
		crit_prob = 4.167f;
	}
	else
	{
		crit_prob = 12.5f;
	}

	int result = rand() % (total_crit_prob + 1);

	if (result < crit_prob)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Combat::turn_order()
{
	if (player_move == nullptr)
	{
		order = 0;
		return;
	}

	int player_velocity = static_cast<int>(act_player_pokemon->get_act_stats()[stats::velocity]);
	if (act_player_pokemon->get_status_problem() == status_problems::paralyzed)
	{
		player_velocity = player_velocity / 2;
	}

	int rival_velocity = static_cast<int>(act_rival_pokemon->get_act_stats()[stats::velocity]);
	if (act_rival_pokemon->get_status_problem() == status_problems::paralyzed)
	{
		rival_velocity = rival_velocity / 2;
	}


	if (rival_move->get_priority() > player_move->get_priority())
	{
		order = 1;
		return;
	}

	if (rival_move->get_priority() < player_move->get_priority())
	{
		order = 2;
		return;
	}

	if (rival_move->get_priority() == player_move->get_priority())
	{
		if (rival_velocity > player_velocity)
		{
			order = 1;
			return;
		}

		if (rival_velocity < player_velocity)
		{
			order = 2;
			return;
		}

		if (rival_velocity == player_velocity)
		{
			order = 1 + rand() % 2;
			return;
		}
		
	}

}

void Combat::player_attack()
{
	if (!act_player_pokemon->get_fainted())
	{
		if (act_player_pokemon->get_status_problem() == status_problems::asleep)
		{
			if (!act_player_pokemon->status_problem_effect())
			{
				set_player_text(act_player_pokemon->get_name() + " está dormido.");
				return;
			}
		}

		if (act_player_pokemon->get_status_problem() == status_problems::paralyzed)
		{
			if (!act_player_pokemon->status_problem_effect())
			{
				set_player_text(act_player_pokemon->get_name() + " está paralizado.");
				return;
			}
		}

		for (std::pair s : act_player_pokemon->get_status_changes())
		{
			switch (s.first)
			{
				case status_changes::flinch:
					if (!act_player_pokemon->status_change_effect())
					{
						set_player_text(act_player_pokemon->get_name() + " está amedrentado.");
					}
					break;
				case status_changes::confused:
					if (!act_player_pokemon->status_change_effect())
					{
						set_rival_text(act_player_pokemon->get_name() + " está tan confuso que se hirió a sí mismo.");
						act_player_pokemon->confuse_damage();
					}
					break;
			}
		}

		switch (player_move->get_objective())
		{
		case objective_type::user:
				set_player_text(player_move->status_use(act_player_pokemon));
				break;
		case objective_type::enemy:
				if (calc_hit(player_move, act_player_pokemon, act_rival_pokemon) == true)
				{
					if (typeid(*player_move) == typeid(Damage_Move))
					{
						set_player_text(player_move->damage_use(act_player_pokemon, act_rival_pokemon, calc_crit(dynamic_cast<Damage_Move*>(player_move))));
					}
					else
					{
						set_player_text(player_move->status_use(act_player_pokemon, act_rival_pokemon));
					}
				}
				else
				{
					set_player_text("Pero, ¡falló!");
				}
				break;
		}
	}
}

void Combat::rival_attack()
{
	if (!act_rival_pokemon->get_fainted())
	{
		if (act_rival_pokemon->get_status_problem() == status_problems::asleep)
		{
			if (!act_rival_pokemon->status_problem_effect())
			{
				set_rival_text(act_rival_pokemon->get_name() + " está dormido.");
				return;
			}
		}

		if (act_rival_pokemon->get_status_problem() == status_problems::paralyzed)
		{
			if (!act_rival_pokemon->status_problem_effect())
			{
				set_rival_text(act_rival_pokemon->get_name() + " está paralizado.");
				return;
			}
		}

		for (std::pair s : act_rival_pokemon->get_status_changes())
		{
			switch (s.first)
			{
			case status_changes::flinch:
				if (!act_rival_pokemon->status_change_effect())
				{
					set_player_text(act_rival_pokemon->get_name() + " está amedrentado.");
				}
				break;
			case status_changes::confused:
				if (!act_rival_pokemon->status_change_effect())
				{
					set_rival_text(act_rival_pokemon->get_name() + " está tan confuso que se hirió a sí mismo.");
					act_rival_pokemon->confuse_damage();
				}
				break;
			}
		}

		switch (rival_move->get_objective())
		{
			case objective_type::user:
				set_rival_text(rival_move->status_use(act_rival_pokemon));
				break;
			case objective_type::enemy:
				if (calc_hit(rival_move, act_rival_pokemon, act_player_pokemon) == true)
				{
					if (typeid(*rival_move) == typeid(Damage_Move))
					{
						set_rival_text(rival_move->damage_use(act_rival_pokemon, act_player_pokemon, calc_crit(dynamic_cast<Damage_Move*>(rival_move))));
					}
					else
					{
						set_rival_text(rival_move->status_use(act_rival_pokemon, act_player_pokemon));
					}
				}
				else
				{
					set_rival_text("Pero, ¡falló!");
				}
				break;
		}
	}
}

void Combat::rival_poke_change()
{
	if (act_rival_pokemon != nullptr && act_rival_pokemon->get_fainted())
	{
		poke_changed = true;
	}
	for each(Pokemon * poke in rival->get_pokemons())
	{
		if (poke != nullptr && !poke->get_fainted())
		{
			act_rival_pokemon = poke;
			set_text(rival->get_name() + " envio a " + act_rival_pokemon->get_name() + ".");
			break;
		}
		
	}
	if (act_rival_pokemon == nullptr || act_rival_pokemon->get_fainted())
	{
		set_victory(true);
	}
	
}

void Combat::player_first_poke()
{
	act_player_pokemon = player_pokemons[0];
	set_text("¡Adelante " + act_player_pokemon->get_name() + "!");
	first_poke_transition = true;
	
}

void Combat::player_poke_change()
{
	if (!act_player_pokemon->get_fainted())
	{
		if (act_player_pokemon->get_status_problem() == status_problems::badly_poisoned)
		{
			act_player_pokemon->reset_poison_turns();
		}
		player_pokemons[0] = player_pokemons[selectioned_poke - 1];
		player_pokemons[selectioned_poke - 1] = act_player_pokemon;
		act_player_pokemon = player_pokemons[0];
		player_move = nullptr;
		set_text("¡Adelante " + act_player_pokemon->get_name() + "!");
		poke_changed = true;
		turn_confirmed = true;
	}
	else
	{
		fainted_pokes += 1;
		
		player_pokemons[0] = player_pokemons[selectioned_poke - 1];
		player_pokemons[selectioned_poke - 1] = act_player_pokemon;
		act_player_pokemon = player_pokemons[0];
		set_text("¡Adelante " + act_player_pokemon->get_name() + "!");
		poke_changed = true;
	}
}

int Combat::get_accuracy(Pokemon* poke)
{
	return static_cast<int>(poke->get_act_stats()[static_cast<stats>(6)]);
}

int Combat::get_evasion(Pokemon* poke)
{
	return static_cast<int>(poke->get_act_stats()[static_cast<stats>(7)]);
}

void Combat::draw_hud(sf::RenderWindow& window)
{
	draw_frames(window);
	if (!act_rival_pokemon->get_fainted())
	{
		window.draw(act_rival_pokemon->get_front_sprite());
	}
	if (!act_player_pokemon->get_fainted())
	{
		window.draw(act_player_pokemon->get_back_sprite());
	}
}

void Combat::draw_presentation(sf::RenderWindow& window)
{
	window.draw(rival->get_sprite());
	window.draw(player_sprite);

	if(player_sprite.getPosition().x == 17 && rival->get_sprite().getPosition().x == 385)
	{
		pokemon_preview(window, true);
		set_text("Has retado al lider de gimnasio " + rival->get_name() + ".");
		draw_text(window);
	}
}

void Combat::draw_transition(sf::RenderWindow& window)
{
	window.draw(player_sprite);
	draw_text(window);
	if (first_poke_transition)
	{
		window.draw(act_rival_pokemon->get_front_sprite());
		window.draw(rival_frame);
	}
}

void Combat::draw_poke_change(sf::RenderWindow& window)
{
	draw_text(window);
}

void Combat::draw_turn(sf::RenderWindow& window)
{
	switch (order)
	{
		case 0://solo ataca el rival
			
			if (rival_turn == false)
			{
				set_text(act_rival_pokemon->get_name() + " enemigo usó " + rival_move->get_name());
				if (move_text == 0)
				{
					draw_battle_text(window, get_text());
				}
				else
				{
					if (rival_texts == "")
					{
						rival_attack();
					}
					else
					{
						if (rival_texts != "A")
						{
							draw_battle_text(window, get_rival_text());
						}
						else
						{
							draw_battle_text(window, "");
						}
					}
				}
			}
			else
			{
				end_turn = true;
			}
			break;
		case 1://ataca primero el rival
			if(rival_turn == false)
			{
				set_text(act_rival_pokemon->get_name() + " enemigo usó " + rival_move->get_name());
				if(move_text == 0)
				{
					draw_battle_text(window, get_text());
				}
				else
				{
					if (rival_texts == "")
					{
						rival_attack();
					}
					else
					{
						if (rival_texts != "A")
						{
							draw_battle_text(window, get_rival_text());
						}
						else
						{
							draw_battle_text(window, "");
						}
					}
				}
			}
			else
			{
				if (!act_player_pokemon->get_fainted())
				{
					set_text(act_player_pokemon->get_name() + " usó " + player_move->get_name());
					if (move_text == 0)
					{
						draw_battle_text(window, get_text());
					}
					else
					{
						if (player_texts == "")
						{
							player_attack();
						}
						else
						{
							if (player_texts != "A")
							{
								draw_battle_text(window, get_player_text());
							}
							else
							{
								draw_battle_text(window, "");
							}
						}
					}
				}
				else
				{
					end_turn = true;
				}
			}
			break;
		case 2://ataca primero el jugador
			if (player_turn == false)
			{
				set_text(act_player_pokemon->get_name() + " usó " + player_move->get_name());
				if (move_text == 0)
				{
					draw_battle_text(window, get_text());
				}
				else
				{
					if (player_texts == "")
					{
						player_attack();
					}
					else
					{
						if (player_texts != "A")
						{
							draw_battle_text(window, get_player_text());
						}
						else
						{
							draw_battle_text(window, "");
						}
					}
				}
			}
			else
			{
				if (!act_rival_pokemon->get_fainted())
				{
					set_text(act_rival_pokemon->get_name() + " enemigo usó " + rival_move->get_name());
					if (move_text == 0)
					{
						draw_battle_text(window, get_text());
					}
					else
					{
						if (rival_texts == "")
						{
							rival_attack();
						}
						else
						{
							if (rival_texts != "A")
							{
								draw_battle_text(window, get_rival_text());
							}
							else
							{
								draw_battle_text(window, "");
							}
						}
					}
				}
				else
				{
					end_turn = true;
				}
			}
			break;
	}

	if (end_turn)
	{
		end_turn_actions();
		reset_turn_param();
	}
	
}

void Combat::draw_frames(sf::RenderWindow& window)
{

	int rival_hp_percent = (100 * act_rival_pokemon->get_hp()) / act_rival_pokemon->get_max_hp();
	int player_hp_percent = (100 * act_player_pokemon->get_hp()) / act_player_pokemon->get_max_hp();

	rival_hp_bar.setSize(sf::Vector2f((rival_hp_percent * 192.f) / 100.f, 8.f));
	player_hp_bar.setSize(sf::Vector2f((player_hp_percent * 192.f) / 100.f, 8.f));

	if (rival_hp_percent > 50)
	{
		rival_hp_bar.setFillColor(sf::Color::Green);
	}
	else if (rival_hp_percent > 25 && rival_hp_percent <= 50)
	{
		rival_hp_bar.setFillColor(sf::Color::Yellow);
	}
	else
	{
		rival_hp_bar.setFillColor(sf::Color::Red);
	}

	if (player_hp_percent > 50)
	{
		player_hp_bar.setFillColor(sf::Color::Green);
	}
	else if (player_hp_percent > 25 && player_hp_percent <= 50)
	{
		player_hp_bar.setFillColor(sf::Color::Yellow);
	}
	else
	{
		player_hp_bar.setFillColor(sf::Color::Red);
	}

	rival_bar.setFillColor(sf::Color::White);
	player_bar.setFillColor(sf::Color::White);
	
	window.draw(rival_frame);
	window.draw(player_frame);

	window.draw(player_bar_sprite);
	window.draw(rival_bar_sprite);

	window.draw(rival_bar);
	window.draw(rival_hp_bar);
	window.draw(player_bar);
	window.draw(player_hp_bar);
	window.draw(player_ps_text_sprite);
	window.draw(rival_ps_text_sprite);

	draw_levels(window);

	write_rival_name(act_rival_pokemon->get_name(), window);
	write_player_name(act_player_pokemon->get_name(), window);
	write_player_hp(act_player_pokemon, window);
}

void Combat::draw_levels(sf::RenderWindow& window)
{
	if(act_player_pokemon->get_status_problem() == status_problems::null_problem)
	{
		window.draw(player_level_text_sprite);
		write_text(481, 261, std::to_string(act_player_pokemon->get_level()), window);
	}
	else
	{
		write_text(481,261,problem_spr(act_player_pokemon), window);
	}

	if (act_rival_pokemon->get_status_problem() == status_problems::null_problem)
	{
		window.draw(rival_level_text_sprite);
		write_text(161, 33, std::to_string(act_rival_pokemon->get_level()), window);
	}
	else
	{
		write_text(161, 33, problem_spr(act_rival_pokemon), window);
	}
}

std::string Combat::problem_spr(Pokemon* poke)
{
	std::string problem;

	switch (poke->get_status_problem())
	{
		case status_problems::paralyzed:
			problem = "PAR";
			break;
		case status_problems::burned:
			problem = "QUE";
			break;
		case status_problems::poisoned:
			problem = "ENV";
			break;
		case status_problems::badly_poisoned:
			problem = "ENV";
			break;
		case status_problems::asleep:
			problem = "DOR";
			break;
		case status_problems::frozen:
			problem = "CON";
			break;
	}

	return problem;
}

void Combat::pokemon_preview(sf::RenderWindow& window, bool is_first)
{
	window.draw(rival_frame);
	window.draw(player_pres_frame);
	if (is_first)
	{

		int player_x = 353;
		int rival_x = 257;
		int player_y = 321;
		int rival_y = 65;

		for each(Pokemon* poke in rival->get_pokemons())
		{
			if (poke != nullptr)
			{
				preview_sprite.setTexture(*have_preview_texture);

				preview_sprite.setPosition(static_cast<float>(rival_x), static_cast<float>(rival_y));
				window.draw(preview_sprite);

				rival_x -= 32;
			}
			else
			{
				preview_sprite.setTexture(*null_preview_texture);

				preview_sprite.setPosition(static_cast<float>(rival_x), static_cast<float>(rival_y));
				window.draw(preview_sprite);

				rival_x -= 32;
			}
		}
		for each(Pokemon* poke in player_pokemons)
		{
			if (poke != nullptr)
			{
				preview_sprite.setTexture(*have_preview_texture);

				preview_sprite.setPosition(static_cast<float>(player_x), static_cast<float>(player_y));
				window.draw(preview_sprite);

				player_x += 32;
			}
			else
			{
				preview_sprite.setTexture(*null_preview_texture);

				preview_sprite.setPosition(static_cast<float>(player_x), static_cast<float>(player_y));
				window.draw(preview_sprite);

				player_x += 32;
			}
		}
	}
	else
	{
		int rival_x = 257;
		int rival_y = 65;
		for each(Pokemon * poke in rival->get_pokemons())
		{
			if (poke != nullptr)
			{
				if (poke->get_fainted() == false) 
				{
					preview_sprite.setTexture(*have_preview_texture);
				}
				else
				{
					preview_sprite.setTexture(*fainted_preview_texture);
				}

				preview_sprite.setPosition(static_cast<float>(rival_x), static_cast<float>(rival_y));
				window.draw(preview_sprite);

				rival_x -= 32;
			}
			else
			{
				preview_sprite.setTexture(*null_preview_texture);

				preview_sprite.setPosition(static_cast<float>(rival_x), static_cast<float>(rival_y));
				window.draw(preview_sprite);

				rival_x -= 32;
			}
		}
	}
}

void Combat::change_text_state()
{
	if (text_state == false) 
	{
		text_state = true;
		act_text_row = 1;
	}
	else
	{
		text_state = false;
	}
}

void Combat::update_text()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		act_text_row += 2;
		sf::sleep(sf::seconds(.2f));
	}
}

void Combat::player_sprite_update()
{
	if (player_sprite.getPosition().x > 17)
	{
		player_sprite.setPosition(player_sprite.getPosition().x - PRESENTATION_SPRITE_SPEED, 161);
	}
}

void Combat::draw_text( sf::RenderWindow& window)
{
	if (!text_state)
	{
		change_text_state();
	}

	draw_textbox(get_text(), act_text_row, window);
	if (act_text_row > get_lines_num(get_text()))
	{
		change_text_state();
		
		if (first_poke_transition)
		{
			first_poke_transition = false;
			return;
		}

		if(rival_presentation)
		{
			rival_presentation = false;
			poke_transition = true;
			return;
		}

		if (poke_changed)
		{
			poke_changed = false;
		}

		if (poke_transition)
		{
			poke_transition = false;
			player_first_poke();
			return;
		}
		reset_turn_param();
		return;
	}
}

void Combat::draw_battle_text(sf::RenderWindow& window, std::string text)
{
	if (!text_state)
	{
		change_text_state();
	}

	draw_textbox(text, act_text_row, window);
	if (act_text_row > get_lines_num(text))
	{
		change_text_state();

		if (move_text == 0)
		{
			move_text += 1;
			return;
		}

		if (move_text != 0 && rival_turn == false || move_text != 0 && player_turn == false)
		{
			move_text = 0;
			rival_turn = true;
			player_turn = true;
			
			return;
		}


		end_turn = true;
	}
}

void Combat::end_turn_actions()
{
	if (act_player_pokemon->get_status_problem() != status_problems::null_problem)
	{
		switch (act_player_pokemon->get_status_problem())
		{
			case status_problems::burned:
			case status_problems::poisoned:
			case status_problems::badly_poisoned:
				act_player_pokemon->status_problem_effect();
				break;
		}
	}
	if (act_rival_pokemon->get_status_problem() != status_problems::null_problem)
	{
		switch (act_rival_pokemon->get_status_problem())
		{
			case status_problems::burned:
			case status_problems::poisoned:
			case status_problems::badly_poisoned:
				act_rival_pokemon->status_problem_effect();
				break;
		}
	}
	
	if (act_player_pokemon->get_status_changes()[status_changes::flinch])
	{
		act_player_pokemon->end_turn_changes();
	}
	if (act_rival_pokemon->get_status_changes()[status_changes::flinch])
	{
		act_rival_pokemon->end_turn_changes();
	}
}

void Combat::reset_turn_param()
{
	rival_turn = false;
	set_rival_text("");
	player_turn = false;
	set_player_text("");
	move_text = 0;
	turn_completed = false;
	end_turn = false;
	selectioned_action = 0;
	selectioned_move = 0;
	selectioned_poke = 0;
	selectioned_poke_action = 0;
	player_move = nullptr;
}

std::string Combat::get_text()
{
	return general_texts;
}

void Combat::set_text(std::string new_text)
{
	general_texts = new_text;
}

std::string Combat::get_rival_text()
{
	return rival_texts;
}

void Combat::set_rival_text(std::string new_text)
{
	rival_texts = new_text;
}

std::string Combat::get_player_text()
{
	return player_texts;
}

void Combat::set_player_text(std::string new_text)
{
	player_texts = new_text;
}

short Combat::get_current_animation_time()
{
	return current_animation_time;
}

void Combat::set_current_animation_time(short current_time)
{
	current_animation_time = current_time;
}

bool Combat::get_victory()
{
	return victory;
}

void Combat::set_victory(bool winned)
{
	victory = winned;
}

bool Combat::get_defeated()
{
	return defeated;
}

void Combat::set_defeated(bool defeat)
{
	defeated = defeat;
}


