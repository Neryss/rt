#include "../includes/vec3.h"

Vec3    createVector(double x, double y, double z)
{
    Vec3    v = {
        .e[0] = x,
        .e[1] = y,
        .e[2] = x
    };
    return(v);
}

Vec3    vectorAdd(Vec3 v1, Vec3 v2)
{
    Vec3    r = {
        .e[0] = v1.e[0] + v2.e[0],
        .e[1] = v1.e[1] + v2.e[1],
        .e[2] = v1.e[2] + v2.e[2],
    };
    return(r);
}

Vec3    vectorMult(Vec3 v1, Vec3 v2)
{
    Vec3    r = {
        .e[0] = v1.e[0] * v2.e[0],
        .e[1] = v1.e[1] * v2.e[1],
        .e[2] = v1.e[2] * v2.e[2],
    };
    return(r);
}

Vec3    vectorDiv(Vec3 v, double t)
{
    if (t != 0.0) {
        double inv_t = 1.0 / t;
        v.e[0] *= inv_t;
        v.e[1] *= inv_t;
        v.e[2] *= inv_t;
    }
    return v;
}

Vec3    unitVector(const Vec3 v)
{
    return (vectorDiv(v, length(v)));
}

Vec3  cross(const Vec3 v1, const Vec3 v2)
{
    Vec3    r = {
        .e[0] = v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
        .e[1] = v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
        .e[2] = v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
    };
    return(r);
}

double  lengthSqrd(Vec3 v)
{
    return(v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

double  length(Vec3 v)
{
    return(sqrt(lengthSqrd(v)));
}

double  dot(const Vec3 v1, const Vec3 v2)
{
    return (v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2]);
}

