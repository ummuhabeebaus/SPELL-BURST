#ifndef BUBBLE_SHOOTING_H
#define BUBBLE_SHOOTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#define NUM_BUBBLES 12

typedef struct {
    SDL_Texture *texture;
    int x, y;
    int popped;
    char letter;
} Bubble;

extern Bubble bubbles[NUM_BUBBLES];

void init_bubble_shooting(SDL_Renderer *renderer);
void cleanup_bubble_shooting();
void handle_bubble_shooting_event(SDL_Event *e, Mix_Chunk *shoot_sound, Mix_Chunk *pop_sound, char *collected_letters, int *collected_count);
void render_bubble_shooting(SDL_Renderer *renderer);
int check_transition_to_word_forming();

#endif





















