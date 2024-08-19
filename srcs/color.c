#include "../includes/color.h"

t_color rayColor(t_ray r)
{
    double  hit = hit_sphere(createVector(0, 0, -1), 0.5, r);
    if (hit > 0.0)
    {
        Vec3 n = unitVector(vectorSub(at(&r, hit), createVector(0, 0, -1)));
        return (vectorMultD(createVector(n.e[0] + 1, n.e[1] + 1, n.e[2] + 1), 0.5));
    }
    // if (hit_sphere(createVector(0, 0, -1), 0.5, r))
    //     return(createVector(1, 0, 0));
    Vec3    unit_dir = unitVector(r.dir);
    // printf("unit_dir.y: %f\n", unit_dir.e[1]);
    float  a = 0.5 * (unit_dir.e[1] + 1.0);
    // printf("dir: [%f, %f, %f] %f\n", r.dir.e[0], r.dir.e[1], r.dir.e[2], a);
    return (vectorAdd(vectorMultD(createVector(1.0, 1.0, 1.0), 1.0 - a), vectorMultD(createVector(0.5, 0.7, 1.0), a)));
    // return (createVector(1.0, 0, 0));
}