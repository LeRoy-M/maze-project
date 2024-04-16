#include "maze.h"

/**
 * sdl_init - Function that intializes SDL Library
 *
 * @state: Struct that holds the window, render and quit state
 * @render_flags: Unsigned integer for rendering option
 *
 * Return: Always VOID!
 */

void sdl_init(State_t *state, Uint32 *render_flags)
{
	/* Initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		fprintf(stderr, "SDL initialization error: %s\n!", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	printf("SDL Initialization SUCCESSFUL!...\n");

	/* Create SDL Window */
	state->window = SDL_CreateWindow("Maze Game Project", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	if (!state->window)
	{
		fprintf(stderr, "SDL window creation error: %s\n!", SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	printf("SDL Window Creation SUCCESSFUL!...\n");

	/* Render to SDL Window */
	*render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	state->render = SDL_CreateRenderer(state->window, -1, *render_flags);

	if (!state->render)
	{
		fprintf(stderr, "SDL render to window error: %s\n!", SDL_GetError());
		SDL_DestroyWindow(state->window);
		SDL_Quit();
		exit(EXIT_FAILURE);
	}
	printf("SDL Render to created window SUCCESSFUL!...\n");

	/* Set mouse to be "hijacked" by game window */
	SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1");
	SDL_SetRelativeMouseMode(true);
	printf("Initialization Completed!...\n");
}

/**
 * sdl_quit - Function that cleans up all initialized subsystems
 *
 * @state: Struct that holds the window, render and quit state
 *
 * Return: Always VOID!
 */

void sdl_quit(State_t *state)
{
	/* Destroy Renderer */
	SDL_DestroyRenderer(state->render);

	/* Destroy Window */
	SDL_DestroyWindow(state->window);

	/* Quit SDL */
	SDL_Quit();

	printf("SDL Quit SUCCESSFUL!...\nGoodbye!\n");
}
