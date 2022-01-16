// [shared.c]
// you should define the shared variable declared in the header here.

#include "shared.h"
#include "utility.h"
#include "game.h"
// #include "scene_menu.h"

ALLEGRO_FONT* font_pirulen_32;
ALLEGRO_FONT* font_pirulen_24;
ALLEGRO_SAMPLE* themeMusic = NULL;
ALLEGRO_SAMPLE* PACMAN_MOVESOUND = NULL;
ALLEGRO_SAMPLE* PACMAN_EATFRUIT = NULL;
ALLEGRO_SAMPLE* PACMAN_DEATH_SOUND = NULL;
ALLEGRO_SAMPLE* GAMEOVER = NULL;
ALLEGRO_SAMPLE* YOU_WIN = NULL;
ALLEGRO_SAMPLE* PLAYING = NULL;
ALLEGRO_SAMPLE* PLAYINGB = NULL;
ALLEGRO_SAMPLE* PLAYINGC = NULL;
ALLEGRO_FONT* menuFont = NULL, * end1 = NULL, * end2 = NULL, *end3 = NULL, * end4 = NULL, * end5 = NULL, *volume1 = NULL, *volume2 = NULL;
int fontSize = 30;
float music_volume = 0.5;
float effect_volume = 0.5;
bool gameDone = false;

/*
	A way to accelerate is load assets once.
	And delete them at the end.
	This method does provide you better management of memory.
	
*/
void shared_init(void) {
	volume1 = load_font("Assets/Minecraft.ttf", 40);
	volume2 = load_font("Assets/Minecraft.ttf", 40);
	end1 = load_font("Assets/Minecraft.ttf", 80);
	end2 = load_font("Assets/Minecraft.ttf", 40);
	end3 = load_font("Assets/Minecraft.ttf", 40);
	end4 = load_font("Assets/Minecraft.ttf", 50);
	end5 = load_font("Assets/Minecraft.ttf", 100);
	menuFont = load_font("Assets/Minecraft.ttf", fontSize);
	themeMusic = load_audio("Assets/Music/original_theme.ogg");
	PACMAN_MOVESOUND = load_audio("Assets/Music/pacman-chomp.ogg");
	PACMAN_EATFRUIT = load_audio("Assets/Music/pacman_eatfruit.ogg");
	PACMAN_DEATH_SOUND = load_audio("Assets/Music/pacman_death.ogg");
	GAMEOVER = load_audio("Assets/Music/gameover.ogg");
	YOU_WIN = load_audio("Assets/Music/you win.ogg");
	PLAYING = load_audio("Assets/Music/playing.ogg");
	PLAYINGB = load_audio("Assets/Music/playingb.ogg");
	PLAYINGC = load_audio("Assets/Music/playingc.ogg");
}

void shared_destroy(void) {

	al_destroy_font(menuFont);
	al_destroy_sample(themeMusic);
	al_destroy_sample(PACMAN_MOVESOUND);
	al_destroy_sample(PACMAN_DEATH_SOUND);
	al_destroy_sample(PACMAN_EATFRUIT);
	al_destroy_sample(GAMEOVER);
	al_destroy_sample(YOU_WIN);
	al_destroy_sample(PLAYING);
	al_destroy_sample(PLAYINGB);
	al_destroy_sample(PLAYINGC);
}