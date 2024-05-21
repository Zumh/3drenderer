#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* color_buffer_texture;
extern uint32_t* color_buffer;
extern int WINDOW_WIDTH;
extern int  WINDOW_HEIGHT;


// index calculation
int calculate_color_index(int x, int y, int window_width);

// Function prototypes
void draw_rect(int x, int y, int width, int height, uint32_t color);
bool initialize_window(void);
void destroy_window(void);
void render_color_buffer(void);
void draw_grid(void);
void clear_color_buffer(uint32_t color);
#endif
