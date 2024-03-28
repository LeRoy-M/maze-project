#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define BUFFER_SIZE (20)
#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define MAP_WIDTH (20)
#define FPS (60) /* FRAMES_PER_SECOND */
#define FTT (1000 / FPS) /* FRAME_TARGET_TIME */
#define SPRITE_POS_X (50)
#define SPRITE_POS_Y (50)
#define PI (3.14159265f)

/* 2D array of game map layout */
extern const int MAP[MAP_WIDTH * MAP_WIDTH];

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
} sprite_t;

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
} compass_t;

void sdl_init(SDL_Window *, SDL_Renderer *, Uint32 *);
/*void process_input(int *, sprite_t *);*/
void renderer(SDL_Renderer *, sprite_t *);
void dda_raycaster(SDL_Renderer **, sprite_t **);
void check_hit(int *, float *, float *, float *, float *, int *, int *, int *, int *, compass_t *);
void draw_walls(int *, int *, compass_t *, SDL_Color *);
/*void dda_setup(int *, int *, int *, int *, int *, double *, double *, double *, double *, double *, double *, double *, double **, double **, sprite_t **);*/
/*void setup(sprite_t *, int *, double *, double *, double *, double *);*/
/*void update(sprite_t *, int *);*/
/*void move_player(SDL_Event *, sprite_t **, double **, double **, double **);*/
void sdl_quit(SDL_Renderer *, SDL_Window *);

#endif /* MAZE_H */
