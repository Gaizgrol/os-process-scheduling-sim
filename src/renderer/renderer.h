#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct UI
{
    SDL_Window* window;
    SDL_Renderer* ctx;
    TTF_Font* font;
} UI;

static const int WINDOW_WIDTH = 900;
static const int WINDOW_HEIGHT = 600;

static const SDL_Color BLACK    = { 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE };
static const SDL_Color BLUE     = { 0x00, 0x00, 0XFF, SDL_ALPHA_OPAQUE };
static const SDL_Color CYAN     = { 0x00, 0XFF, 0XFF, SDL_ALPHA_OPAQUE };
static const SDL_Color GRAY     = { 0x7F, 0X7F, 0x7F, SDL_ALPHA_OPAQUE };
static const SDL_Color GREEN    = { 0x00, 0XFF, 0x00, SDL_ALPHA_OPAQUE };
static const SDL_Color MAGENTA  = { 0XFF, 0x00, 0XFF, SDL_ALPHA_OPAQUE };
static const SDL_Color RED      = { 0XFF, 0x00, 0x00, SDL_ALPHA_OPAQUE };
static const SDL_Color WHITE    = { 0XFF, 0XFF, 0XFF, SDL_ALPHA_OPAQUE };
static const SDL_Color YELLOW   = { 0XFF, 0XFF, 0x00, SDL_ALPHA_OPAQUE };

// Construtor
UI* new_ui();
// Destrutor
void delete_ui( UI** render );

// Limpa a tela com uma cor sólida
void clear( UI* render );
void draw_line( UI* canvas, SDL_Color color, int x0, int y0, int x1, int y1 );
// Desenha um retângulo na tela
void draw_rect( UI* canvas, int filled, SDL_Color color, int x, int y, int w, int h );
// Desenha um texto na tela
void draw_text( UI* canvas, const char* text, SDL_Color color, int x, int y );
// Gera uma cor aleatória para o processo
SDL_Color random_dark_color();
// Atualiza e mostra a tela
void refresh( UI* render );

#endif