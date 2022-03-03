#include "renderer.h"

UI* new_ui()
{
    SDL_Init( SDL_INIT_VIDEO );

    UI* canvas = malloc( sizeof( UI ) );

    SDL_Window* win = SDL_CreateWindow(
        "OS Process Scheduling Simulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );
    SDL_Renderer* render = SDL_CreateRenderer( win, -1, SDL_RENDERER_ACCELERATED );

    *canvas = ( UI ) {
        .window = win,
        .ctx = render
    };

    return canvas;
}


void delete_ui( UI** canvas )
{
    SDL_DestroyRenderer( (*canvas)->ctx );
    (*canvas)->ctx = NULL;
    SDL_DestroyWindow( (*canvas)->window );
    (*canvas)->window = NULL;

    free( *canvas );
    *canvas = NULL;

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

void refresh( UI* canvas )
{
    SDL_RenderPresent( canvas->ctx );
}