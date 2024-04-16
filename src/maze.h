#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define BUFFER_SIZE (20)
#define WINDOW_WIDTH (1280)
#define WINDOW_HEIGHT (720)
#define MAP_WIDTH (20)
#define FPS (60) /* FRAMES_PER_SECOND */
#define FTT (1000 / FPS) /* FRAME_TARGET_TIME */
#define PI (3.14159265f)
#define MOV_SPD (0.05) /* Player movement speed */
#define ROT_SPD (0.025) /* Player rotation speed */

/* 2D array of game map layout */
extern const int MAP[MAP_WIDTH * MAP_WIDTH];

/**
 * struct state_s - Defines program state
 *
 * @window: Pointer that holds all the rendered graphics
 * @render: Pointer that contains the rendered state
 * @quit: Boolean of running state
 *
 */

typedef struct state_s
{
	SDL_Window *window;
	SDL_Renderer *render;
	bool quit;
} State_t;

/**
 * struct sprite_s - Defines sprite
 *
 * @pos_x: sprite x-coordinate
 * @pos_y: sprite y-coordinate
 * @dir_x: sprite x-direction
 * @dir_y: sprite y-direction
 * @plane_x: sprite x-plane
 * @plane_y: sprite y-plane
 *
 * Description: struct declaration for sprite position,
 * direction and plane
 */

typedef struct sprite_s
{
	float pos_x, pos_y, dir_x, dir_y, plane_x, plane_y;
} Sprite_t;

/**
 * enum compass_s - Defines compass directions
 *
 * @NthSth: North South plane
 * @EstWst: East West plane
 *
 * Description: enum defition for map compass direction
 */

typedef enum compass_s
{
	NthSth, EstWst
} Compass_t;

void sdl_init(State_t *, Uint32 *);
void setup(State_t *, Sprite_t *, double *, double *);
void input_handler(State_t *, Sprite_t *);
void mouse_input(Sprite_t **, SDL_Event *);
void keyboard_input(State_t **, Sprite_t **, SDL_Event *, float *, float *);
void dda_raycaster(State_t *, Sprite_t *);
void setup_dda(Sprite_t **, int *, int *, int *, int *, int *, float *,
		float *, float *, float *, float *, float *);
void check_hit(float *, float *, float *, float *, int *, int *, int *,
		int *, Compass_t *);
void draw_walls(int *, int *, Compass_t *, SDL_Color *);
void sdl_quit(State_t *);

#endif /* MAZE_H */
