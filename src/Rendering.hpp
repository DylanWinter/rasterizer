#include "Drawing.hpp"

struct Vertex
{
    vec3 Position;
    float Intensity = 1.0;

    Vertex(const vec3& Position, float intensity = 1.0f)
        : Position(Position), Intensity(intensity)
    {}
};

namespace Rendering 
{
    void RenderTriangle(const Vertex& V0, const Vertex& V1, const Vertex& V2, const color4& Color);
}