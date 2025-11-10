#pragma once
#include <vector>
#include "Vec.hpp"  

struct Vertex
{
    vec3 Position;
    float Intensity = 1.0;

    Vertex(const vec3& Position, float intensity = 1.0f)
        : Position(Position), Intensity(intensity)
    {}
};

struct MeshData
{
    color4 Color = Colors::Red;
    std::vector<Vertex> Vertices;
    std::vector<int> Indices;  // must be a multiple of 3
};

struct MeshInstance
{
    const MeshData& Mesh;
    vec3 Position = vec3(0, 0, 0);

    MeshInstance(const MeshData& Mesh, const vec3& Position = vec3(0, 0, 0))
        : Mesh(Mesh), Position(Position)
    {}
};

struct Scene
{
    std::vector<MeshInstance> Meshes{};
};