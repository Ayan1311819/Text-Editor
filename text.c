#include <stdio.h>
#include<stddef.h>
#include <SDL2/SDL.h>
#include <assert.h>
#define WIDTH 1024
#define HEIGHT 576

typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 i32;
typedef Sint64 i64;
int main(int argc ,char *argv[]){
	
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window *win = SDL_CreateWindow("Spell Checker", 320,200,WIDTH,HEIGHT,0);
	assert(win);
	SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_SOFTWARE);
	assert(renderer);
	SDL_Texture *screen = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	assert(screen);
	u32 *screen_pixels = (u32*) calloc(WIDTH*HEIGHT,sizeof(u32));
	return 0;
}
