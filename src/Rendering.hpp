#pragma once
#include "Drawing.hpp"
#include "Scene.hpp"

namespace Rendering 
{
    constexpr int ViewportWidth = 1;
    constexpr int ViewportHeight = 1;
    constexpr int ViewportDistanceFromCamera = 1;

    ivec2 WorldPositionToCanvas(const vec3& Pos);

    void RenderTriangle(const Vertex& V0, const Vertex& V1, const Vertex& V2, const color4& Color);
    void RenderMesh(const MeshInstance& Instance);
}