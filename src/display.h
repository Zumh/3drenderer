#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000/FPS)

extern SDL_Window* window;
extern SDL_Renderer* renderer;
// format the linear colorbuffer to profper texture
extern SDL_Texture* colorBufferTexture;


extern uint32_t* colorBuffer;
extern int windowWidth;
extern int windowHeight;


bool initialize_window(void);
void renderColorBuffer();
void destroyWindow(void);
void clearColorBuffer(uint32_t color);
void drawGrid(void);
void drawPixel(int x, int y, uint32_t color); 
void drawRectangle(int windowX,int windowY,int rectWidth,int rectHeight,uint32_t color);	

void draw_triangle(int x0, int y0, int x1, int y1, int x2,  int y2, uint32_t color);
void draw_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_horizontal_line(int x0, int y0, int x1, int y1, uint32_t color);
void draw_vertical_line(int x0, int y0, int x1, int y1, uint32_t color);
#endif
