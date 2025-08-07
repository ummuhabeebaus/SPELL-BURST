#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "bubble_shooting.h"
#include "word_forming.h"
#include "utils.h"

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#include <windows.h>
#endif

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Global variables
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Mix_Chunk *shoot_sound = NULL;
Mix_Chunk *pop_sound = NULL;
TTF_Font *font = NULL;
int game_stage = 0; // 0 for bubble shooting, 1 for word forming
char collected_letters[100];
int collected_count = 0;

// Initialize SDL and create window/renderer
int init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 0;
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("IMG_Init Error: %s\n", IMG_GetError());
        return 0;
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        return 0;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        return 0;
    }

    window = SDL_CreateWindow("SPELL-BURST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 0;
    }
    shoot_sound = load_sound("assets/sounds/shoot.wav");
    pop_sound = load_sound("assets/sounds/pop.wav");
    font = load_font("assets/fonts/font.ttf", 24);

    if (!shoot_sound || !pop_sound || !font) {
        return 0;
    }

    init_bubble_shooting(renderer);
    return 1;
}

// Clean up resources
void close() {
    free_font(font);
    free_sound(shoot_sound);
    free_sound(pop_sound);
    cleanup_bubble_shooting();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!init()) {
        printf("Initialization failed!\n");
        return 1;
    }

    SDL_Event e;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            if (game_stage == 0) { // Bubble shooting stage
                handle_bubble_shooting_event(&e, shoot_sound, pop_sound, collected_letters, &collected_count);
                if (check_transition_to_word_forming()) {
                    game_stage = 1;
                }
            } else if (game_stage == 1) { // Word forming stage
                handle_word_forming_event(&e, collected_letters, &collected_count);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (game_stage == 0) {
            render_bubble_shooting(renderer);
            render_collected_letters(renderer, font, collected_letters, collected_count);
        } else if (game_stage == 1) {
            render_word_forming(renderer, font, collected_letters, collected_count);
        }

        SDL_RenderPresent(renderer);
    }

    close();
    return 0;
}

#ifdef _WIN32
// Define a custom structure to hold command-line arguments
typedef struct {
    int argc;
    char** argv;
} Argv;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Convert the command-line arguments
    int argc = __argc;
    char** argv = __argv;

    // Call the main function
    return main(argc, argv);
}
#endif


























