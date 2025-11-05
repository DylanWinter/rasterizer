#pragma once
#include <iostream>
#include <chrono>

#include <SDL3/SDL.h>

#include "Drawing.hpp"
#include "Rendering.hpp"

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
    Drawing::Renderer = SDL_CreateRenderer(Window, nullptr);
    SDL_SetRenderDrawColor(Drawing::Renderer, 0, 0, 0, 255);

    // Main loop
    bool Running = true;
    SDL_Event e;
    while (Running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT)
                Running = false;
        }

        SDL_SetRenderDrawColor(Drawing::Renderer, 0, 0, 0, 255);
        SDL_RenderClear(Drawing::Renderer);

        auto StartTime = std::chrono::high_resolution_clock::now();
        
        Vertex vAf({ -1.0f, -1.0f, 5.0f }, 1.0f); 
        Vertex vBf({ -1.0f,  1.0f, 5.0f }, 1.0f); 
        Vertex vCf({ 1.0f,  1.0f, 5.0f }, 1.0f); 
        Vertex vDf({ 1.0f, -1.0f, 5.0f }, 1.0f); 
        Vertex vAb({ -1.0f, -1.0f, 6.0f }, 1.0f); 
        Vertex vBb({ -1.0f,  1.0f, 6.0f }, 1.0f); 
        Vertex vCb({ 1.0f,  1.0f, 6.0f }, 1.0f); 
        Vertex vDb({ 1.0f, -1.0f, 6.0f }, 1.0f); 

        // Rendering
        {
            Rendering::RenderTriangle(vAb, vBb, vCb, Colors::Red);
            Rendering::RenderTriangle(vAb, vCb, vDb, Colors::Red);
            Rendering::RenderTriangle(vAf, vBf, vCf, Colors::Blue);
            Rendering::RenderTriangle(vAf, vCf, vDf, Colors::Blue);
            Rendering::RenderTriangle(vAf, vAb, vBb, Colors::Green);
            Rendering::RenderTriangle(vAf, vBb, vBf, Colors::Green);
            Rendering::RenderTriangle(vDf, vCf, vCb, Colors::Yellow);
            Rendering::RenderTriangle(vDf, vCb, vDb, Colors::Yellow);
            Rendering::RenderTriangle(vBf, vBb, vCb, Colors::Cyan);
            Rendering::RenderTriangle(vBf, vCb, vCf, Colors::Cyan);
            Rendering::RenderTriangle(vAf, vDf, vDb, Colors::Magenta);
            Rendering::RenderTriangle(vAf, vDb, vAb, Colors::Magenta);
        }

        auto StopTime = std::chrono::high_resolution_clock::now();
        auto Duration = std::chrono::duration_cast<std::chrono::milliseconds>(StopTime - StartTime);
        std::cout << "Rendered in " << Duration.count() << " ms." << std::endl;

        SDL_RenderPresent(Drawing::Renderer);
    }

    // Clean up
    SDL_DestroyRenderer(Drawing::Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
    return 0;
}
