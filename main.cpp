#include <SDL2/SDL.h>
#include <stdio.h>

#define WIDTH 600 // Canvas width
#define HEIGHT 500 // Canvas height
#define FRAMERATE 80
#define TITLE "Button Hover Effect - Coffee"
#define PEN_SIZE 120

void drawRectangle(SDL_Renderer *renderer, int x, int y, int width, int height);
void renderText(SDL_Renderer *renderer, int x, int y, const char* textContent);

int main(int argc, char* args[]) {

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event e;
    bool running = true;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        int buttonCenterX = WIDTH / 2;
        int buttonCenterY = HEIGHT / 2;
        int buttonWidth = 150; // Increase the button width
        int buttonHeight = 100; // Increase the button height

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool mouseKeyPress = false;

        if (mouseX <= (buttonCenterX + buttonWidth / 2) &&
            mouseX >= (buttonCenterX - buttonWidth / 2) &&
            mouseY <= (buttonCenterY + buttonHeight / 2) &&
            mouseY >= (buttonCenterY - buttonHeight / 2)) {

            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                mouseKeyPress = true;
            }

            if (mouseKeyPress) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            }
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        drawRectangle(renderer, buttonCenterX, buttonCenterY, buttonWidth, buttonHeight);
        renderText(renderer, WIDTH / 2 - 24, HEIGHT / 2 - 17, "Click Me!");

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FRAMERATE);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void drawRectangle(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_Rect rect = { x - width / 2, y - height / 2, width, height };
    SDL_RenderDrawRect(renderer, &rect);
}

void renderText(SDL_Renderer *renderer, int x, int y, const char* textContent) {
    // You can add text rendering functionality here using SDL_ttf library.
}
