#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* load_texture(const char *path, SDL_Renderer *renderer);
Mix_Chunk* load_sound(const char *path);
TTF_Font* load_font(const char *path, int font_size);
void free_texture(SDL_Texture *texture);
void free_sound(Mix_Chunk *sound);
void free_font(TTF_Font *font);

void render_texture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h);
void render_collected_letters(SDL_Renderer *renderer, TTF_Font *font, const char *collected_letters, int collected_count);

#endif





















