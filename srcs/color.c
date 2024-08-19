#include "../includes/color.h"

t_color rayColor(t_ray r)
{
    if (hit_sphere(createVector(0, 0, -1), 0.5, r))
        return(createVector(1, 0, 0));
    Vec3    unit_dir = unitVector(r.dir);
    double  a = 0.5 * (unit_dir.e[1] + 1.0);
    return (vectorAdd(vectorMultD(createVector(1.0, 1.0, 1.0), 1.0 - a), vectorMultD(createVector(0.5, 0.7, 1.0), a)));
}