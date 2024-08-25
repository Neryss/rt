#include "../includes/color.h"
#include "../includes/engine.h"

t_color rayColor(struct s_engine *engine, t_ray r)
{
    t_hit_record    rec;
    if (hit_sphere(&engine->sphere, &r, 0, INFINITY, &rec))
        return (vectorMultD(vectorAdd(rec.normal, createVector(1, 1, 1)), 0.5));
    Vec3    unit_dir = unitVector(r.dir);
    float  a = 0.5 * (unit_dir.e[1] + 1.0);
    return (vectorAdd(vectorMultD(createVector(1.0, 1.0, 1.0), 1.0 - a), vectorMultD(createVector(0.5, 0.7, 1.0), a)));
}