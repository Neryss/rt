#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct  s_vec3
{
    double  e[3];
}               Vec3;

Vec3    createVector(double x, double y, double z);
Vec3    vectorAdd(Vec3 v1, Vec3 v2);
Vec3    vectorSub(Vec3 v1, Vec3 v2);
Vec3    vectorMult(Vec3 v1, Vec3 v2);
Vec3    vectorMultD(Vec3 v1, double t);
Vec3    vectorDiv(Vec3 v1, double t);
Vec3    unitVector(const Vec3 v);
Vec3    negate(Vec3 v);
double  lengthSqrd(Vec3 v);
double  length(Vec3 v);
double  dot(const Vec3 v1, const Vec3 v2);
Vec3    cross(const Vec3 v1, const Vec3 v2);

void    printVec3(const Vec3 *v);


#endif