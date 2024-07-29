#include <stdio.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

#define WIDTH 1024
#define HEIGHT 576
#define FALSE 0
#define TRUE 1
#define BOOL u32
#define LEN 120

typedef Uint32 u32;
typedef Uint64 u64;
typedef Sint32 i32;
typedef Sint64 i64;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} rect_t;

void FILLRECT(rect_t rect, u32 pixel_color, u32 *screen_pixels) {
    SDL_assert(screen_pixels);
    for (int row = 0; row < rect.h; ++row) {
        for (int col = 0; col < rect.w; ++col) {
            screen_pixels[(row + rect.y) * WIDTH + col + rect.x] = pixel_color;
        }
    }
}
int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Spell Checker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    assert(win);
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    assert(renderer);
    SDL_Texture *screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    assert(screen);
    u32 *screen_pixels = (u32 *)calloc(WIDTH * HEIGHT, sizeof(u32));
    assert(screen_pixels);
    
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }
        
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }
     
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "  ", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    //int textWidth = textSurface->w;
    //int textHeight = textSurface->h;
    int twl = 14 ;
    SDL_FreeSurface(textSurface);
    SDL_SetRenderTarget(renderer, textTexture);
    rect_t cursor = {0, 0, 2, 24};
    FILLRECT(cursor, 0xFFFFFF, screen_pixels);
    SDL_UpdateTexture(screen, NULL, screen_pixels, WIDTH * sizeof(u32));
    SDL_RenderCopy(renderer, screen, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, textTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    
    char ascii = '\0'; 
    char buffer[LEN] = {0};
    BOOL done = FALSE;
    int id = 0;
    
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = TRUE;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode kcode = event.key.keysym.sym;
                switch (kcode) {
                    case SDLK_ESCAPE:
                        done = TRUE;
                        break;
                    case SDLK_UP:
                        cursor.y = (cursor.y - twl + HEIGHT) % HEIGHT;
                        break;
                    case SDLK_DOWN:
                        cursor.y = (cursor.y + twl) % HEIGHT;
                        break;
                    case SDLK_LEFT:
                        cursor.x = (cursor.x - twl + WIDTH) % WIDTH;
                        break;
                    case SDLK_RIGHT:
                        cursor.x = (cursor.x + twl) % WIDTH;
                        break;
                    case SDLK_BACKSPACE:
                        if (id > 0) {
                            id--;
                            buffer[id] = '\0';
                        }
                        break;
                    default:
                        ascii = (char)kcode;
                        break;
                }
            }
        }
        
        memset(screen_pixels, 0, WIDTH * HEIGHT * sizeof(u32));
        SDL_RenderClear(renderer);
        
		SDL_SetRenderTarget(renderer, textTexture);
        FILLRECT(cursor, 0xFFFFFF, screen_pixels);
        SDL_UpdateTexture(screen, NULL, screen_pixels, WIDTH * sizeof(u32));
        SDL_RenderCopy(renderer, screen, NULL, NULL);

        SDL_SetRenderTarget(renderer, NULL);
		if (((ascii >= 'a' && ascii <= 'z') || (ascii >= '0' && ascii <= '9')) && id < LEN - 1) {
				            buffer[id++] = ascii;
				            buffer[id] = '\0';}
		
		ascii = '\0';
		textSurface = TTF_RenderText_Solid(font, buffer, textColor);
        if(textSurface){
        	
        	SDL_DestroyTexture(textTexture);
        	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        	SDL_Rect renderQuad = {0, 0, textSurface->w, textSurface->h};
        	SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    		SDL_FreeSurface(textSurface);
    		SDL_RenderPresent(renderer);}     
    }
    
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    free(screen_pixels);
    return 0;
}
