
#include "ghost.h"
#include "pacman_obj.h"
#include "map.h"
/* Shared variables */
#define GO_OUT_TIME 256
extern uint32_t GAME_TICK_CD;
extern uint32_t GAME_TICK;
extern ALLEGRO_TIMER* game_tick_timer;
extern const int cage_grid_x, cage_grid_y;

/* Declare static function prototypes */
static void ghost_red_move_script_FREEDOM(Ghost* ghost, Map* M);
static void ghost_pink_move_script_FREEDOM(Ghost* ghost, Map* M);
static void ghost_orange_move_script_FREEDOM(Ghost* ghost, Map* M);
static void ghost_blue_move_script_FREEDOM(Ghost* ghost, Map* M);

static void ghost_red_move_script_BLOCKED(Ghost* ghost, Map* M);
static void ghost_pink_move_script_BLOCKED(Ghost* ghost, Map* M);
static void ghost_orange_move_script_BLOCKED(Ghost* ghost, Map* M);
static void ghost_blue_move_script_BLOCKED(Ghost* ghost, Map* M);

static void ghost_red_move_script_FREEDOM(Ghost* ghost, Map* M) {
	// [HACKATHON 2-4]
	// Uncomment the following code and finish pacman picking random direction.

	
	
	static Directions proba[400]; // possible movement
	int cnt = 0;
	static Directions chosen_direction = 0;
	/*UP = 1,
	LEFT = 2,
	RIGHT = 3,
	DOWN = 4,*/

	for (Directions i = 1; i <= 4; i++) {
		if (ghost_movable(ghost, M, i, true)) {
			if (i == chosen_direction) {
				for (int j = 0; j < 100; j++) {
					proba[cnt++] = i;
				}
			}
			if ((chosen_direction == 1 && i != 4) ||
				(chosen_direction == 2 && i != 3) ||
				(chosen_direction == 3 && i != 2) ||
				(chosen_direction == 4 && i != 1)) {
				for (int j = 0; j < 50; j++) {
					proba[cnt++] = i;
				}
			}
			proba[cnt++] = i;
		}
	}

	chosen_direction = proba[generateRandomNumber(0, cnt - 1)];
	ghost_NextMove(ghost, chosen_direction);
	
	
	// [TODO] (Not in Hackathon) 
	// Description:
	// For red(Blinky) ghost, we ask you to implement an random strategy ghost, 
	// which means moving in random direction.
	// But your random strategy have to designed carefully so that ghost won't walk back and forth.
	// (The code here DO perform walking back and forth.)
	
}
static void ghost_pink_move_script_FREEDOM(Ghost* ghost, Map* M) {
	static Directions proba[400]; // possible movement
	int cnt = 0;
	static Directions chosen_direction = 0;
	for (Directions i = 1; i <= 4; i++) {
		if (ghost_movable(ghost, M, i, true)) {
			if (i == chosen_direction) {
				for (int j = 0; j < 100; j++) {
					proba[cnt++] = i;
				}
			}
			if ((chosen_direction == 1 && i != 4) || (chosen_direction == 2 && i != 3) ||
				(chosen_direction == 3 && i != 2) || (chosen_direction == 4 && i != 1)) {
				for (int j = 0; j < 50; j++) {
					proba[cnt++] = i;
				}
			}
			proba[cnt++] = i;
		}
	}
	chosen_direction = proba[generateRandomNumber(0, cnt - 1)];
	ghost_NextMove(ghost, chosen_direction);
}
static void ghost_blue_move_script_FREEDOM(Ghost* ghost, Map* M) {
	static Directions proba[400]; // possible movement
	int cnt = 0;
	static Directions chosen_direction = 0;
	for (Directions i = 1; i <= 4; i++) {
		if (ghost_movable(ghost, M, i, true)) {
			if (i == chosen_direction) {
				for (int j = 0; j < 100; j++) {
					proba[cnt++] = i;
				}
			}
			if ((chosen_direction == 1 && i != 4) || (chosen_direction == 2 && i != 3) ||
				(chosen_direction == 3 && i != 2) || (chosen_direction == 4 && i != 1)) {
				for (int j = 0; j < 50; j++) {
					proba[cnt++] = i;
				}
			}
			proba[cnt++] = i;
		}
	}
	chosen_direction = proba[generateRandomNumber(0, cnt - 1)];
	ghost_NextMove(ghost, chosen_direction);
}
static void ghost_orange_move_script_FREEDOM(Ghost* ghost, Map* M) {
	static Directions proba[400]; // possible movement
	int cnt = 0;
	static Directions chosen_direction = 0;
	for (Directions i = 1; i <= 4; i++) {
		if (ghost_movable(ghost, M, i, true)) {
			if (i == chosen_direction) {
				for (int j = 0; j < 100; j++) {
					proba[cnt++] = i;
				}
			}
			if ((chosen_direction == 1 && i != 4) || (chosen_direction == 2 && i != 3) ||
				(chosen_direction == 3 && i != 2) || (chosen_direction == 4 && i != 1)) {
				for (int j = 0; j < 50; j++) {
					proba[cnt++] = i;
				}
			}
			proba[cnt++] = i;
		}
	}
	chosen_direction = proba[generateRandomNumber(0, cnt - 1)];
	ghost_NextMove(ghost, chosen_direction);
}

static void ghost_red_move_script_BLOCKED(Ghost* ghost, Map* M) {

	switch (ghost->objData.preMove)
	{
	case UP:
		if (ghost->objData.Coord.y == 10)
			ghost_NextMove(ghost, DOWN);
		else
			ghost_NextMove(ghost, UP);
		break;
	case DOWN:
		if (ghost->objData.Coord.y == 12)
			ghost_NextMove(ghost, UP);
		else
			ghost_NextMove(ghost, DOWN);
		break;
	default:
		ghost_NextMove(ghost, UP);
		break;
	}
}
static void ghost_pink_move_script_BLOCKED(Ghost* ghost, Map* M) {

	switch (ghost->objData.preMove)
	{
	case UP:
		if (ghost->objData.Coord.y == 10)
			ghost_NextMove(ghost, DOWN);
		else
			ghost_NextMove(ghost, UP);
		break;
	case DOWN:
		if (ghost->objData.Coord.y == 12)
			ghost_NextMove(ghost, UP);
		else
			ghost_NextMove(ghost, DOWN);
		break;
	default:
		ghost_NextMove(ghost, UP);
		break;
	}
}
static void ghost_blue_move_script_BLOCKED(Ghost* ghost, Map* M) {

	switch (ghost->objData.preMove)
	{
	case UP:
		if (ghost->objData.Coord.y == 10)
			ghost_NextMove(ghost, DOWN);
		else
			ghost_NextMove(ghost, UP);
		break;
	case DOWN:
		if (ghost->objData.Coord.y == 12)
			ghost_NextMove(ghost, UP);
		else
			ghost_NextMove(ghost, DOWN);
		break;
	default:
		ghost_NextMove(ghost, UP);
		break;
	}
}
static void ghost_orange_move_script_BLOCKED(Ghost* ghost, Map* M) {

	switch (ghost->objData.preMove)
	{
	case UP:
		if (ghost->objData.Coord.y == 10)
			ghost_NextMove(ghost, DOWN);
		else
			ghost_NextMove(ghost, UP);
		break;
	case DOWN:
		if (ghost->objData.Coord.y == 12)
			ghost_NextMove(ghost, UP);
		else
			ghost_NextMove(ghost, DOWN);
		break;
	default:
		ghost_NextMove(ghost, UP);
		break;
	}
}

void ghost_red_move_script(Ghost* ghost, Map* M, Pacman* pacman) {
	
	if (!movetime(ghost->speed))
		return;
		switch (ghost->status)
		{
		case BLOCKED:
			ghost_red_move_script_BLOCKED(ghost, M);
			if (!ghost->b_flag) {
				
				
				if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
					ghost->status = GO_OUT;
			}
			else {
				al_start_timer(ghost->blocked_timer);
				if (al_get_timer_count(ghost->blocked_timer) >= 2) {
					al_stop_timer(ghost->blocked_timer);
					al_set_timer_count(ghost->blocked_timer, 0);
					ghost->status = GO_OUT;
				}
			}
			break;
		case FREEDOM:
			ghost_red_move_script_FREEDOM(ghost, M);
			break;
		case GO_OUT:
			ghost->b_flag = 1;
			ghost_move_script_GO_OUT(ghost, M);	
			
			break;
		case GO_IN:
			ghost_move_script_GO_IN(ghost, M);
			if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
				ghost->status = BLOCKED;
				ghost->speed = 2;
			}
			break;
		case FLEE: 
			ghost_red_move_script_FLEE(ghost, M, pacman);
			break;
		case PREFREEDOM:
			ghost_red_move_script_FLEE(ghost, M, pacman);
			break;
		default:
			break;
		}

		if(ghost_movable(ghost, M, ghost->objData.nextTryMove, false)){
			ghost->objData.preMove = ghost->objData.nextTryMove;
			ghost->objData.nextTryMove = NONE;
		}
		else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
			return;

		switch (ghost->objData.preMove) {
		case RIGHT:
			ghost->objData.Coord.x += 1;
			break;
		case LEFT:
			ghost->objData.Coord.x -= 1;
			break;
		case UP:
			ghost->objData.Coord.y -= 1;
			break;
		case DOWN:
			ghost->objData.Coord.y += 1;
			break;
		default:
			break;
		}
		ghost->objData.facing = ghost->objData.preMove;
		ghost->objData.moveCD = GAME_TICK_CD;
}
void ghost_pink_move_script(Ghost* ghost, Map* M, Pacman* pacman) {

	if (!movetime(ghost->speed))
		return;
	switch (ghost->status)
	{
	case BLOCKED:
		ghost_pink_move_script_BLOCKED(ghost, M);
		if (!ghost->b_flag) {


			if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
				ghost->status = GO_OUT;
		}
		else {
			al_start_timer(ghost->blocked_timer);
			if (al_get_timer_count(ghost->blocked_timer) >= 2) {
				al_stop_timer(ghost->blocked_timer);
				al_set_timer_count(ghost->blocked_timer, 0);
				ghost->status = GO_OUT;
			}
		}
		break;
	case FREEDOM:
		ghost_pink_move_script_FREEDOM(ghost, M);
	case GO_OUT:
		ghost->b_flag = 1;
		ghost_move_script_GO_OUT(ghost, M);

		break;
	case GO_IN:
		ghost_move_script_GO_IN(ghost, M);
		if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
			ghost->status = BLOCKED;
			ghost->speed = 2;
		}
		break;
	case FLEE:
		ghost_pink_move_script_FLEE(ghost, M, pacman);
		break;
	case PREFREEDOM:
		ghost_pink_move_script_FLEE(ghost, M, pacman);
		break;
	default:
		break;
	}

	if (ghost_movable(ghost, M, ghost->objData.nextTryMove, false)) {
		ghost->objData.preMove = ghost->objData.nextTryMove;
		ghost->objData.nextTryMove = NONE;
	}
	else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
		return;

	switch (ghost->objData.preMove) {
	case RIGHT:
		ghost->objData.Coord.x += 1;
		break;
	case LEFT:
		ghost->objData.Coord.x -= 1;
		break;
	case UP:
		ghost->objData.Coord.y -= 1;
		break;
	case DOWN:
		ghost->objData.Coord.y += 1;
		break;
	default:
		break;
	}
	ghost->objData.facing = ghost->objData.preMove;
	ghost->objData.moveCD = GAME_TICK_CD;
}
void ghost_blue_move_script(Ghost* ghost, Map* M, Pacman* pacman) {

	if (!movetime(ghost->speed))
		return;
	switch (ghost->status)
	{
	case BLOCKED:
		ghost_blue_move_script_BLOCKED(ghost, M);
		if (!ghost->b_flag) {


			if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
				ghost->status = GO_OUT;
		}
		else {
			al_start_timer(ghost->blocked_timer);
			if (al_get_timer_count(ghost->blocked_timer) >= 2) {
				al_stop_timer(ghost->blocked_timer);
				al_set_timer_count(ghost->blocked_timer, 0);
				ghost->status = GO_OUT;
			}
		}
		break;
	case FREEDOM:
		ghost_blue_move_script_FREEDOM(ghost, M);
	case GO_OUT:
		ghost->b_flag = 1;
		ghost_move_script_GO_OUT(ghost, M);

		break;
	case GO_IN:
		ghost_move_script_GO_IN(ghost, M);
		if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
			ghost->status = BLOCKED;
			ghost->speed = 2;
		}
		break;
	case FLEE:
		ghost_blue_move_script_FLEE(ghost, M, pacman);
		break;
	case PREFREEDOM:
		ghost_blue_move_script_FLEE(ghost, M, pacman);
		break;
	default:
		break;
	}

	if (ghost_movable(ghost, M, ghost->objData.nextTryMove, false)) {
		ghost->objData.preMove = ghost->objData.nextTryMove;
		ghost->objData.nextTryMove = NONE;
	}
	else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
		return;

	switch (ghost->objData.preMove) {
	case RIGHT:
		ghost->objData.Coord.x += 1;
		break;
	case LEFT:
		ghost->objData.Coord.x -= 1;
		break;
	case UP:
		ghost->objData.Coord.y -= 1;
		break;
	case DOWN:
		ghost->objData.Coord.y += 1;
		break;
	default:
		break;
	}
	ghost->objData.facing = ghost->objData.preMove;
	ghost->objData.moveCD = GAME_TICK_CD;
}
void ghost_orange_move_script(Ghost* ghost, Map* M, Pacman* pacman) {

	if (!movetime(ghost->speed))
		return;
	switch (ghost->status)
	{
	case BLOCKED:
		ghost_orange_move_script_BLOCKED(ghost, M);
		if (!ghost->b_flag) {


			if (al_get_timer_count(game_tick_timer) > GO_OUT_TIME)
				ghost->status = GO_OUT;
		}
		else {
			al_start_timer(ghost->blocked_timer);
			if (al_get_timer_count(ghost->blocked_timer) >= 2) {
				al_stop_timer(ghost->blocked_timer);
				al_set_timer_count(ghost->blocked_timer, 0);
				ghost->status = GO_OUT;
			}
		}
		break;
	case FREEDOM:
		ghost_orange_move_script_FREEDOM(ghost, M);
	case GO_OUT:
		ghost->b_flag = 1;
		ghost_move_script_GO_OUT(ghost, M);

		break;
	case GO_IN:
		ghost_move_script_GO_IN(ghost, M);
		if (M->map[ghost->objData.Coord.y][ghost->objData.Coord.x] == 'B') {
			ghost->status = BLOCKED;
			ghost->speed = 2;
		}
		break;
	case FLEE:
		ghost_orange_move_script_FLEE(ghost, M, pacman);
		break;
	case PREFREEDOM:
		ghost_orange_move_script_FLEE(ghost, M, pacman);
		break;
	default:
		break;
	}

	if (ghost_movable(ghost, M, ghost->objData.nextTryMove, false)) {
		ghost->objData.preMove = ghost->objData.nextTryMove;
		ghost->objData.nextTryMove = NONE;
	}
	else if (!ghost_movable(ghost, M, ghost->objData.preMove, false))
		return;

	switch (ghost->objData.preMove) {
	case RIGHT:
		ghost->objData.Coord.x += 1;
		break;
	case LEFT:
		ghost->objData.Coord.x -= 1;
		break;
	case UP:
		ghost->objData.Coord.y -= 1;
		break;
	case DOWN:
		ghost->objData.Coord.y += 1;
		break;
	default:
		break;
	}
	ghost->objData.facing = ghost->objData.preMove;
	ghost->objData.moveCD = GAME_TICK_CD;
}
