#include "display.h"

// Variables and global declaration
 SDL_Window* window = NULL;
 SDL_Renderer* renderer = NULL;
 SDL_Texture* color_buffer_texture = NULL;
 uint32_t* color_buffer = NULL;
 int WINDOW_WIDTH = 800;
 int  WINDOW_HEIGHT =  600;


void clear_color_buffer(uint32_t color){
	for(int y = 0; y < WINDOW_HEIGHT; y++){
		for(int x = 0; x < WINDOW_WIDTH; x++){
			color_buffer[calculate_color_index(x, y, WINDOW_WIDTH)] = color;
		}
	}

}
// we de allocate in reverse order
void destroy_window(void){
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
					color_buffer[calculate_color_index(x, y, WINDOW_WIDTH)] = 0xFF333333;
				}
			}
	}	
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

int calculate_color_index(int x, int y, int window_width) {
	return (window_width * y) + x; 	
}

void draw_rect(int x, int y, int width, int height, uint32_t color){
	for (int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			int current_x = x + i;
			int current_y = y + j;
			color_buffer[calculate_color_index(current_x, current_y, WINDOW_WIDTH)] = color;
		}
	}
	
}
