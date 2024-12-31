#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "array.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

// Array of triangles should be rendered frame by frame
// allocating dynamic memory inside a game loop is bad idea because it slow things down
triangle_t* triangles_to_render = NULL;

// Declare an array of vectors 
const int fovFactor  = 700;
vec3_t cameraPosition = {
	.x = 0,
	.y = 0,
	.z = -5
};


bool isRunning = false;
int previousFrameTime = 0;

void setup(void);
void processInput(void);
void update(void);
void render(void);
void free_resources(void);
int main(void){
	/* Create a SDL a window */

	
	isRunning = initialize_window();

	setup();

	while(isRunning){
		processInput();
		update();
		render();
		
	}

	destroyWindow();
	free_resources();
	return 0;
}

// free the memory that was dynamically allocated by the program
void free_resources(void){
	free(colorBuffer);
	array_free(mesh.faces);
	array_free(mesh.vertices);	
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
	// manual delay, relying on process speed
	// calculate reamining time to wait
	int remainingTimeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);
	// if the reamining time to wait is within target time frame then do the waiting using os delay 
	// os delay does context switching
	if (remainingTimeToWait > 0 && remainingTimeToWait <= FRAME_TARGET_TIME){
		SDL_Delay(remainingTimeToWait);
	}	
	previousFrameTime = SDL_GetTicks();

	// initialize the array of triangles to render
	triangles_to_render = NULL;	
	
	mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.01;
	mesh.rotation.x += 0.01;
	
	// Loop all triangle faces of our mesh
	int num_faces = array_length(mesh.faces);

	for(int i = 0; i < num_faces; i++){
		face_t mesh_face = mesh.faces[i];
		
		vec3_t face_vertices[3];
		face_vertices[0] = mesh.vertices[mesh_face.a - 1];
		face_vertices[1] = mesh.vertices[mesh_face.b - 1];
		face_vertices[2] = mesh.vertices[mesh_face.c - 1];
		
		triangle_t projected_triangle;
	
		// Loop all three vertices of this current face and apply tranformations
		
		for(int j = 0; j < 3; j++){
			vec3_t transformed_vertex = face_vertices[j];
			transformed_vertex = vec3RotateX(transformed_vertex, mesh.rotation.x);
			transformed_vertex = vec3RotateY(transformed_vertex, mesh.rotation.y);
			transformed_vertex = vec3RotateZ(transformed_vertex, mesh.rotation.z);
			
			// Translate the vertex away from the camera
			transformed_vertex.z -= cameraPosition.z;

			// Project the current vertex
			vec2_t projected_point = project(transformed_vertex);
			// Sacle and translate the projected points to the middle of the screen
			projected_point.x += (windowWidth/2);
			projected_point.y += (windowHeight/2);

			projected_triangle.points[j] = projected_point;
		
		}
		
		// Save the projected triangle in the array of triangles to render
		//triangles_to_render[i] = projected_triangle;
		array_push(triangles_to_render, projected_triangle);
	}


}


void render(void){
	drawGrid();
	

	// Loop all projected triangles and render then

	int num_triangles = array_length(triangles_to_render);

	for(int i = 0; i < num_triangles; i++){
		triangle_t triangle = triangles_to_render[i];
		
		// Draw vertex points
		drawRectangle(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFFFF00);
		drawRectangle(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFFFF00);
		drawRectangle(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFFFF00);

		// Draw unfilled triangle
		draw_triangle(
			triangle.points[0].x,
			triangle.points[0].y,
			triangle.points[1].x,
			triangle.points[1].y,
			triangle.points[2].x,
			triangle.points[2].y,
			0xFF00FF00
		);
	}	
		
	// Clear the array of triangles to render every frame loop
	array_free(triangles_to_render);
	
	renderColorBuffer();
	// clear the color before rendering them
	// rgb
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

	// Loads the cube value in the mesh data structure
	//	load_cube_mesh_data();
	load_obj_file_data("./assets/cube.obj");
}

void processInput(void){

	
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





