#include <Core/Screens/Screens.h>
#include <Core/Screens/Title.h>
#include "Core/Selections.h"
//#include <corecrt_math.h>
#include <Utils/Constants.h>
#include <SFML/Window/Event.hpp>
#include <Core/Screens/Badges.h>
#include <SFML/System/Sleep.hpp>
#include <Panels/Interfaces.h>
#include <UI/Text.h>
#include <Gameplay/Combat.h>
#include <SFML/Graphics/RenderWindow.hpp>

bool Screens::Init()
{
    for (int i = 0; i < 8; i++)
    {
        badges[i] = false;
    }

    marked_selection = 1;
    selectioned_badge = 0;
    selectioned_mode = 0;
    return true;
}

void Screens::update()
{
    switch (selectioned_mode)
    {
        case 0:
            marked_selection = change_menu_selection(marked_selection);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                selection_confirmed();
            }
            break;
        case 1: //League
            if (selectioned_badge != 0)
            {
                combat->update();
                if (combat->get_victory() || combat->get_defeated())
                {
                    if(combat->get_victory())
                    {
                        badges[selectioned_badge - 1] = true;
                    }
                    selectioned_badge = 0;
                    delete combat;
                }
            }
            else {
                marked_selection = change_badge_selection(marked_selection);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    selectioned_mode = 0;
                    sf::sleep(sf::seconds(.2f));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    selectioned_badge = marked_selection;

                    combat = new Combat(selectioned_badge);
                    sf::sleep(sf::seconds(.2f));

                }
            }
            
            break;
        case 2: //Exit
            
            break;
        default:
            break;
    }
}

void Screens::render(sf::RenderWindow& window)
{
    if (selectioned_mode == 1 && selectioned_badge != 0)
    {
        combat->render(window);
    }
    else
    {
        switch (selectioned_mode)
        {
            case 0:
                draw_title_screen(window, marked_selection);
                break;
            case 1:
                draw_badges_screen(window, marked_selection, badges);
                break;
            case 2:
                window.close();
                break;
            case 3:
                break;
        }
    }
    

}

void Screens::selection_confirmed()
{
    selectioned_mode = marked_selection;
    marked_selection = 1;
    sf::sleep(sf::seconds(.2f));
}
