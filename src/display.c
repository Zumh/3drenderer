#include "display.h"
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
// format the linear colorbuffer to profper texture
SDL_Texture* colorBufferTexture = NULL;


uint32_t* colorBuffer = NULL;
int windowWidth = 800;
int windowHeight = 600;

// drawing a line in rastering
// DDA algorithm
/*
void draw_line(int x0, int y0, int x1, int y1, uint32_t color){
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);
	
	//int longest_side_length = abs((delta_x >= delta_y) ? delta_x : delta_y);
	int longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);	
	float x_inc = delta_x / (float)longest_side_length;
	float y_inc = delta_y / (float)longest_side_length;

	float current_x = x0;
	float current_y = y0;

	for (int i = 0; i <= longest_side_length; i++){
		drawPixel(round(current_x), round(current_y), color);
		current_x += x_inc;
		current_y += y_inc;
	}


}*/

// using Bresenhame's Algorithm
// https://www.youtube.com/watch?v=CceepU1vIKo
void draw_line(int x0, int y0, int x1, int y1, uint32_t color){
	int x_delta = abs(x1 - x0);
	int y_delta = abs(y1 - y0);
	
	if (x_delta > y_delta) {
		draw_horizontal_line(x0, y0, x1, y1, color);			
	} else {

		draw_vertical_line(x0, y0, x1, y1, color);			
	}
}

void draw_vertical_line(int x0, int y0, int x1, int y1, uint32_t color){
	if (y0 > y1){
		int temp = x0;
		x0 = x1;
		x1 = temp;
				
		temp = y0;
		y0 = y1;
		y1 = temp;	
	}

	int x_delta = x1 - x0;
	int y_delta = y1 - y0;
	
	int direction = (x_delta < 0) ? -1 : 1;
	x_delta *= direction;
	
	if (y_delta != 0){
		int current_x = x0;
		int p = 2 * x_delta - y_delta;
		
		for (int i = 0; i < y_delta + 1; i++){
			drawPixel(current_x, y0 + i, color);
			if (p >= 0){
				current_x += direction;
				p -= 2 * y_delta;
			} 
			p += (2 * x_delta);
		}
	}	
	
}


void draw_horizontal_line(int x0, int y0, int x1, int y1, uint32_t color){
	if (x0 > x1){
		int temp = x0;
		x0 = x1;
		x1 = temp;
			
		temp = y0;
		y0 = y1;
		y1 = temp;	
	}

	int x_delta = x1 - x0;
	int y_delta = y1 - y0;
	
	int direction = (y_delta < 0) ? -1 : 1;
	y_delta *= direction;
	
	if (x_delta != 0){
		int current_y = y0;
		int p = 2 * y_delta - x_delta;
		
		for (int i = 0; i < x_delta + 1; i++){
			drawPixel(x0 + i, current_y, color);
			if (p >= 0){
				current_y += direction;
				p -= 2 * x_delta;
			} 
			p += (2 * y_delta);
		}
	}	
	
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color){
	draw_line(x0, y0, x1, y1, color);
	draw_line(x1, y1, x2, y2, color);
	draw_line(x2, y2, x0, y0, color);
}

void drawPixel(int x, int y, uint32_t color){
	if ( x>=0 && x < windowWidth && y >=0 && y < windowHeight){
		colorBuffer[(windowWidth * y) + x] = color;
	}	
} 

void drawRectangle(int windowX,int windowY,int rectWidth,int rectHeight,uint32_t color){	

	for(int  rectColumn = 0; rectColumn < rectWidth; rectColumn++){
		for(int rectRow = 0; rectRow < rectHeight; rectRow++){
			int currentX = rectColumn + windowX;
			int currentY = rectRow + windowY;
			
			//colorBuffer[(windowWidth * currentY) + currentX] = color;
			drawPixel(currentX, currentY, color);
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
void clearColorBuffer(uint32_t color){
	for(int row = 0; row < windowHeight; row++){
		for(int column = 0; column < windowWidth; column++){
			colorBuffer[(windowWidth * row) + column] = color;
		}
	}	
}

void destroyWindow(void){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
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
	SDL_SetWindowFullscreen(window, 

	//SDL_WINDOW_FULLSCREEN
	0
	);	
	return true;
}
