#include "Rendering.hpp"


namespace Rendering 
{
    void RenderTriangle(const Vertex& V0, const Vertex& V1, const Vertex& V2, const color4& Color)
    {
        Vertex2D P0(Drawing::WorldPositionToCanvas(V0.Position), V0.Intensity);
        Vertex2D P1(Drawing::WorldPositionToCanvas(V1.Position), V1.Intensity);
        Vertex2D P2(Drawing::WorldPositionToCanvas(V2.Position), V2.Intensity);
        Drawing::DrawTriangle(P0, P1, P2, Color, false);
    }
}