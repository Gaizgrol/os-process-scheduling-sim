#include <SDL2/SDL_ttf.h>
#include "renderer.h"

UI* new_ui()
{
    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();

    UI* canvas = malloc( sizeof( UI ) );

    SDL_Window* win = SDL_CreateWindow(
        "OS Process Scheduling Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* render = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );
    TTF_Font* font = TTF_OpenFont( "assets/Pixellettersfull-BnJ5.ttf", 16 );

    *canvas = ( UI ) {
        .window = win,
        .ctx = render,
        .font = font
    };

    return canvas;
}


void delete_ui( UI** canvas )
{
    TTF_CloseFont( (*canvas)->font );
    (*canvas)->font = NULL;
    SDL_DestroyRenderer( (*canvas)->ctx );
    (*canvas)->ctx = NULL;
    SDL_DestroyWindow( (*canvas)->window );
    (*canvas)->window = NULL;

    free( *canvas );
    *canvas = NULL;

    TTF_Quit();
    SDL_Quit();
}

void clear( UI* canvas )
{
    SDL_SetRenderDrawColor( canvas->ctx, 0, 0, 0, SDL_ALPHA_OPAQUE );
    SDL_RenderClear( canvas->ctx );
}

void draw_rect( UI* canvas, int filled, SDL_Color color, int x, int y, int w, int h )
{
    SDL_SetRenderDrawColor( canvas->ctx, color.r, color.g, color.b, color.a );
    if ( filled )
        SDL_RenderFillRect( canvas->ctx, &((SDL_Rect){ x, y, w, h }) );
    else
        SDL_RenderDrawRect( canvas->ctx, &((SDL_Rect){ x, y, w, h }) );
}

void draw_text( UI* canvas, const char* text, SDL_Color color, int x, int y )
{
    SDL_Surface* surf = TTF_RenderText_Solid( canvas->font, text, color );
    SDL_Texture* txtr = SDL_CreateTextureFromSurface( canvas->ctx, surf );
    
    int w = 0, h = 0;
    SDL_QueryTexture( txtr, NULL, NULL, &w, &h );
    SDL_RenderCopy( canvas->ctx, txtr, NULL, &(SDL_Rect){ x, y, w, h } );

    SDL_DestroyTexture( txtr );
    SDL_FreeSurface( surf );
}

void refresh( UI* canvas )
{
    SDL_RenderPresent( canvas->ctx );
}