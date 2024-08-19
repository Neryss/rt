#include "../includes/color.h"

t_color rayColor(t_ray r)
{
    if (hit_sphere(createVector(0, 0, -1), 0.5, r))
    {
        printf("OMG\n");
        return(createVector(1, 0, 0));
    }
    Vec3    unit_dir = unitVector(r.dir);
    // printf("unit_dir.y: %f\n", unit_dir.e[1]);
    float  a = 0.5 * (unit_dir.e[1] + 1.0);
    // printf("dir: [%f, %f, %f] %f\n", r.dir.e[0], r.dir.e[1], r.dir.e[2], a);
    return (vectorAdd(vectorMultD(createVector(1.0, 1.0, 1.0), 1.0 - a), vectorMultD(createVector(0.5, 0.7, 1.0), a)));
    // return (createVector(1.0, 0, 0));
}