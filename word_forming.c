#include <stdio.h>
#include <string.h>
#include "word_forming.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define MAX_WORDS 3

char user_input[100] = "";
char formed_words[MAX_WORDS][20];
int current_word = 0;
int is_input_error = 0;

int is_valid_word(const char *word) {
    FILE *file = fopen("assets/valid_words.txt", "r");
    if (!file) {
        printf("Failed to open valid_words.txt\n");
        return 0;
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
        if (strcmp(buffer, word) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void handle_word_forming_event(SDL_Event *e, char *collected_letters, int *num_collected_letters) {
    if (e->type == SDL_KEYDOWN) {
        printf("Key pressed: %d\n", e->key.keysym.sym);
        if (e->key.keysym.sym == SDLK_RETURN) {
            printf("Enter key pressed. Current input: %s\n", user_input);
            if (is_valid_word(user_input)) {
                strcpy(formed_words[current_word], user_input);
                current_word++;
                user_input[0] = '\0';
                is_input_error = 0;  // Clear user input
                printf("Valid word formed. Total words: %d\n", current_word);
                if (current_word >= MAX_WORDS) {
                    printf("All words formed!\n");
                }
            } else {
                printf("Invalid word! Please reenter.\n");
                is_input_error = 1; // Set input error flag for invalid word
            }
        } else if (e->key.keysym.sym == SDLK_BACKSPACE && strlen(user_input) > 0) {
            user_input[strlen(user_input) - 1] = '\0'; // Remove last character
            printf("Backspace pressed. Current input: %s\n", user_input);
        } else if (strlen(user_input) < sizeof(user_input) - 1) {
            char ch = e->key.keysym.sym;
            if (ch >= 'a' && ch <= 'z') {
                // Check if the letter is in collected_letters
                int letter_found = 0;
                for (int i = 0; i < *num_collected_letters; ++i) {
                    if (collected_letters[i] == ch) {
                        letter_found = 1;
                        break;
                    }
                }
                if (letter_found) {
                    user_input[strlen(user_input)] = ch;
                    user_input[strlen(user_input) + 1] = '\0';
                    printf("Letter %c added. Current input: %s\n", ch, user_input);
                } else {
                    printf("Letter %c not found in collected letters\n", ch);
                }
            }
        }
    }
}

void render_word_forming(SDL_Renderer *renderer, TTF_Font *font, char *collected_letters, int num_collected_letters) {
    char text[100];
    snprintf(text, sizeof(text), "Collected Letters: %s", collected_letters);
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, (SDL_Color){255, 255, 255, 255});
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect = {20, 20, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    snprintf(text, sizeof(text), "Current Word: %s", user_input);
    text_surface = TTF_RenderText_Solid(font, text, (SDL_Color){255, 255, 255, 255});
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    text_rect = (SDL_Rect){20, 60, text_surface->w, text_surface->h};
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);

    for (int i = 0; i < current_word; ++i) {
        snprintf(text, sizeof(text), "Word %d: %s", i + 1, formed_words[i]);
        text_surface = TTF_RenderText_Solid(font, text, (SDL_Color){255, 255, 255, 255});
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        text_rect = (SDL_Rect){20, 100 + i * 40, text_surface->w, text_surface->h};
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    // Render completion or error message
    if (current_word >= MAX_WORDS) {
        snprintf(text, sizeof(text), "You have formed 3 words!");
        text_surface = TTF_RenderText_Solid(font, text, (SDL_Color){0, 255, 0, 255}); // Green color
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        text_rect = (SDL_Rect){20, 300, text_surface->w, text_surface->h}; // Adjust position as needed
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    } else if (is_input_error == 1) {
        snprintf(text, sizeof(text), "Invalid word!");
        text_surface = TTF_RenderText_Solid(font, text, (SDL_Color){255, 0, 0, 255}); // Red color
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        text_rect = (SDL_Rect){20, 300, text_surface->w, text_surface->h}; // Adjust position as needed
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    } else if (is_input_error == 2) {
        snprintf(text, sizeof(text), "nice!valid word");
        text_surface = TTF_RenderText_Solid(font, text, (SDL_Color){255, 0, 0, 255}); // Red color
        text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        text_rect = (SDL_Rect){20, 300, text_surface->w, text_surface->h}; // Adjust position as needed
        SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }
}







