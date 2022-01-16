#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string.h>
#include "game.h"
#include "shared.h"
#include "utility.h"
#include "scene_game.h"
#include "scene_menu.h"
#include "pacman_obj.h"
#include "ghost.h"
#include "map.h"


// [HACKATHON 2-0]
// Just modify the GHOST_NUM to 1
#define GHOST_NUM 4
/* global variables*/
extern const uint32_t GAME_TICK_CD;
extern uint32_t GAME_TICK;
extern ALLEGRO_TIMER* game_tick_timer;
int game_main_Score = 0;
bool game_over = false;

/* Internal variables*/

static ALLEGRO_TIMER* power_up_timer;
static const int power_up_duration = 10;
static Pacman* pman;
static Map* basic_map;
static Ghost** ghosts;
bool debug_mode = false;
bool cheat_mode = false;

/* Declare static function prototypes */
static void init(void);
static void step(void);
static void checkItem(void);
static void status_update(void);
static void update(void);
static void draw(void);
static void printinfo(void);
static void destroy(void);
static void on_key_down(int key_code);
static void on_mouse_down(void);
static void render_init_screen(void);
static void draw_hitboxes(void);

static void b_init(void);
static void c_init(void);
static void draw_hall(void);
static ALLEGRO_SAMPLE_ID menuBGM;
static ALLEGRO_SAMPLE_ID gameover;
static ALLEGRO_SAMPLE_ID you_win;
static ALLEGRO_SAMPLE_ID playing;
static ALLEGRO_SAMPLE_ID playingb;
static ALLEGRO_SAMPLE_ID playingc;
//
void draw_lose(void) {
	char buffer[100];
	int sum = 0;
	for (int i = 0; i < GHOST_NUM; i++) {

		sum += ghosts[i]->pp;
	}
	game_main_Score = ((basic_map->beansNum) - (basic_map->beansCount)) * 10 + sum * 200;
	sprintf_s(buffer, sizeof(buffer), "Your score is : %d", game_main_Score);
	al_clear_to_color(al_map_rgb(3, 38, 58));
	al_draw_text(end5, al_map_rgb(250
		, 0, 0), 400, 200, ALLEGRO_ALIGN_CENTRE, "Game Over");
	al_draw_text(end2, al_map_rgb(222, 125, 44), 400, 400, ALLEGRO_ALIGN_CENTRE, buffer);
	al_draw_text(end3, al_map_rgb(222, 125, 44), 400, 500, ALLEGRO_ALIGN_CENTRE, "Press \"Enter\" to go to menu");
	al_draw_text(end3, al_map_rgb(222, 125, 44), 400, 600, ALLEGRO_ALIGN_CENTRE, "Press \"H\" to go to hall");
}

void press(int keycode) {
	if (keycode == ALLEGRO_KEY_ENTER) {
		stop_bgm(gameover);
		game_change_scene(scene_menu_create());
	}
	if (keycode == ALLEGRO_KEY_H) {
		stop_bgm(gameover);
		game_change_scene(scene_hall_create());
	}
}
void press_hall(int keycode) {
	if (keycode == ALLEGRO_KEY_A) {
		stop_bgm(menuBGM);
		playing = play_bgm(PLAYING, music_volume);
		game_change_scene(scene_main_create());
	}
	if (keycode == ALLEGRO_KEY_B) {
		stop_bgm(menuBGM);
		playingb = play_bgm(PLAYINGB, music_volume);
		game_change_scene(scene_B_create());
	}
	if (keycode == ALLEGRO_KEY_C) {
		stop_bgm(menuBGM);
		playingc = play_bgm(PLAYINGC, music_volume);
		game_change_scene(scene_C_create());
	}
}
static void init_lose() {
	stop_bgm(gameover);
	stop_bgm(playing);
	stop_bgm(playingb);
	stop_bgm(playingc);
	gameover = play_audio(GAMEOVER, music_volume);
}
static void init_win() {
	stop_bgm(you_win);
	stop_bgm(playing);
	stop_bgm(playingb);
	stop_bgm(playingc);
	you_win = play_audio(YOU_WIN, music_volume);
}
Scene scene_lose_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.initialize = &init_lose;
	scene.name = "End";
	scene.draw = &draw_lose;
	scene.on_key_down = &press;
	game_log("lose scene created");
	return scene;
}

void draw_win(void) {
	char buffer[100];
	int sum = 0;
	for (int i = 0; i < GHOST_NUM; i++) {

		sum += ghosts[i]->pp;
	}
	game_main_Score = ((basic_map->beansNum) - (basic_map->beansCount)) * 10 + sum * 200;
	sprintf_s(buffer, sizeof(buffer), "Your score is : %d", game_main_Score);
	al_clear_to_color(al_map_rgb(3, 38, 58));
	al_draw_text(end5, al_map_rgb(250, 218, 141), 400, 200, ALLEGRO_ALIGN_CENTRE, "You win !!");
	al_draw_text(end2, al_map_rgb(222, 125, 44), 400, 400, ALLEGRO_ALIGN_CENTRE, buffer);
	al_draw_text(end3, al_map_rgb(222, 125, 44), 400, 500, ALLEGRO_ALIGN_CENTRE, "Press \"Enter\" to go to menu");
	al_draw_text(end3, al_map_rgb(222, 125, 44), 400, 600, ALLEGRO_ALIGN_CENTRE, "Press \"H\" to go to hall");
}
Scene scene_win_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.initialize = &init_win;
	scene.name = "Win";
	scene.draw = &draw_win;
	scene.on_key_down = &press;
	game_log("win scene created");
	return scene;
}
static void init(void) {
	game_over = false;
	game_main_Score = 0;
	// create map
	//basic_map = create_map(NULL);
	// [TODO]
	// Create map from .txt file and design your own map !!
	basic_map = create_map("Assets/test.txt");
	if (!basic_map) {
		game_abort("error on creating map");
	}	
	// create pacman
	pman = pacman_create();
	if (!pman) {
		game_abort("error on creating pacamn\n");
	}
	
	// allocate ghost memory
	// [HACKATHON 2-1]
	// TODO: Allocate dynamic memory for ghosts array.
	
	ghosts = (Ghost**)malloc(sizeof(Ghost*) * GHOST_NUM);
	
	if(!ghosts){
		game_log("We haven't create any ghosts!\n");
	}
	else {
		// [HACKATHON 2-2]
		// TODO: create a ghost.
		// Try to look the definition of ghost_create and figure out what should be placed here.
		for (int i = 0; i < GHOST_NUM; i++) {
			
			game_log("creating ghost %d\n", i);
			ghosts[i] = ghost_create(i); 
			if (!ghosts[i])
				game_abort("error creating ghost\n");
			
		}
	}
	GAME_TICK = 0;

	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick / sec
	if (!power_up_timer)
		game_abort("Error on create timer\n");
	return ;
}

static void b_init(void) {
	game_over = false;
	game_main_Score = 0;
	// create map
	//basic_map = create_map(NULL);
	// [TODO]
	// Create map from .txt file and design your own map !!
	basic_map = create_map("Assets/b.txt");
	if (!basic_map) {
		game_abort("error on creating map");
	}
	// create pacman
	pman = pacman_create();
	if (!pman) {
		game_abort("error on creating pacamn\n");
	}

	// allocate ghost memory
	// [HACKATHON 2-1]
	// TODO: Allocate dynamic memory for ghosts array.

	ghosts = (Ghost**)malloc(sizeof(Ghost*) * GHOST_NUM);

	if (!ghosts) {
		game_log("We haven't create any ghosts!\n");
	}
	else {
		// [HACKATHON 2-2]
		// TODO: create a ghost.
		// Try to look the definition of ghost_create and figure out what should be placed here.
		for (int i = 0; i < GHOST_NUM; i++) {

			game_log("creating ghost %d\n", i);
			ghosts[i] = ghost_create(i);
			if (!ghosts[i])
				game_abort("error creating ghost\n");

		}
	}
	GAME_TICK = 0;

	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick / sec
	if (!power_up_timer)
		game_abort("Error on create timer\n");
	return;
}
static void c_init(void) {
	game_over = false;
	game_main_Score = 0;
	// create map
	//basic_map = create_map(NULL);
	// [TODO]
	// Create map from .txt file and design your own map !!
	basic_map = create_map("Assets/c.txt");
	if (!basic_map) {
		game_abort("error on creating map");
	}
	// create pacman
	pman = pacman_create();
	if (!pman) {
		game_abort("error on creating pacamn\n");
	}

	// allocate ghost memory
	// [HACKATHON 2-1]
	// TODO: Allocate dynamic memory for ghosts array.

	ghosts = (Ghost**)malloc(sizeof(Ghost*) * GHOST_NUM);

	if (!ghosts) {
		game_log("We haven't create any ghosts!\n");
	}
	else {
		// [HACKATHON 2-2]
		// TODO: create a ghost.
		// Try to look the definition of ghost_create and figure out what should be placed here.
		for (int i = 0; i < GHOST_NUM; i++) {

			game_log("creating ghost %d\n", i);
			ghosts[i] = ghost_create(i);
			if (!ghosts[i])
				game_abort("error creating ghost\n");

		}
	}
	GAME_TICK = 0;

	render_init_screen();
	power_up_timer = al_create_timer(1.0f); // 1 tick / sec
	if (!power_up_timer)
		game_abort("Error on create timer\n");
	return;
}
static void init_hall() {
	stop_bgm(menuBGM);
	stop_bgm(playing);
	stop_bgm(playingb);
	stop_bgm(playingc);
	menuBGM = play_bgm(themeMusic, music_volume);
}
static ALLEGRO_SAMPLE_ID menuBGM;

static void step(void) {
	if (pman->objData.moveCD > 0)
		pman->objData.moveCD -= pman->speed;
	for (int i = 0; i < GHOST_NUM; i++) {
		// important for movement
		if (ghosts[i]->objData.moveCD > 0)
			ghosts[i]->objData.moveCD -= ghosts[i]->speed;
	}
}
static void checkItem(void) {
	int Grid_x = pman->objData.Coord.x, Grid_y = pman->objData.Coord.y;
	if (Grid_y >= basic_map->row_num - 1 || Grid_y <= 0 || Grid_x >= basic_map->col_num - 1 || Grid_x <= 0)
		return;
	// [HACKATHON 1-3]
	// TODO: check which item you are going to eat and use `pacman_eatItem` to deal with it.
	
	switch (basic_map->map[Grid_y][Grid_x])
	{
	case '.':
		pacman_eatItem(pman, '.');
		basic_map->beansCount--;
		break;
	case 'P':
		pacman_eatItem(pman, 'P');
		al_stop_timer(power_up_timer);
		al_set_timer_count(power_up_timer, 0);
		al_start_timer(power_up_timer);
		for (int i = 0; i < GHOST_NUM; i++) {
			ghost_toggle_FLEE(ghosts[i], true);
		}
		break;
	default:
		break;
	}
	
	// [HACKATHON 1-4]
	// erase the item you eat from map
	// be careful no erasing the wall block.
	
		basic_map->map[Grid_y][Grid_x] = '\0';
	
}
static void status_update(void) {
	if(al_get_timer_count(power_up_timer) >= power_up_duration - 2 && al_get_timer_count(power_up_timer) < power_up_duration) {
		for (int i = 0; i < GHOST_NUM; i++) {
			if (ghosts[i]->status == FLEE) {
				ghosts[i]->status = PREFREEDOM;
			}
		}
	}
	if (al_get_timer_count(power_up_timer) >= power_up_duration) {
		for (int i = 0; i < GHOST_NUM; i++) {
			ghost_toggle_FLEE(ghosts[i], false);
		}
		al_stop_timer(power_up_timer);
		al_set_timer_count(power_up_timer, 0);
	}

	for (int i = 0; i < GHOST_NUM; i++) {
		if (ghosts[i]->status == GO_IN)
			continue;
		// [TODO]
		// use `getDrawArea(..., GAME_TICK_CD)` and `RecAreaOverlap(..., GAME_TICK_CD)` functions to detect
		// if pacman and ghosts collide with each other.
		// And perform corresponding operations.
		// [NOTE]
		// You should have some branch here if you want to implement power bean mode.
		// Uncomment Following Code
		
		
		if (!cheat_mode && RecAreaOverlap(getDrawArea(pman->objData, GAME_TICK_CD), getDrawArea(ghosts[i]->objData, GAME_TICK_CD)))
		{
			if (ghosts[i]->status == FREEDOM) {
				game_log("collide with ghost\n");
				al_rest(1.0);
				pacman_die();
				game_over = true;
				break;
			}
			else if (ghosts[i]->status == FLEE || ghosts[i]->status == PREFREEDOM) {
				game_log("collide with ghost %d and eat it\n", i);
				ghost_collided(ghosts[i]);

			}
		}
		
	}
	
}

static void update(void) {
	if (basic_map->beansCount == 0) {
		game_change_scene(scene_win_create());
		
	}
	if (game_over) {
		
		al_start_timer(pman->death_anim_counter);

		if (al_get_timer_count(pman->death_anim_counter) > 150) {
			al_stop_timer(pman->death_anim_counter);
			al_set_timer_count(pman->death_anim_counter, 0);
			game_change_scene(scene_lose_create());
		}
		return;
	}

	step();
	checkItem();
	status_update();
	pacman_move(pman, basic_map);
	for (int i = 0; i < GHOST_NUM; i++) 
		ghosts[i]->move_script(ghosts[i], basic_map, pman);
}


static void update_b(void) {
	if (basic_map->beansCount == 0) {
		game_change_scene(scene_win_create());

	}
	if (game_over) {

		al_start_timer(pman->death_anim_counter);

		if (al_get_timer_count(pman->death_anim_counter) > 150) {
			al_stop_timer(pman->death_anim_counter);
			al_set_timer_count(pman->death_anim_counter, 0);
			game_change_scene(scene_lose_create());
		}
		return;
	}

	step();
	checkItem();
	status_update();
	pacman_move(pman, basic_map);
	for (int i = 0; i < GHOST_NUM; i++)
		ghosts[i]->move_script(ghosts[i], basic_map, pman);

}
static void update_c(void) {
	if (basic_map->beansCount == 0) {
		game_change_scene(scene_win_create());

	}
	if (game_over) {

		al_start_timer(pman->death_anim_counter);

		if (al_get_timer_count(pman->death_anim_counter) > 150) {
			al_stop_timer(pman->death_anim_counter);
			al_set_timer_count(pman->death_anim_counter, 0);
			game_change_scene(scene_lose_create());
		}
		return;
	}

	step();
	checkItem();
	status_update();
	pacman_move(pman, basic_map);
	for (int i = 0; i < GHOST_NUM; i++)
		ghosts[i]->move_script(ghosts[i], basic_map, pman);

}
static void draw(void) {

	al_clear_to_color(al_map_rgb(3, 38, 58));

	
	//	[TODO]
	//	Draw scoreboard, something your may need is sprinf();
	char buffer[100];
	int sum = 0;
	for (int i = 0; i < GHOST_NUM; i++) {
		
		sum += ghosts[i]->pp;
	}
	game_main_Score = ((basic_map->beansNum) - (basic_map->beansCount)) * 10 + sum * 200;
	sprintf_s(buffer, sizeof(buffer), "SCORE : %d", game_main_Score);
	al_draw_text(
		menuFont,
		al_map_rgb(250, 218, 141),
		45,
		20,
		ALLEGRO_ALIGN_LEFT,
		buffer
		);
	

	draw_map(basic_map);

	pacman_draw(pman);
	if (game_over) return;
	// no drawing below when game over
	for (int i = 0; i < GHOST_NUM; i++)
		ghost_draw(ghosts[i]);
	
	//debugging mode
	if (debug_mode) {
		draw_hitboxes();
	}

}

static void draw_b(void) {

	al_clear_to_color(al_map_rgb(3, 38, 58));


	//	[TODO]
	//	Draw scoreboard, something your may need is sprinf();
	char buffer[100];
	int sum = 0;
	for (int i = 0; i < GHOST_NUM; i++) {

		sum += ghosts[i]->pp;
	}
	game_main_Score = ((basic_map->beansNum) - (basic_map->beansCount)) * 10 + sum * 200;
	sprintf_s(buffer, sizeof(buffer), "SCORE : %d", game_main_Score);
	al_draw_text(
		menuFont,
		al_map_rgb(250, 218, 141),
		45,
		20,
		ALLEGRO_ALIGN_LEFT,
		buffer
	);


	draw_map(basic_map);

	pacman_draw(pman);
	if (game_over) return;
	// no drawing below when game over
	for (int i = 0; i < GHOST_NUM; i++)
		ghost_draw(ghosts[i]);

	//debugging mode
	if (debug_mode) {
		draw_hitboxes();
	}

}
static void draw_c(void) {

	al_clear_to_color(al_map_rgb(3, 38, 58));


	//	[TODO]
	//	Draw scoreboard, something your may need is sprinf();
	char buffer[100];
	int sum = 0;
	for (int i = 0; i < GHOST_NUM; i++) {

		sum += ghosts[i]->pp;
	}
	game_main_Score = ((basic_map->beansNum) - (basic_map->beansCount)) * 10 + sum * 200;
	sprintf_s(buffer, sizeof(buffer), "SCORE : %d", game_main_Score);
	al_draw_text(
		menuFont,
		al_map_rgb(250, 218, 141),
		45,
		20,
		ALLEGRO_ALIGN_LEFT,
		buffer
	);


	draw_map(basic_map);

	pacman_draw(pman);
	if (game_over) return;
	// no drawing below when game over
	for (int i = 0; i < GHOST_NUM; i++)
		ghost_draw(ghosts[i]);

	//debugging mode
	if (debug_mode) {
		draw_hitboxes();
	}

}
static void draw_hitboxes(void) {
	RecArea pmanHB = getDrawArea(pman->objData, GAME_TICK_CD);
	al_draw_rectangle(
		pmanHB.x, pmanHB.y,
		pmanHB.x + pmanHB.w, pmanHB.y + pmanHB.h,
		al_map_rgb_f(1.0, 0.0, 0.0), 2
	);

	for (int i = 0; i < GHOST_NUM; i++) {
		RecArea ghostHB = getDrawArea(ghosts[i]->objData, GAME_TICK_CD);
		al_draw_rectangle(
			ghostHB.x, ghostHB.y,
			ghostHB.x + ghostHB.w, ghostHB.y + ghostHB.h,
			al_map_rgb_f(1.0, 0.0, 0.0), 2
		);
	}

}

static void printinfo(void) {
	game_log("pacman:\n");
	game_log("coord: %d, %d\n", pman->objData.Coord.x, pman->objData.Coord.y);
	game_log("PreMove: %d\n", pman->objData.preMove);
	game_log("NextTryMove: %d\n", pman->objData.nextTryMove);
	game_log("Speed: %f\n", pman->speed);
}


static void destroy(void) {
	/*
		[TODO]
		free map array, Pacman and ghosts
	*/
	
}

static void on_key_down(int key_code) {
	switch (key_code)
	{
		// [HACKATHON 1-1]	
		// TODO: Use allegro pre-defined enum ALLEGRO_KEY_<KEYNAME> to controll pacman movement
		// we provided you a function `pacman_NextMove` to set the pacman's next move direction.
		
		case ALLEGRO_KEY_W:
			pacman_NextMove(pman, 1);
			break;
		case ALLEGRO_KEY_A:
			pacman_NextMove(pman, 2);
			break;
		case ALLEGRO_KEY_S:
			pacman_NextMove(pman, 4);
			break;
		case ALLEGRO_KEY_D:
			pacman_NextMove(pman, 3);
			break;
		case ALLEGRO_KEY_C:
			cheat_mode = !cheat_mode;
			if (cheat_mode)
				printf("cheat mode on\n");
			else 
				printf("cheat mode off\n");
			break;
		case ALLEGRO_KEY_G:
			debug_mode = !debug_mode;
			break;
		
	default:
		break;
	}

}

static void on_mouse_down(void) {
	// nothing here

}

static void render_init_screen(void) {
	al_clear_to_color(al_map_rgb(3, 38, 58));

	draw_map(basic_map);
	pacman_draw(pman);
	for (int i = 0; i < GHOST_NUM; i++) {
		ghost_draw(ghosts[i]);
	}

	al_draw_text(
		menuFont,
		al_map_rgb(250, 218, 141),
		400, 400,
		ALLEGRO_ALIGN_CENTER,
		"READY!"
	);

	al_flip_display();
	al_rest(2.0);

}
// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_main_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start";
	scene.initialize = &init;
	scene.update = &update;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Start scene created");
	return scene;
}
Scene scene_B_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start_B";
	scene.initialize = &b_init;
	scene.update = &update_b;
	scene.draw = &draw_b;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("B scene created");
	return scene;
}
Scene scene_C_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Start_C";
	scene.initialize = &c_init;
	scene.update = &update_c;
	scene.draw = &draw_c;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_down = &on_mouse_down;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("C scene created");
	return scene;
}
Scene scene_hall_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.initialize = &init_hall;
	scene.name = "Start_hall";
	scene.draw = &draw_hall;
	scene.on_key_down = &press_hall;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("hall scene created");
	return scene;
}
void draw_hall(void) {
	al_clear_to_color(al_map_rgb(3, 38, 58));
	al_draw_text(end1, al_map_rgb(250, 218, 141), 400, 200, ALLEGRO_ALIGN_CENTRE, "Choose your map !");
	al_draw_text(end4, al_map_rgb(222, 125, 44), 400, 400, ALLEGRO_ALIGN_CENTRE, "\"A\" : NTHU map");
	al_draw_text(end4, al_map_rgb(222, 125, 44), 400, 500, ALLEGRO_ALIGN_CENTRE, "\"B\" : LOOK map");
	al_draw_text(end4, al_map_rgb(222, 125, 44), 400, 600, ALLEGRO_ALIGN_CENTRE, "\"C\" : SQUARE map");
}