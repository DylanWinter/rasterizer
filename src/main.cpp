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
    Cube.Vertices = {
        Vertex({ -0.5f, -0.5f, -0.5f }),
        Vertex({ -0.5f,  0.5f, -0.5f }),
        Vertex({  0.5f,  0.5f, -0.5f }),
        Vertex({  0.5f, -0.5f, -0.5f }),
        Vertex({ -0.5f, -0.5f,  0.5f }),
        Vertex({ -0.5f,  0.5f,  0.5f }),
        Vertex({  0.5f,  0.5f,  0.5f }),
        Vertex({  0.5f, -0.5f,  0.5f })
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
    Instance.Transform.Position = vec3(2, 1, 7);
    Instance.Transform.Rotation = vec3(0.0f, DegToRad(45.0f), 0.0f);
    Scene.Meshes.push_back(Instance);

    MeshInstance Instance2 = MeshInstance(Cube);
    Instance2.Transform.Position = vec3(-2, 1, 7);
    Instance2.Transform.Rotation = vec3(0.0f, DegToRad(-45.0f), 0.0f);
    Instance2.Color = Colors::Blue;
    Scene.Meshes.push_back(Instance2);

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
