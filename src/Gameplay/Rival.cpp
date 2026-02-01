#include <Gameplay/Rival.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <Core/AssetManager.h>


using json = nlohmann::json;

Rival::~Rival()
{
    for each(Pokemon* poke in pokemons)
    {
        delete poke;
    }
}

Rival::Rival(std::string name)
{
    std::string archive = LEAGUE_ARCHIVES + name + ".json";
    std::ifstream pf(archive);

    json j;
    pf >> j;

    //char* rival_archive = (char*)name.c_str() + *PNG;

    //rival_texture = AssetManager::getInstance()->loadTexture(LEAGUE_SPRITES + *rival_archive);
    

    //begin placeholder
    std::string sprite_test = LEAGUE_SPRITES;
    sprite_test += "brock.png";
    rival_texture = AssetManager::getInstance()->loadTexture(sprite_test.c_str());
    //end placeholder
    
    rival_sprite.setTexture(*rival_texture);
    rival_sprite.setPosition(-223, 0);

    set_name(j["name"]);

    std::array<int, 6> pk;
    for (int i = 0; i < 6; i++)
    {
        if (j["pokemons"][i] == 0)
        {
            pk[i] = NULL;
        }
        else
        {
            pk[i] = j["pokemons"][i];
        }
    }
    set_pokemons(pk);
}

void Rival::sprite_update()
{
    if (rival_sprite.getPosition().x < 385)
    {
        rival_sprite.setPosition(rival_sprite.getPosition().x + PRESENTATION_SPRITE_SPEED, 0);
    }
}

sf::Sprite Rival::get_sprite()
{
    return rival_sprite;
}

void Rival::set_name(std::string name)
{
    rival_name = name;
}

std::string Rival::get_name()
{
    return rival_name;
}

void Rival::set_pokemons(std::array<int, 6> poke_num)
{
    for (int i = 0; i < 6; i++)
    {
        if (poke_num[i] == 0) 
        {
            pokemons[i] = nullptr;
        }
        else
        {
            pokemons[i] = new Pokemon(poke_num[i]);
        }
    }
}

std::array<Pokemon*, 6> Rival::get_pokemons()
{
    return pokemons;
}
