#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Rendereer* renderer = NULL;
bool isRunning = false;

bool initialize_window(void);

int main(void){
	/* TODO: Create a SDL a window */

	
	isRunning = initialize_window();
	return 0;
}


bool initialize_window(void){
	// mouse, keyboard
	// test permission to access input signal from keyboard and mouse
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	// TODO: Create  SDL window
	int width = 800; 
	int height = 600;	
	// no window border = NULL
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_BORDERLESS
	);

	// check if window is successfully created or not
	if (!window){
		fprintf(stderr, "Error couldn't create SDL window\n");
		return false;
	}

	// TODO: Create a SDL renderer
	// renderer of 'window' object
	// -1 get a default graphics driver
	// 0 i don't have any special flags
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer){
		fprintf(stderr, "Error couldn't create SDL renderer.\n");
		return false;
	}
	
	return true;
}
