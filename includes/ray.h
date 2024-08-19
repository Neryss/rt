#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct  s_ray
{
    Vec3    origin;
    Vec3    dir;
}               t_ray;

Vec3    at(const t_ray *r, double t);

#endif