#include "maze.h"

const int MAP[MAP_WIDTH * MAP_WIDTH] =
{
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
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
	int quit, mouse_pos_x, mouse_pos_y;
	float mov_spd, rot_spd, old_dir_x, old_plane_x;
	double crnt_time, prev_time;
	double delta_pos_x, delta_pos_y;
	SDL_Window *window;
	SDL_Renderer *render;
	Uint32 render_flags;
	SDL_Event event;
	sprite_t player;

	/* Initialize SDL library */
	window = NULL;
	render = NULL;
	sdl_init(window, render, &render_flags);

	/* SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1"); */
	/* SDL_SetRelativeMouseMode(true); */

	/* Setup game player position */
	quit = 0;
	player.pos_x = 5.0;
	player.pos_y = 5.0;
	player.dir_x = -1.0;
	player.dir_y = player.plane_x = crnt_time = prev_time = 0;
	player.plane_y = 0.66;
	mov_spd = 0.1;
	rot_spd = 0.025;

	/* Game Loop */
	while (!quit)
	{
		mouse_pos_x = mouse_pos_y = 0;
		delta_pos_x = player.pos_x * mov_spd;
		delta_pos_y = player.pos_y * mov_spd;

		/* process_input()*/
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case (SDL_QUIT):
					quit = 1;
					break;
				case (SDL_MOUSEMOTION):
					mouse_pos_x = event.motion.xrel;
					if (mouse_pos_x != 0)
					{
						old_dir_x = player.pos_x;
						player.dir_x = player.dir_x * cosf(rot_spd) - player.dir_y * sinf(rot_spd);
						player.dir_y = old_dir_x * sinf(rot_spd) + player.dir_y * cosf(rot_spd);

						old_plane_x = player.plane_x;
						player.plane_x = player.plane_x * cosf(rot_spd) - player.plane_y * sinf(rot_spd);
						player.plane_y = old_plane_x * sinf(rot_spd) + player.plane_y * cosf(rot_spd);
					}
					break;
				case (SDL_KEYDOWN):
					/* Handle player movement */
					switch ((event).key.keysym.sym)
					{
						case (SDL_SCANCODE_W):
						case (SDL_SCANCODE_UP):
							if (MAP[(int)(player.pos_y * MAP_WIDTH + (player.pos_x + delta_pos_x))] == 0)
									player.pos_x += delta_pos_x;
							if (MAP[(int)((player.pos_y + delta_pos_y) * MAP_WIDTH + player.pos_x)] == 0)
									player.pos_y += delta_pos_y;
							break;
						case (SDL_SCANCODE_A):
						case (SDL_SCANCODE_LEFT):
							if (MAP[(int)(player.pos_y * MAP_WIDTH + (player.pos_x - delta_pos_y))] == 0)
									player.pos_x -= delta_pos_y;
							if (MAP[(int)((player.pos_y - -(delta_pos_x)) * MAP_WIDTH + player.pos_x)] == 0)
									player.pos_y -= -(delta_pos_x);
							break;
						case (SDL_SCANCODE_D):
						case (SDL_SCANCODE_RIGHT):
							if (MAP[(int)(player.pos_y * MAP_WIDTH + (player.pos_x - -(delta_pos_y)))] == 0)
									player.pos_x -= -(delta_pos_y);
							if (MAP[(int)((player.pos_y - delta_pos_x) * MAP_WIDTH + player.pos_x)] == 0)
									player.pos_y -= delta_pos_x;
							break;
						case (SDL_SCANCODE_S):
						case (SDL_SCANCODE_DOWN):
							if (MAP[(int)(player.pos_y * MAP_WIDTH + (player.pos_x - delta_pos_x))] == 0)
									player.pos_x -= delta_pos_x;
							if (MAP[(int)((player.pos_y - delta_pos_y) * MAP_WIDTH + player.pos_x)] == 0)
									player.pos_y -= delta_pos_y;
							break;
					}
					break;
			}
		}

		/* Draw to render */
		renderer(render, &player);
	}

	/* Clean up all initialized subsystems */
	sdl_quit(render, window);

	exit(EXIT_SUCCESS);
}

/**
 * process_input - Function that handles user input
 *
 * @quit: Keyboard input event to exit game
 * @player: Struct containing player size and position
 *
 * Return: Always VOID!
 */

/*void process_input(int *quit, sprite_t *player)*/
/*{*/
	/*SDL_Event event;*/

	/* TODO */
/*}*/

/**
 * renderer - Function that renders to buffer
 *
 * @render: Struct that contains a rendering state
 * @player: Struct containing player size and position
 *
 * Return: Always VOID!
 */

void renderer(SDL_Renderer *render, sprite_t *player)
{
	SDL_Renderer *rnd_ptr;
	sprite_t *ply_ptr;

	rnd_ptr = render;
	ply_ptr = player;

	/* Set buffer colour */
	SDL_SetRenderDrawColor(render, 0, 0, 30, 255);

	/* Clear the buffer */
	SDL_RenderClear(render);

	/* DDA Raycaster Algorithm */
	dda_raycaster(&rnd_ptr, &ply_ptr);

	/* Show front buffer */
	SDL_RenderPresent(render);
}
