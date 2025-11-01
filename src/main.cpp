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
        {
            Drawing::DrawLine(Renderer, ivec2(100, 100), ivec2(0, 0), Colors::White);
            Drawing::DrawLine(Renderer, ivec2(0, 100), ivec2(100, 0), Colors::Red);
            Drawing::DrawLine(Renderer, ivec2(200, 50), ivec2(10, 50), Colors::Green);
            Drawing::DrawLine(Renderer, ivec2(50, 60), ivec2(200, 60), Colors::Blue);
            Drawing::DrawLine(Renderer, ivec2(150, 120), ivec2(150, 10), Colors::Yellow);
            Drawing::DrawLine(Renderer, ivec2(160, 20), ivec2(160, 120), Colors::Magenta);
            Drawing::DrawLine(Renderer, ivec2(180, 80), ivec2(20, 30), Colors::Cyan);
            Drawing::DrawLine(Renderer, ivec2(80, 200), ivec2(50, 20), Colors::Orange);
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
