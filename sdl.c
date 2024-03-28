#include "maze.h"

/**
 * sdl_init - Function that intializes SDL Library
 *
 * @window: Struct that holds all the display graphics
 * @render: Struct that contains a rendering state
 * @render_flags: Unsigned Integer
 *
 * Return: Always VOID!
 */

void sdl_init(SDL_Window *window, SDL_Renderer *render, Uint32 *render_flags)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		fprintf(stderr, "SDL initialization error: %s\n!", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	printf("SDL Initialization SUCCESSFUL!...\n");

	/* Create SDL Window */
	window = SDL_CreateWindow("Maze Game Project", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (!window)
	{
		fprintf(stderr, "SDL window creation error: %s\n!", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	printf("SDL Window Creation SUCCESSFUL!...\n");

	/* Render to SDL Window */
	*render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	render = SDL_CreateRenderer(window, -1, *render_flags);

	if (!render)
	{
		fprintf(stderr, "SDL render to window error: %s\n!", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	printf("SDL Render to created Window SUCCESSFUL!...\n");
}

/**
 * sdl_quit - Function that cleans up all initialized subsystems
 *
 * @render: Struct that contains a rendering state
 * @window: Struct that holds all the display graphics
 *
 * Return: Always VOID!
 */

void sdl_quit(SDL_Renderer *render, SDL_Window *window)
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();

	printf("SDL Quit SUCCESSFUL!...\n");
}
