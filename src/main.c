#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
// format the linear colorbuffer to profper texture
SDL_Texture* colorBufferTexture = NULL;


uint32_t* colorBuffer = NULL;
int windowWidth = 800;
int windowHeight = 600;
bool isRunning = false;
const int GRIDSIZE = 20;


bool initialize_window(void);
void setup(void);
void processInput(void);
void update(void);
void renderColorBuffer();
void render(void);
void destroyWindow(void);
void clearColorBuffer(uint32_t color);
void drawGrid(void);
void drawRectangle(int windowX,int windowY,int rectWidth,int rectHeight,uint32_t color);	
int main(void){
	/* TODO: Create a SDL a window */

	
	isRunning = initialize_window();

	setup();

	while(isRunning){
		processInput();
		update();
		render();
		
	}
	destroyWindow();
	return 0;
}

void drawRectangle(int windowX,int windowY,int rectWidth,int rectHeight,uint32_t color){	
	for(int  rectColumn = 0; rectColumn < rectWidth; rectColumn++){
		for(int rectRow = 0; rectRow < rectHeight; rectRow++){
			int currentX = rectColumn + windowX;
			int currentY = rectRow + windowY;
			colorBuffer[(windowWidth * currentY) + currentX] = color;
		}
	} 

}

void drawGrid(void){
	// Draw dots
	for(int row = 0; row < windowHeight; row += 10){
		for(int column = 0; column< windowWidth; column += 10){
			// draw dots
				
			// draw grid 10 x 10
			if( column % 10 == 0 || row % 10 == 0){
				colorBuffer[(windowWidth * row) + column] = 0xFF333333;
			}
		}
	}
	// Draw grids	
	/*for(int row = 0; row < windowHeight; row++){
		for(int column = 0; column< windowWidth; column++){
			// draw dots
				
			// draw grid 10 x 10
			if( column % 10 == 0 || row % 10 == 0){
				colorBuffer[(windowWidth * row) + column] = 0xFF333333;
			}
		}
	}*/
}


void update(void){
	//TODO;
}
void renderColorBuffer(){
	// copy color buffer to texture
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,	
		colorBuffer,
		(int)(windowWidth * sizeof(uint32_t))
		
	);
	// want to display the entire texture
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}
void render(void){
	//TODO;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderClear(renderer);
	drawGrid();
	drawRectangle(300, 200, 300, 150, 0xFFFF80);
	renderColorBuffer();
	// clear the color before rendering them
	// rgb
	//clearColorBuffer(0xFF0000FF);
	// black background
	clearColorBuffer(0xFF000000);
	SDL_RenderPresent(renderer);
}

void clearColorBuffer(uint32_t color){
	for(int row = 0; row < windowHeight; row++){
		for(int column = 0; column < windowWidth; column++){
			colorBuffer[(windowWidth * row) + column] = color;
		}
	}	
}

void destroyWindow(void){
	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void setup(void){
	// allocating the size of a grid using windowWidth and windowHeight
	colorBuffer = (uint32_t*) malloc(sizeof(uint32_t) * windowWidth * windowHeight);
	// create SDL texture that is used to display the color buffer	
	colorBufferTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		windowWidth,
		windowHeight
	);
}

void processInput(void){

	
	//TODO; 
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch(event.type){
		// event of close is SDL_QUIT
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE){
				isRunning = false;
			}
			break;
		default:
		break;
	}
} 




bool initialize_window(void){
	// mouse, keyboard
	// test permission to access input signal from keyboard and mouse
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	// WHAT IS the fullscreen max using SDL. width and height
	// fake full screen using current window resolution
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	
	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	// TODO: Create  SDL window
	// no window border = NULL
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
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
	// real window screen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);	
	return true;
}
