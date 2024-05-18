#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool initialize_window(void);
void setup(void);
void process_input(void);
void update(void);
void render(void);

int main(void){

	printf("Hello, world!\n");
	// TODO: Crate a SDL window
	is_running = initialize_window();

	setup();

	while(is_running){
		process_input();
		update();
		render();
	}	
	return 0;
}


void setup(void){
	
}
void process_input(void){

	// start reading event from keyboard
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type){
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE){
				is_running = false;
			}
			break;
	}
}

void update(void){

}

void render(void){
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	//...
	SDL_RenderPresent(renderer);

}


bool initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
	}
	// Create a SDL Window
	window = SDL_CreateWindow(

		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);

	if (!window){
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	// Create a SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){
		fprintf(stderr, "Error creating SDL renderer.\n");	
		return false;
	}
	return true;
}
