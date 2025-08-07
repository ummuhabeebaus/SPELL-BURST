#ifndef WORD_FORMING_H
#define WORD_FORMING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void handle_word_forming_event(SDL_Event *e, char *collected_letters, int *num_collected_letters);
void render_word_forming(SDL_Renderer *renderer, TTF_Font *font, char *collected_letters, int num_collected_letters);

#endif














