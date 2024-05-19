#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;
uint32_t* color_buffer = NULL;

int WINDOW_WIDTH = 800;
int  WINDOW_HEIGHT =  600;


bool initialize_window(void);
void setup(void);
void process_input(void);
void update(void);
void render(void);

void clear_color_buffer(uint32_t color);
void destroy_window(void);
void render_color_buffer();

void draw_grid(void);
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
	destroy_window();
	return 0;
}

// we de allocate in reverse order
void destroy_window(void){
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void setup(void){
	// Allocate the required memory in bytes to hold the color buffer
	color_buffer = (uint32_t*) malloc( WINDOW_WIDTH * WINDOW_HEIGHT * sizeof(uint32_t));
	// Creating a SDL texture that is used to display
	color_buffer_texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		WINDOW_WIDTH,
		WINDOW_HEIGHT
	);

	
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

void clear_color_buffer(uint32_t color){
	for(int y = 0; y < WINDOW_HEIGHT; y++){
		for(int x = 0; x < WINDOW_WIDTH; x++){
			color_buffer[(WINDOW_WIDTH * y) + x] = color;
		}
	}

}

void draw_grid(void){
	// grid drawing
	/*
	for(int y= 0; y < WINDOW_HEIGHT; y++){
		for(int x = 0; x < WINDOW_WIDTH; x++){
			if(x % 10 == 0 || y % 10 == 0){
				color_buffer[(WINDOW_WIDTH * y) + x] = 0xFF333333;
			}
		}
	}	
	*/
	// dotted grid
	for(int y= 0; y < WINDOW_HEIGHT; y += 10){
			for(int x = 0; x < WINDOW_WIDTH; x += 10){
				if(x % 10 == 0 || y % 10 == 0){
					color_buffer[(WINDOW_WIDTH * y) + x] = 0xFF333333;
				}
			}
	}	
}

void render(void){
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	draw_grid();
	render_color_buffer();
	// copy this to sdl texture
	//clear_color_buffer(0xFFFFFF00);
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);

}


bool initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
	}
	// Use SDL to query wat is the fullscreen max. width and height
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);

	// fake full screen intialization
	WINDOW_WIDTH = display_mode.w;
	WINDOW_HEIGHT = display_mode.h;

	// Create a SDL Window
	window = SDL_CreateWindow(

		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
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
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	return true;
}

// Renders the color buffer array in a texture and displays it
void render_color_buffer(void){
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(WINDOW_WIDTH * sizeof(uint32_t))
	
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}
