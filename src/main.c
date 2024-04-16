#include "maze.h"

/* Game Map */
const int MAP[MAP_WIDTH * MAP_WIDTH] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

/**
 * main - Entry/ Exit Point
 *
 * Return: Always SUCCESS!
 */

int main(void)
{
	double crnt_time, prev_time;
	State_t state;
	Uint32 render_flags;
	Sprite_t player;

	/* Setup some game variables */
	setup(&state, &player, &crnt_time, &prev_time);

	/* Initialize SDL library */
	sdl_init(&state, &render_flags);

	/* Game Loop */
	while (!state.quit)
	{
		/* Handle input */
		input_handler(&state, &player);

		/* Set buffer colour */
		SDL_SetRenderDrawColor(state.render, 0x12, 0x2C, 0x34, 0xFF);

		/* Clear the buffer */
		SDL_RenderClear(state.render);

		/* DDA Raycaster Algorithm */
		dda_raycaster(&state, &player);

		/* Show front buffer */
		SDL_RenderPresent(state.render);
	}

	/* Clean up all initialized subsystems */
	sdl_quit(&state);

	exit(EXIT_SUCCESS);
}

/**
 * setup - Function that initializes a few of the program variables
 *
 * @state: Struct that holds the window, render and quit state
 * @player: The player struct
 * @crnt_time: Current time
 * @prev_time: Previous time
 *
 * Return: Always VOID
 */

void setup(State_t *state, Sprite_t *player, double *crnt_time,
		double *prev_time)
{
	/* Game state initialized */
	state->window = NULL;
	state->render = NULL;
	state->quit = false;

	/* Sprite and timing variables initialized */
	player->pos_x = 17.0;
	player->pos_y = 17.0;
	player->dir_x = -1.0;
	player->dir_y = player->plane_x = *crnt_time = *prev_time = 0;
	player->plane_y = 0.66;
}

/**
 * input_handler - Function that handles user input
 *
 * @state: Struct that holds the window, render and quit state
 * @player: The player struct
 *
 * Return: Always VOID!
 */

void input_handler(State_t *state, Sprite_t *player)
{
	float delta_pos_x, delta_pos_y;
	SDL_Event event; /* event struct */

	/* Change in player x & y positions */
	delta_pos_x = player->pos_x * MOV_SPD;
	delta_pos_y = player->pos_y * MOV_SPD;

	/* Input Loop */
	while (SDL_PollEvent(&event))
	{
		/* Handle mouse movement */
		switch (event.type)
		{
			case (SDL_QUIT):
				state->quit = true;
				break;
			case (SDL_MOUSEMOTION):
				/* Mouse handler function */
				mouse_input(&player, &event);
				break;
		}

		/* Handle keyboard input */
		switch (event.type)
		{
			case (SDL_KEYDOWN):
				/* Keyboard handler function */
				keyboard_input(&state, &player, &event, &delta_pos_x, &delta_pos_y);
				break;
		}
	}
}

/**
 * mouse_input - Function that handles user mouse input
 *
 * @player: The player struct
 * @event: General event struct
 *
 * Return: Always VOID!
 */

void mouse_input(Sprite_t **player, SDL_Event *event)
{
	int mouse_pos_x, mouse_pos_y;
	float r_speed, old_dir_x, old_plane_x;

	/* Mouse position */
	mouse_pos_x = mouse_pos_y = 0;
	mouse_pos_x = event->motion.xrel;
	mouse_pos_y = event->motion.yrel;

	if (mouse_pos_x != 0)
	{
		r_speed = (ROT_SPD) * (mouse_pos_x * -(0.1)); /* rotation speed */
		old_dir_x = (*player)->dir_x; /* previous x-direction */
		(*player)->dir_x = (*player)->dir_x * cosf(r_speed) - (*player)->dir_y *
			sinf(r_speed);
		(*player)->dir_y = old_dir_x * sinf(r_speed) + (*player)->dir_y *
			cosf(r_speed);

		old_plane_x = (*player)->plane_x; /* previous x-plane */
		(*player)->plane_x = (*player)->plane_x * cosf(r_speed) -
			(*player)->plane_y * sinf(r_speed);
		(*player)->plane_y = old_plane_x * sinf(r_speed) + (*player)->plane_y *
			cosf(r_speed);
	}
}

/**
 * keyboard_input - Function that handles user keyboard input
 *
 * @state: Struct that holds the window, render and quit state
 * @player: The player struct
 * @event: General event struct
 * @delta_pos_x: The change in x position
 * @delta_pos_y: The change in y position
 *
 * Return: Always VOID!
 */

void keyboard_input(State_t **state, Sprite_t **player, SDL_Event *event,
		float *delta_pos_x, float *delta_pos_y)
{
	/* Find key pressed and move player */
	switch (event->key.keysym.sym)
	{
		case (SDLK_ESCAPE): /* 'Esc' key pressed */
		(*state)->quit = true;
			break;
		case (SDLK_w): /* 'W' key pressed */
			if (MAP[(int)((*player)->pos_y * MAP_WIDTH + ((*player)->pos_x +
							*delta_pos_x))] == 0)
				(*player)->pos_x += *delta_pos_x;
			if (MAP[(int)(((*player)->pos_y + *delta_pos_y) * MAP_WIDTH +
						(*player)->pos_x)] == 0)
				(*player)->pos_y += *delta_pos_y;
			break;
		case (SDLK_a): /* 'A' key pressed */
			if (MAP[(int)((*player)->pos_y * MAP_WIDTH + ((*player)->pos_x -
							*delta_pos_y))] == 0)
				(*player)->pos_x -= *delta_pos_y;
			if (MAP[(int)(((*player)->pos_y - -(*delta_pos_x)) * MAP_WIDTH +
						(*player)->pos_x)] == 0)
				(*player)->pos_y -= -(*delta_pos_x);
			break;
		case (SDLK_d): /* 'D' key pressed */
			if (MAP[(int)((*player)->pos_y * MAP_WIDTH + ((*player)->pos_x -
							-(*delta_pos_y)))] == 0)
				(*player)->pos_x -= -(*delta_pos_y);
			if (MAP[(int)(((*player)->pos_y - *delta_pos_x) * MAP_WIDTH +
						(*player)->pos_x)] == 0)
				(*player)->pos_y -= *delta_pos_x;
			break;
		case (SDLK_s): /* 'S' key pressed */
			if (MAP[(int)((*player)->pos_y * MAP_WIDTH + ((*player)->pos_x -
							*delta_pos_x))] == 0)
				(*player)->pos_x -= *delta_pos_x;
			if (MAP[(int)(((*player)->pos_y - *delta_pos_y) * MAP_WIDTH +
						(*player)->pos_x)] == 0)
				(*player)->pos_y -= *delta_pos_y;
			break;
	}
}
