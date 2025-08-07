#include "utils.h"
#include <stdio.h>

#define WINDOW_HEIGHT 600

SDL_Texture* load_texture(const char *path, SDL_Renderer *renderer) {
    SDL_Texture *texture = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path);
    if (!loaded_surface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
    if (!texture) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
    }
    SDL_FreeSurface(loaded_surface);
    return texture;
}

Mix_Chunk* load_sound(const char *path) {
    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (!sound) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
    }
    return sound;
}

TTF_Font* load_font(const char *path, int font_size) {
    TTF_Font *font = TTF_OpenFont(path, font_size);
    if (!font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    return font;
}

void free_texture(SDL_Texture *texture) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void free_sound(Mix_Chunk *sound) {
    if (sound) {
        Mix_FreeChunk(sound);
    }
}

void free_font(TTF_Font *font) {
    if (font) {
        TTF_CloseFont(font);
    }
}

void render_texture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y, int w, int h) {
    SDL_Rect renderQuad = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
}

void render_collected_letters(SDL_Renderer *renderer, TTF_Font *font, const char *collected_letters, int collected_count) {
    char text[256];
    snprintf(text, sizeof(text), "Collected Letters: %s", collected_letters);

    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, textColor);
    if (!text_surface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(text_surface);
        return;
    }

    SDL_Rect text_rect = {20, WINDOW_HEIGHT - 50, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}




