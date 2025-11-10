#pragma once
#include <iostream>
#include <chrono>

#include <SDL3/SDL.h>

#include "Drawing.hpp"
#include "Rendering.hpp"
#include "Scene.hpp"

int main(int argc, char* argv[]) {
    // SDL Setup
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }
    SDL_Window* Window = SDL_CreateWindow(
        "Rasterizer", RES_X, RES_Y, SDL_WINDOW_RESIZABLE);
    if (!Window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }
    Drawing::Renderer = SDL_CreateRenderer(Window, nullptr);
    SDL_SetRenderDrawColor(Drawing::Renderer, 0, 0, 0, 255);

    Scene Scene{};
    MeshData Cube;
    Cube.Color = Colors::Red;
    Cube.Vertices = {
        Vertex({ -1.0f, -1.0f, 5.0f }),  
        Vertex({ -1.0f,  1.0f, 5.0f }),  
        Vertex({  1.0f,  1.0f, 5.0f }), 
        Vertex({  1.0f, -1.0f, 5.0f }), 
        Vertex({ -1.0f, -1.0f, 6.0f }),  
        Vertex({ -1.0f,  1.0f, 6.0f }),  
        Vertex({  1.0f,  1.0f, 6.0f }),  
        Vertex({  1.0f, -1.0f, 6.0f })   
    };
    Cube.Indices = {
        4, 5, 6,
        4, 6, 7,
        0, 2, 1,
        0, 3, 2,
        0, 4, 5,
        0, 5, 1,
        3, 2, 6,
        3, 6, 7,
        1, 5, 6,
        1, 6, 2,
        0, 3, 7,
        0, 7, 4
    };

    MeshInstance Instance = MeshInstance(Cube);
    Instance.Position = vec3(2, 2, 2);
    Scene.Meshes.push_back(Instance);

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

        // Rendering
        {
            for (auto& Mesh : Scene.Meshes)
                Rendering::RenderMesh(Mesh);
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
