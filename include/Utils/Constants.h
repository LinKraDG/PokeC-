#pragma once

constexpr char* GAME_TITLE = "PokeC++";

constexpr char* BLANK_BACKGROUND_TEXTURE = "../Data/background.png";
constexpr char* TITLE_TEXTURE = "../Data/Sprites/Menu/Title.png";


constexpr char SPRITE_SIZE = 32;
constexpr char* FONT_SPRITES = "../Data/Text/Font.png";
constexpr char* PKMN_SPRITE = "../Data/Text/Font.png";
constexpr char* SELECTION_SPRITE = "../Data/Sprites/Menu/Selection.png";
constexpr char* BOX_SPRITES = "../Data/Text/Box/box_sprites.png";

constexpr char TEXT_BOX_X = 6;
constexpr char TEXT_BOX_Y = 12;

constexpr char SCREEN_HEIGHT = 18;
constexpr char SCREEN_WIDTH = 20;
//constexpr char SCREEN_RESIZE = 34;

constexpr char SELECTION_ANIMATION_SPEED = 32;

constexpr char PRESENTATION_SPRITE_SPEED = 8;


// Badgets sprites
constexpr char* BADGET_BACKGROUND_TEXTURE = "../Data/badgets_background.png";

constexpr char* BOULDER_BADGET = "../Data/Sprites/Menu/Badges/Boulder.png";
constexpr char* BLOCKED_BOULDER_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Boulder.png";

constexpr char* CASCADE_BADGET = "../Data/Sprites/Menu/Badges/Cascade.png";
constexpr char* BLOCKED_CASCADE_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Cascade.png";

constexpr char* THUNDER_BADGET = "../Data/Sprites/Menu/Badges/Thunder.png";
constexpr char* BLOCKED_THUNDER_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Thunder.png";

constexpr char* RAINBOW_BADGET = "../Data/Sprites/Menu/Badges/Rainbow.png";
constexpr char* BLOCKED_RAINBOW_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Rainbow.png";

constexpr char* SOUL_BADGET = "../Data/Sprites/Menu/Badges/Soul.png";
constexpr char* BLOCKED_SOUL_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Soul.png";

constexpr char* MARSH_BADGET = "../Data/Sprites/Menu/Badges/Marsh.png";
constexpr char* BLOCKED_MARSH_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Marsh.png";

constexpr char* VOLCANO_BADGET = "../Data/Sprites/Menu/Badges/Volcano.png";
constexpr char* BLOCKED_VOLCANO_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Volcano.png";

constexpr char* EARTH_BADGET = "../Data/Sprites/Menu/Badges/Earth.png";
constexpr char* BLOCKED_EARTH_BADGET = "../Data/Sprites/Menu/Badges/Blocked_Earth.png";

constexpr char* BADGET_SELECTION_FRAME = "../Data/Sprites/Menu/Badges/Badge_frame.png";


// Combat sprites
constexpr char* LEAGUE_ARCHIVES = "../Data/League/";
constexpr char* LEAGUE_SPRITES = "../Data/Sprites/Gameplay/Characters/";
constexpr char* PLAYER_SPRITE = "../Data/Sprites/Gameplay/Characters/red_back.png";

constexpr char* POKEMON_ARCHIVES = "../Data/Pokemons/";
constexpr char* POKEMON_SPRITES = "../Data/Sprites/Gameplay/Pokemons/";
constexpr char* FRONT_SPRITES = "_front.png";
constexpr char* BACK_SPRITES = "_back.png";
constexpr char* POKEMON_MENU_SPRITES = "../Data/Sprites/Menu/";
constexpr char* MOVES_ARCHIVES = "../Data/Moves/";

constexpr char* RIVAL_COMBAT_FRAME = "../Data/Sprites/Gameplay/Combat/rival_frame.png";
constexpr char* PLAYER_PRESENTATION_FRAME = "../Data/Sprites/Gameplay/Combat/player_pres_frame.png";
constexpr char* PLAYER_COMBAT_FRAME = "../Data/Sprites/Gameplay/Combat/player_frame.png";

constexpr char* LEVEL_TEXT_TEXTURE = "../Data/Sprites/Gameplay/Combat/n_sprite.png";
constexpr char* PS_TEXT_TEXTURE = "../Data/Sprites/Gameplay/Combat/ps_sprite.png";
constexpr char* HEALTH_BAR_TEXTURE = "../Data/Sprites/Gameplay/Combat/health_bar.png";

constexpr char* POKEMON_PREVIEW_NULL = "../Data/Sprites/Gameplay/Combat/null_pokemon.png";
constexpr char* POKEMON_PREVIEW_HAVE = "../Data/Sprites/Gameplay/Combat/have_pokemon.png";
constexpr char* POKEMON_PREVIEW_FAINTED = "../Data/Sprites/Gameplay/Combat/fainted_pokemon.png";

constexpr char* PNG = ".png";

// Status screen sprites
constexpr char* S_STATUS_FRAME_TEXTURE = "../Data/Sprites/Gameplay/Combat/s_status_screen_frame.png";
constexpr char* I_STATUS_FRAME_TEXTURE = "../Data/Sprites/Gameplay/Combat/i_status_screen_frame.png";
constexpr char* A_TEXTURE = "../Data/Sprites/Gameplay/Combat/a_sprite.png";
constexpr char* ID_TEXTURE = "../Data/Sprites/Gameplay/Combat/id_sprite.png";
constexpr char* NO_TEXTURE = "../Data/Sprites/Gameplay/Combat/number_sprite.png";



 
//origin screen: 160 width, 144 height
//this screen:	 640 width, 576 height


// Enums

enum class type
{
	steel,
	water,
	bug,
	dragon,
	electric,
	ghost,
	fairy,
	fire,
	ice,
	fighting,
	normal,
	grass,
	psychic,
	rock,
	dark,
	ground,
	poison,
	flying,
	null_type = 100
};

enum class nature
{
	hardy,
	lonely,
	brave,
	adamant,
	naughty,
	bold,
	docile,
	relaxed,
	impish,
	lax,
	timid,
	hasty,
	serious,
	jolly,
	naive,
	modest,
	mild,
	quiet,
	bashful,
	rash,
	calm,
	gentle,
	sassy,
	careful,
	quirky
};

enum class stats
{
	hp,
	attack,
	defense,
	special_attack,
	special_defense,
	velocity,
	accuracy,
	evasion
};

enum class move_category
{
	physical,
	special,
	status
};

enum class objective_type
{
	user,
	enemy
};

enum class move_effect
{
	status_problem,
	status_change,
	user_stat,
	enemy_stat,
	heal
};

enum class status_problems
{
	paralyzed,
	burned,
	poisoned,
	badly_poisoned,
	asleep,
	frozen,
	null_problem = 100
};

enum class status_changes
{
	flinch,
	confused,
	trapped,
	bound,
	seeded
};

enum class recoil_heal_type
{
	objective,
	max
};

enum class special_cases
{
	accumulation_damage,
	charge_attack,
	rest_turn,
	fixed_damage,
	porcentual_damage
};