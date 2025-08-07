#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bubble_shooting.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Bubble bubbles[NUM_BUBBLES];

// Function to get a random letter with weighted probabilities
char get_random_letter() {
    const char letters[] = "eeeettttaaaaaoooiiiiiiiiiiiiiiiirrrnnnsssssllccddppffgghhjjkkmmmmmqqvvwwxxyybbb";
    int num_letters = sizeof(letters) - 1; // Subtract 1 to ignore the null terminator

    // Generate a random index based on the weighted array
    int index = rand() % num_letters;

    return letters[index];
}

void init_bubble_shooting(SDL_Renderer *renderer) {
    srand((unsigned int)time(NULL)); // Seed the random number generator

    for (int i = 0; i < NUM_BUBBLES; ++i) {
        char path[50];
        sprintf(path, "assets/bubbles/bubble%d.png", i % 12 + 1);
        bubbles[i].texture = load_texture(path, renderer);
        bubbles[i].x = rand() % (800 - 50);
        bubbles[i].y = rand() % (600 - 50);
        bubbles[i].popped = 0;
        bubbles[i].letter = get_random_letter(); // Assign weighted random letters
    }
}

void cleanup_bubble_shooting() {
    for (int i = 0; i < NUM_BUBBLES; ++i) {
        free_texture(bubbles[i].texture);
    }
}

void handle_bubble_shooting_event(SDL_Event *e, Mix_Chunk *shoot_sound, Mix_Chunk *pop_sound, char *collected_letters, int *collected_count) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        for (int i = 0; i < NUM_BUBBLES; ++i) {
            if (!bubbles[i].popped &&
                x >= bubbles[i].x && x <= bubbles[i].x + 50 &&
                y >= bubbles[i].y && y <= bubbles[i].y + 50) {
                bubbles[i].popped = 1;
                Mix_PlayChannel(-1, pop_sound, 0);
                collected_letters[*collected_count] = bubbles[i].letter;
                (*collected_count)++;
                collected_letters[*collected_count] = '\0'; // Null-terminate the string
                break;
            }
        }
    }
}

void render_bubble_shooting(SDL_Renderer *renderer) {
    for (int i = 0; i < NUM_BUBBLES; ++i) {
        if (!bubbles[i].popped) {
            render_texture(bubbles[i].texture, renderer, bubbles[i].x, bubbles[i].y, 50, 50);
        }
    }
}

int check_transition_to_word_forming() {
    for (int i = 0; i < NUM_BUBBLES; ++i) {
        if (!bubbles[i].popped) {
            return 0;
        }
    }
    return 1;
}




