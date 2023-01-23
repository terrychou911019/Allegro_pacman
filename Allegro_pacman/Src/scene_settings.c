// [HACKATHON 3-9]
// TODO: Create scene_settings.h and scene_settings.c.
// No need to do anything for this part. We've already done it for
// you, so this 2 files is like the default scene template.
#include "scene_settings.h"
#include "shared.h"
#include "scene_menu_object.h"
#include "scene_menu.h"
// Variables and functions with 'static' prefix at the top level of a
// source file is only accessible in that file ("file scope", also
// known as "internal linkage"). If other files has the same variable
// name, they'll be different variables.

/* Define your static vars / function prototypes below. */

// TODO: More variables and functions that will only be accessed
// inside this scene. They should all have the 'static' prefix.
static Button increase_m, decrease_m, increase_e, decrease_e;
static ALLEGRO_SAMPLE_ID menuBGM;

static void draw(void) {
	al_clear_to_color(al_map_rgb(3, 38, 58));
	char m_volume[100];
	sprintf_s(m_volume, sizeof(m_volume), "Music Volume : %2.f %%", music_volume < 0.1 ? (double)0 : music_volume * 100);
	al_draw_text(volume1, al_map_rgb(250, 218, 141), 400, 300, ALLEGRO_ALIGN_CENTRE, m_volume);
	char e_volume[100];
	sprintf_s(e_volume, sizeof(e_volume), "Effect Volume : %2.f %%", effect_volume < 0.1 ? (double)0 : effect_volume * 100);
	al_draw_text(volume1, al_map_rgb(250, 218, 141), 400, 400, ALLEGRO_ALIGN_CENTRE, e_volume);
	drawButton(increase_m);
	drawButton(decrease_m);
	drawButton(increase_e);
	drawButton(decrease_e);
	al_draw_text(volume1, al_map_rgb(222, 125, 44), 400, 600, ALLEGRO_ALIGN_CENTRE, "Press \"ESC\" to quit");
}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	increase_m.hovered = buttonHover(increase_m, mouse_x, mouse_y);
	decrease_m.hovered = buttonHover(decrease_m, mouse_x, mouse_y);
	increase_e.hovered = buttonHover(increase_e, mouse_x, mouse_y);
	decrease_e.hovered = buttonHover(decrease_e, mouse_x, mouse_y);
}

static void on_mouse_down() {
	if (increase_m.hovered && music_volume < 1) {
		music_volume += 0.1;
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic, music_volume);
	}
	if (decrease_m.hovered && music_volume > 0) {
		music_volume -= 0.1;
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic, music_volume);
	}
	if (increase_e.hovered && effect_volume < 1) {
		effect_volume += 0.1;
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic, music_volume);
	}
	if (decrease_e.hovered && effect_volume > 0) {
		effect_volume -= 0.1;
		stop_bgm(menuBGM);
		menuBGM = play_bgm(themeMusic, music_volume);
	}
}

static void destroy() {
	al_destroy_bitmap(increase_m.default_img);
	al_destroy_bitmap(increase_m.hovered_img);
	al_destroy_bitmap(decrease_m.default_img);
	al_destroy_bitmap(decrease_m.hovered_img);
	al_destroy_bitmap(increase_e.default_img);
	al_destroy_bitmap(increase_e.hovered_img);
	al_destroy_bitmap(decrease_e.default_img);
	al_destroy_bitmap(decrease_e.hovered_img);
}
void init(void) {
	increase_m = button_create(660, 290, 50, 50, "Assets/increase1.png", "Assets/increase2.png");
	decrease_m = button_create(90, 290, 50, 50, "Assets/decrease1.png", "Assets/decrease2.png");
	increase_e = button_create(660, 390, 50, 50, "Assets/increase1.png", "Assets/increase2.png");
	decrease_e = button_create(90, 390, 50, 50, "Assets/decrease1.png", "Assets/decrease2.png");
	stop_bgm(menuBGM);
	menuBGM = play_bgm(themeMusic, music_volume);
}

void press2(int keycode) {
	if (keycode == ALLEGRO_KEY_ESCAPE) {
		stop_bgm(menuBGM);
		game_change_scene(scene_menu_create());
	}
}
// The only function that is shared across files.
Scene scene_settings_create(void) {
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &press2;
	scene.on_mouse_down = &on_mouse_down;
	scene.on_mouse_move = &on_mouse_move;
	// TODO: Register more event callback functions such as keyboard, mouse, ...
	game_log("Settings scene created");
	return scene;
}

