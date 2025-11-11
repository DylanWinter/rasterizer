#pragma once
#include "Vec.hpp"

inline vec3 ApplyRotation(const vec3& Pos, const vec3& Rot)
{
    float cx = cos(Rot.x), sx = sin(Rot.x);
    float cy = cos(Rot.y), sy = sin(Rot.y);
    float cz = cos(Rot.z), sz = sin(Rot.z);

    float x1 = Pos.x;
    float y1 = Pos.y * cx - Pos.z * sx;
    float z1 = Pos.y * sx + Pos.z * cx;

    float x2 = x1 * cy + z1 * sy;
    float y2 = y1;
    float z2 = -x1 * sy + z1 * cy;

    float x3 = x2 * cz - y2 * sz;
    float y3 = x2 * sz + y2 * cz;
    float z3 = z2;

    return vec3(x3, y3, z3);
}

inline vec3 ApplyScale(const vec3& Pos, const vec3& Scale)
{
    return vec3(Pos.x * Scale.x, Pos.y * Scale.y, Pos.z * Scale.z);
}

template<typename T>
inline T DegToRad(T Deg)
{
    return Deg * static_cast<T>(3.14159265358979323846) / static_cast<T>(180);
}

template<typename T>
inline T RadToDeg(T Rad)
{
    return Rad * static_cast<T>(180) / static_cast<T>(3.14159265358979323846);
}