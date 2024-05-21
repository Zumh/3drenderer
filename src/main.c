#include "display.h"

bool is_running = false;

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
	destroy_window();
	return 0;
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




void render(void){
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	draw_grid();
	
	draw_rect(300, 200, 300, 150, 0xFFFF00FF);
	render_color_buffer();
	// copy this to sdl texture
	//clear_color_buffer(0xFFFFFF00);
	clear_color_buffer(0xFF000000);
	SDL_RenderPresent(renderer);

}



