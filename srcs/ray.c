#include "../includes/ray.h"

Vec3    at(const t_ray *r, double t)
{
    return (vectorAdd(r->origin, (vectorMultD(r->dir, t))));
}