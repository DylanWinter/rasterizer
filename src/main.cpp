#pragma once
#include <iostream>
#include <chrono>

#include <SDL3/SDL.h>

#include "Drawing.hpp"

int main(int argc, char* argv[]) {
    // SDL Setup
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Window* Window = SDL_CreateWindow(
        "Rasterizer", Drawing::ResX, Drawing::ResY, SDL_WINDOW_RESIZABLE);
    if (!Window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* Renderer = SDL_CreateRenderer(Window, nullptr);
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);

    // Main loop
    bool Running = true;
    SDL_Event e;
    while (Running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                Running = false;
        }

        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        SDL_RenderClear(Renderer);

        auto StartTime = std::chrono::high_resolution_clock::now();
        
        // Rendering
        #pragma omp for
        for (int x = -Drawing::ResX / 2; x < Drawing::ResX / 2; x++) 
        {
            for (int y = -Drawing::ResY / 2; y < Drawing::ResY / 2; y++) 
            {

            }
        }

        auto StopTime = std::chrono::high_resolution_clock::now();
        auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(StopTime - StartTime);
        std::cout << "Rendered in " << Duration.count() << " ms." << std::endl;

        SDL_RenderPresent(Renderer);
    }

    // Clean up
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return 0;
}
