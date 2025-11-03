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
			return std::vector<float>{d0};

		std::vector<float> Values{};
		Values.reserve(i1 - i0 + 1);
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
		if (x > ResX || y > ResY)
		{
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

	void DrawTriangle(SDL_Renderer* Renderer, Vertex Point0, Vertex Point1, Vertex Point2, color4 Color, bool Filled)
	{
		if (!Filled)
		{
			DrawLine(Renderer, Point0.Position, Point1.Position, Color);
			DrawLine(Renderer, Point1.Position, Point2.Position, Color);
			DrawLine(Renderer, Point2.Position, Point0.Position, Color);
			return;
		}

		// Sort points in descending order of y
		if (Point0.Position.y > Point1.Position.y)
			std::swap(Point0, Point1);
		if (Point0.Position.y > Point2.Position.y)
			std::swap(Point0, Point2);
		if (Point1.Position.y > Point2.Position.y)
			std::swap(Point1, Point2);

		// Compute x values and intensities per edge
		auto Edge01Xs = Interpolate(Point0.Position.y, Point0.Position.x, Point1.Position.y, Point1.Position.x);
		auto Edge01Intensities = Interpolate(Point0.Position.y, Point0.Intensity, Point1.Position.y, Point1.Intensity);
		auto Edge12Xs = Interpolate(Point1.Position.y, Point1.Position.x, Point2.Position.y, Point2.Position.x);
		auto Edge12Intensities = Interpolate(Point1.Position.y, Point1.Intensity, Point2.Position.y, Point2.Intensity);
		auto Edge02Xs = Interpolate(Point0.Position.y, Point0.Position.x, Point2.Position.y, Point2.Position.x);
		auto Edge02Intensities = Interpolate(Point0.Position.y, Point0.Intensity, Point2.Position.y, Point2.Intensity);
		// Concatenate two sides
		Edge01Xs.pop_back();
		Edge01Intensities.pop_back();
		Edge01Xs.insert(Edge01Xs.end(), Edge12Xs.begin(), Edge12Xs.end());
		Edge01Intensities.insert(Edge01Intensities.end(), Edge12Intensities.begin(), Edge12Intensities.end());
		auto& X012Vals = Edge01Xs;
		auto& Intensity012Vals = Edge01Intensities;

		// Determine which side is left vs. right
		int Middle = std::floor(X012Vals.size() / 2);
		auto& XLeft = (Edge02Xs[Middle] < X012Vals[Middle]) ? Edge02Xs : X012Vals;
		auto& IntensityLeft = (Edge02Xs[Middle] < X012Vals[Middle]) ? Edge02Intensities : Intensity012Vals;
		auto& XRight = (Edge02Xs[Middle] < X012Vals[Middle]) ? X012Vals : Edge02Xs;
		auto& IntensityRight = (Edge02Xs[Middle] < X012Vals[Middle]) ? Intensity012Vals : Edge02Intensities;

		for (int y = Point0.Position.y; y <= Point2.Position.y; y++)
		{
			// Compute intensities along the row
			int X_L = XLeft[y - Point0.Position.y];
			int X_R = XRight[y - Point0.Position.y];
			auto IntensitiesHorizontal = Interpolate(X_L, IntensityLeft[y - Point0.Position.y], 
												     X_R, IntensityRight[y - Point0.Position.y]);
			for (int x = X_L; x <= X_R; x++)
				DrawPixel(Renderer, x, y, Color * IntensitiesHorizontal[x - X_L]);
		}
	}
}