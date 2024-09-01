#include "../includes/color.h"
#include "../includes/engine.h"

t_color rayColor(struct s_engine *engine, t_ray r)
{
    t_hit_record    rec;
    int i = 0;
    while (engine->scene.spheres[i])
    {
        if (hit_sphere(engine->scene.spheres[i], &r, 0, INFINITY, &rec))
            return (rec.color);
            // return (vectorMultD(vectorAdd(rec.normal, createVector(1, 1, 1)), 0.5));
        i++;
    }
    // return (createVector(0, 0, 0));
    Vec3    unit_dir = unitVector(r.dir);
    float  a = 0.5 * (unit_dir.e[1] + 1.0);
    Vec3    tmp = vectorAdd(vectorMultD(createVector(1.0, 1.0, 1.0), 1.0 - a), vectorMultD(createVector(0.5, 0.7, 1.0), a));
    return (tmp);
}

uint32_t    convertToRBGA(t_color *color)
{
    uint8_t   r = (uint8_t)(255.0 * clamp(color->e[0], 0.0, 1.0));
    uint8_t   g = (uint8_t)(255.0 * clamp(color->e[1], 0.0, 1.0));
    uint8_t   b = (uint8_t)(255.0 * clamp(color->e[2], 0.0, 1.0));

    uint32_t    res = ((uint8_t) 0xFF << 24 | (b << 16) | (g << 8) | r);
    return (res);
}