#include "display.h"
#include "vector.h"

// Declare an array of vectors 

const int fovFactor  = 700;
const int POINTS = 9 * 9 * 9;
vec3_t cubePoints[POINTS]; //9^3 cube
vec2_t projectedPoints[POINTS];
vec3_t cameraPosition = {
	.x = 0,
	.y = 0,
	.z = -5
};

vec3_t cubeRotation = {

	.x = 0,
	.y = 0,
	.z = 0
};
bool isRunning = false;
void setup(void);
void processInput(void);
void update(void);
void render(void);
int main(void){
	/* TODO: Create a SDL a window */

	
	isRunning = initialize_window();

	setup();
	//vec3_t myvector = {2.0, 3.0, -4.0};
	while(isRunning){
		processInput();
		update();
		render();
		
	}
	destroyWindow();
	return 0;
}

// function that recives a 3D vector and returns a projected 2D point
vec2_t project(vec3_t point){
	vec2_t projectedPoint = {
		.x = (fovFactor * point.x)/ point.z,
		.y = (fovFactor * point.y)/ point.z
	};

	return projectedPoint;
}
void update(void){
	cubeRotation.y += 0.01;
	cubeRotation.z += 0.01;
	cubeRotation.x += 0.01;
	for(int i = 0; i < POINTS; i++){
		vec3_t point = cubePoints[i];
		// rotate in y direction meaning lock the y axis
		vec3_t transformedPoint = vec3RotateX(point, cubeRotation.x);
		 transformedPoint = vec3RotateY(transformedPoint, cubeRotation.y);
		 transformedPoint = vec3RotateZ(transformedPoint, cubeRotation.z);
		// change the z direction 	
		transformedPoint.z -= cameraPosition.z;		
		// Projcet the current point
		vec2_t projectedPoint = project(transformedPoint);

		/*
		// move a way from the camera
		point.z -= cameraPosition.z;		
		// Projcet the current point
		vec2_t projectedPoint = project(point);
		*/
		// Save the projected 2D vector in the array of projected points
		projectedPoints[i] = projectedPoint;		
	}
}

void render(void){
	//TODO;
	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//SDL_RenderClear(renderer);
	drawGrid();
	//drawPixel(20,20, 0xFF00FF);
	//drawRectangle(300, 200, 300, 150, 0xFFFF80);
		
	for ( int i = 0; i < POINTS; i++){
		vec2_t projectedPoint = projectedPoints[i];
		drawRectangle(
			projectedPoint.x + (windowWidth / 2),
			projectedPoint.y + (windowHeight /2),
			4,4,0xFF00FF
		);
	}
	renderColorBuffer();
	// clear the color before rendering them
	// rgb
	//clearColorBuffer(0xFF0000FF);
	// black background
	clearColorBuffer(0xFF000000);
	SDL_RenderPresent(renderer);
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
	// start loading my array of vectors
	int pointCount = 0;	
	for ( float x = -1.0; x <= 1.0;  x += 0.25){
		
		for ( float y = -1.0; y <= 1.0;  y += 0.25){
			for ( float z= -1.0; z <= 1.0;  z += 0.25){
				vec3_t newPoint = {.x = x, .y = y, .z = z};
				cubePoints[pointCount++] = newPoint;
			}
		}
	}
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





