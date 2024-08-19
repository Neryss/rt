#include "../includes/vec3.h"

Vec3    createVector(double x, double y, double z)
{
    Vec3    v = {
        .e[0] = x,
        .e[1] = y,
        .e[2] = z
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


Vec3    vectorSub(Vec3 v1, Vec3 v2)
{
    Vec3    r = {
        .e[0] = v1.e[0] - v2.e[0],
        .e[1] = v1.e[1] - v2.e[1],
        .e[2] = v1.e[2] - v2.e[2],
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

Vec3    vectorMultD(Vec3 v1, double t)
{
    Vec3    r = {
        .e[0] = v1.e[0] * t,
        .e[1] = v1.e[1] * t,
        .e[2] = v1.e[2] * t,
    };
    return(r);
}

Vec3    vectorDiv(Vec3 v, double t)
{
    Vec3 result;
    double inv_t = 1.0 / t;  // Calculate the inverse of t
    result.e[0] = v.e[0] * inv_t;
    result.e[1] = v.e[1] * inv_t;
    result.e[2] = v.e[2] * inv_t;
    return result;
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

void    printVec3(const Vec3 *v)
{
    printf("Vec: [%f, %f, %f]\n", v->e[0], v->e[1], v->e[2]);
}

