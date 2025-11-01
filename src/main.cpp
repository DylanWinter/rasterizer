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
            Drawing::DrawTriangle(Renderer, ivec2(100, 50), ivec2(150, 200), ivec2(50, 200), Colors::Red);
            Drawing::DrawTriangle(Renderer, ivec2(20, 20), ivec2(40, 60), ivec2(10, 50), Colors::Blue);
            Drawing::DrawTriangle(Renderer, ivec2(200, 50), ivec2(220, 180), ivec2(180, 180), Colors::Yellow);
            Drawing::DrawTriangle(Renderer, ivec2(50, 150), ivec2(250, 150), ivec2(150, 100), Colors::Cyan);
            Drawing::DrawTriangle(Renderer, ivec2(300, 50), ivec2(250, 200), ivec2(350, 200), Colors::Magenta);
            Drawing::DrawTriangle(Renderer, ivec2(400, 100), ivec2(500, 50), ivec2(500, 150), Colors::Orange);
            Drawing::DrawTriangle(Renderer, ivec2(600, 100), ivec2(500, 50), ivec2(500, 150), Colors::Green);
            Drawing::DrawTriangle(Renderer, ivec2(10, 10), ivec2(15, 15), ivec2(5, 20), Colors::White);
            Drawing::DrawTriangle(Renderer, ivec2(0, 590), ivec2(400, 590), ivec2(200, 150), Colors::Purple);
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
