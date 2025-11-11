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
    std::vector<Vertex> Vertices;
    std::vector<int> Indices;  // must be a multiple of 3
};

struct Transform
{
    vec3 Position = vec3(0, 0, 0);
    vec3 Rotation = vec3(0, 0, 0);
    vec3 Scale = vec3(1, 1, 1);
};

struct MeshInstance
{
    color4 Color = Colors::Red;
    const MeshData& Mesh;
    Transform Transform;

    MeshInstance(const MeshData& Mesh, const vec3& Position = vec3(0, 0, 0), const vec3& Rotation = vec3(0, 0, 0), const vec3& Scale = vec3(1, 1, 1))
        : Mesh(Mesh)
    {
        Transform = { Position, Rotation, Scale };
    }
};

struct Scene
{
    std::vector<MeshInstance> Meshes{};
};