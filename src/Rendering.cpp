#include "Rendering.hpp"

namespace Rendering 
{
    // Project a 3D position in the world to a 2D screen space position
    ivec2 WorldPositionToCanvas(const vec3& Pos)
    {
        float ViewportX = Pos.x * ViewportDistanceFromCamera / Pos.z;
        float ViewportY = Pos.y * ViewportDistanceFromCamera / Pos.z;
        return ivec2((ViewportX * RES_X / ViewportWidth) + (RES_X / 2), (ViewportY * RES_Y / ViewportHeight) + (RES_Y / 2));
    }

    void RenderTriangle(const Vertex& V0, const Vertex& V1, const Vertex& V2, const color4& Color)
    {
        Vertex2D P0(WorldPositionToCanvas(V0.Position), V0.Intensity);
        Vertex2D P1(WorldPositionToCanvas(V1.Position), V1.Intensity);
        Vertex2D P2(WorldPositionToCanvas(V2.Position), V2.Intensity);
        Drawing::DrawTriangle(P0, P1, P2, Color, false);
    }

    void RenderMesh(const MeshInstance& Instance)
    {
        std::vector<Vertex2D> Projected = {};
        for (auto& Vertex : Instance.Mesh.Vertices)
        {
            const vec3 TransformedVertex = ApplyRotation(ApplyScale(Vertex.Position, Instance.Transform.Scale), Instance.Transform.Rotation) + Instance.Transform.Position;
            Projected.push_back(Vertex2D(WorldPositionToCanvas(TransformedVertex), Vertex.Intensity));
        }

        for (int i = 0; i < Instance.Mesh.Indices.size(); i += 3)
            Drawing::DrawTriangle(Projected[Instance.Mesh.Indices[i]], Projected[Instance.Mesh.Indices[i + 1]], Projected[Instance.Mesh.Indices[i + 2]], Instance.Color, false);
    }
}