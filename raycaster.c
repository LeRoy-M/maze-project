#include "maze.h"

/**
 * dda_raycaster - Function containing raycasting algorithm
 *
 * @render: Struct that contains a rendering state
 * @player: Struct containing player size and position
 *
 * Return: Always VOID!
 */

void dda_raycaster(SDL_Renderer **render, sprite_t **player)
{
	int x, hit, map_x, map_y, step_x, step_y;
	int line_height, draw_start, draw_end;
	float camera, ray_dir_x, ray_dir_y, side_dist_x, side_dist_y;
	float delta_dist_x, delta_dist_y, perp_wall_dist;
	SDL_Color colour;
	compass_t side;

	for (x = 0; x < WINDOW_WIDTH; x++)
	{
		camera = 2 * x / (float)MAP_WIDTH - 1;
		ray_dir_x = (*player)->dir_x + (*player)->plane_x * camera;
		ray_dir_y = (*player)->dir_y + (*player)->plane_y * camera;
		map_x = (int)(*player)->pos_x;
		map_y = (int)(*player)->pos_y;
		side_dist_x = side_dist_y = 0;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabsf(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabsf(1 / ray_dir_y);
		hit = 0;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = ((*player)->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - (*player)->pos_x) * delta_dist_x;
		}

		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = ((*player)->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - (*player)->pos_y) * delta_dist_y;
		}

		check_hit(&hit, &side_dist_x, &side_dist_y, &delta_dist_x,
				&delta_dist_y, &map_x, &map_y, &step_x,
				&step_y, &side);

		if (side == EstWst)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else if (side == NthSth)
			perp_wall_dist = side_dist_y - delta_dist_y;

		line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
		draw_start = (-(line_height) / 2) + (WINDOW_HEIGHT / 2);
		if (draw_start < 0)
			draw_start = 0;

		draw_end = (line_height / 2) + (WINDOW_HEIGHT / 2);
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT;

		draw_walls(&map_x, &map_y, &side, &colour);

		/* Set rectangle colour */
		SDL_SetRenderDrawColor(*render, colour.r, colour.g, colour.b, colour.a);
		SDL_RenderDrawLine(*render, x, draw_start, x, draw_end);
	}
	printf("dda_raycaster Done SUCCESSFUL!...\n");
}

/**
 * check_hit - Function checking for collision with a wall
 *
 * @hit: Contact with wall
 * @side_dist_x: Current position to next x-side
 * @side_dist_y: Current position to next y-side
 * @delta_dist_x: Change in x-distance
 * @delta_dist_y: Change in y-distance
 * @map_x: x-coordinate of map
 * @map_y: y-coordinate of map
 * @step_x: Direction to step in x-direction
 * @step_y: Direction to step in y-direction
 * @side: Direction of wall hit
 *
 * Return: Always VOID!
 */

void check_hit(int *hit, float *side_dist_x, float *side_dist_y,
		float *delta_dist_x, float *delta_dist_y, int *map_x,
		int *map_y, int *step_x, int *step_y, compass_t *side)
{
	while (*hit)
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += *delta_dist_x;
			*map_x += *step_x;
			*side = EstWst;
		}
		else
		{
			*side_dist_y += *delta_dist_y;
			*map_y += *step_y;
			*side = NthSth;
		}

		if (MAP[(int)(*map_y * MAP_WIDTH + *map_x)] > 0)
			*hit = 1;
	}
}

/**
 * draw_walls - Function that paints the walls
 *
 * @map_x: x-coordinate of map
 * @map_y: y-coordinate of map
 * @side: Direction of wall hit
 * @colour: Colour struct to paint walls
 *
 * Return: Always VOID!
 */

void draw_walls(int *map_x, int *map_y, compass_t *side, SDL_Color *colour)
{
	switch (MAP[(int)(*map_y * MAP_WIDTH + *map_x)])
	{
		case (1):
			colour->r = 255;
			colour->g = 0;
			colour->b = 0;
			colour->a = 255;
			break;
		case (2):
			colour->r = 0;
			colour->g = 255;
			colour->b = 0;
			colour->a = 255;
			break;
		case (3):
			colour->r = 0;
			colour->g = 0;
			colour->b = 255;
			colour->a = 255;
			break;
		case (4):
			colour->r = 0;
			colour->g = 0;
			colour->b = 0;
			colour->a = 255;
			break;
		default:
			colour->r = 234;
			colour->g = 170;
			colour->b = 0;
			colour->a = 255;
			break;
	}

	if (*side == NthSth)
	{
		colour->r /= 2;
		colour->g /= 2;
		colour->b /= 2;
	}
}
