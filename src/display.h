#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

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


#endif
