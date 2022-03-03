#include <SDL2/SDL.h>

typedef struct UI
{
    SDL_Window* window;
    SDL_Renderer* ctx;
} UI;

// Construtor
UI* new_ui();
// Destrutor
void delete_ui( UI** render );

// Limpa a tela com uma cor sólida
void clear( UI* render );
// Desenha um retângulo na tela
void draw_rect( UI* canvas, int filled, SDL_Color color, int x, int y, int w, int h );
// Atualiza e mostra a tela
void refresh( UI* render );