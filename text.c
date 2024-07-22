#include <stdio.h>
#include<stddef.h>
#include <SDL2/SDL.h>
#include <assert.h>
#define WIDTH 1024
#define HEIGHT 576
#define FALSE 0
#define TRUE 1
#define BOOL u32

typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 i32;
typedef Sint64 i64;

typedef struct
{
   int x;
   int y;
   int w;
   int h;
} rect_t;

void FILLRECT(rect_t rect, u32 pixel_color, u32 *screen_pixels)
{
	SDL_assert(screen_pixels);
	for (int row=0; row< rect.h; ++row)
	{
		for(int col=0; col<rect.w; ++col)
		{
			screen_pixels[(row+rect.y)*WIDTH+col+rect.x] = pixel_color; //colouring the screen pixels to look like rectangle
		}	
	}
}


int main(int argc ,char *argv[]){

// Create a Basic window
	 
SDL_Init(SDL_INIT_VIDEO);
	
SDL_Window *win = SDL_CreateWindow("Spell Checker", 320,200,WIDTH,HEIGHT,0);
assert(win);
SDL_Renderer *renderer = SDL_CreateRenderer(win, 0, SDL_RENDERER_SOFTWARE);
assert(renderer);
SDL_Texture *screen = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
assert(screen);
u32 *screen_pixels = (u32*) calloc(WIDTH*HEIGHT,sizeof(u32));
//SDL_Delay(7000); //Displaying window for 7 seconds	
    
rect_t cursor = {0,0,10,10};
cursor.x =  (WIDTH-cursor.w)/2;
cursor.y = (HEIGHT-cursor.h)/2;
FILLRECT(cursor,255, screen_pixels);
	
SDL_UpdateTexture(screen, NULL, screen_pixels, WIDTH * sizeof(u32));
SDL_RenderCopy(renderer, screen, NULL, NULL);
SDL_RenderPresent(renderer);
    

BOOL done = FALSE;
while(!done)
      {
    	SDL_Event event;
    	while(SDL_PollEvent(&event))
    	{
		if (event.type == SDL_QUIT){ // closing the window 
			done = TRUE;
			break;}
    	}
    }
return 0;
}
