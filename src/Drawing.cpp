#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

#include "Drawing.hpp"

namespace 
{
	std::vector<float> Interpolate(int i0, float d0, int i1, float d1)
	{
		if (i0 == i1)
			return std::vector<float>(d0);

		std::vector<float> Values{};
		float a = (d1 - d0) / (i1 - i0);
		float d = d0;
		for (int i = i0; i <= i1; i++)
		{
			Values.push_back(d);
			d += a;
		}
		return Values;
	}
}

namespace Drawing 
{
	// Draws a single pixel on screen
	void DrawPixel(SDL_Renderer* Renderer, int x, int y, color4 Color) 
	{
		if (x > ResX) 
		{
			std::cout << "DrawPixel given invalid x coordinate: " << x << std::endl;
			return;
		}
		if (y > ResY)
		{
			std::cout << "DrawPixel given invalid y coordinate: " << y << std::endl;
			return;
		}
		
		auto Remap = [](float Value)
		{
			return Value / (Value + 1.0f);
		};
		SDL_SetRenderDrawColor(Renderer, Remap(Color.r) * 255, Remap(Color.g) * 255, Remap(Color.b) * 255, Color.a * 255);
		SDL_RenderPoint(Renderer, x, y);
	}

	// Wrapper to allow passing in an ivec2 instead of separate x and y 
	void DrawPixel(SDL_Renderer* Renderer, ivec2 Position, color4 Color)
	{
		DrawPixel(Renderer, Position.x, Position.y, Color);
	}

	// Draws a line of pixels from Start to End
	void DrawLine(SDL_Renderer* Renderer, ivec2 Start, ivec2 End, color4 Color)
	{
		if (Start == End)
		{
			DrawPixel(Renderer, Start, Color);
			return;
		}
		// More horizontal than vertical
		if (std::abs(End.x - Start.x) > std::abs(End.y - Start.y))
		{
			// Swap if line moves right to left
			if (Start.x > End.x)
				std::swap(Start, End);

			auto YValues = Interpolate(Start.x, Start.y, End.x, End.y);

			for (int x = Start.x; x <= End.x; x++)
				DrawPixel(Renderer, x, std::round<int>(YValues[x - Start.x]), Color);
		}
		// More vertical than horizontal
		else
		{
			// Swap if line moves upwards
			if (Start.y > End.y)
				std::swap(Start, End);

			auto XValues = Interpolate(Start.y, Start.x, End.y, End.x);

			for (int y = Start.y; y <= End.y; y++)
				DrawPixel(Renderer, std::round<int>(XValues[y - Start.y]), y, Color);
		}
	}
}