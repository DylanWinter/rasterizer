#pragma once
#include <SDL3/SDL.h>
#include "Vec.hpp"

constexpr int RES_X = 640;
constexpr int RES_Y = 640;

namespace Colors 
{
    inline const vec4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline const vec4 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline const vec4 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
    inline const vec4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
    inline const vec4 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
    inline const vec4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
    inline const vec4 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
    inline const vec4 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
    inline const vec4 Gray = { 0.502f, 0.502f, 0.502f, 1.0f }; 
    inline const vec4 Orange = { 1.0f, 0.647f, 0.0f, 1.0f };     
    inline const vec4 Purple = { 0.502f, 0.0f, 0.502f, 1.0f };  
    inline const vec4 Brown = { 0.647f, 0.165f, 0.165f, 1.0f }; 
}

struct Vertex2D
{
    ivec2 Position;
    float Intensity = 1.0;

    Vertex2D(const ivec2& Position, float intensity = 1.0f)
        : Position(Position), Intensity(intensity)
    {}
};

namespace Drawing 
{
    inline SDL_Renderer* Renderer = nullptr;

	void DrawPixel(int x, int y, color4 Color);
	void DrawPixel(ivec2 Position, color4 Color);
    void DrawLine(ivec2 Start, ivec2 End, color4 Color);
    void DrawTriangle(Vertex2D Point0, Vertex2D Point1, Vertex2D Point2, const color4& Color, bool Filled = true);
}
