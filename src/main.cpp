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
            Drawing::DrawTriangle(Renderer, Vertex({ 100, 50 }, 1.0f), Vertex({ 150, 200 }, 0.6f), Vertex({ 50, 200 }, 0.0f), Colors::Red);
            Drawing::DrawTriangle(Renderer, Vertex({ 20, 20 }, 1.0f), Vertex({ 40, 60 }, 0.5f), Vertex({ 10, 50 }, 0.2f), Colors::Blue);
            Drawing::DrawTriangle(Renderer, Vertex({ 200, 50 }, 1.0f), Vertex({ 220, 180 }, 0.7f), Vertex({ 180, 180 }, 0.4f), Colors::Yellow);
            Drawing::DrawTriangle(Renderer, Vertex({ 50, 150 }, 0.9f), Vertex({ 250, 150 }, 0.5f), Vertex({ 150, 300 }, 0.1f), Colors::Cyan);
            Drawing::DrawTriangle(Renderer, Vertex({ 300, 50 }, 1.0f), Vertex({ 250, 200 }, 0.6f), Vertex({ 350, 200 }, 0.3f), Colors::Magenta);
            Drawing::DrawTriangle(Renderer, Vertex({ 400, 100 }, 1.0f), Vertex({ 500, 50 }, 0.5f), Vertex({ 500, 150 }, 0.2f), Colors::Orange);
            Drawing::DrawTriangle(Renderer, Vertex({ 600, 100 }, 1.0f), Vertex({ 500, 50 }, 0.5f), Vertex({ 500, 150 }, 0.2f), Colors::Green);
            Drawing::DrawTriangle(Renderer, Vertex({ 10, 10 }, 1.0f), Vertex({ 15, 15 }, 0.5f), Vertex({ 5, 20 }, 0.2f), Colors::White);
            Drawing::DrawTriangle(Renderer, Vertex({ 0, 590 }, 1.0f), Vertex({ 400, 590 }, 0.7f), Vertex({ 200, 150 }, 0.3f), Colors::Purple);

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
