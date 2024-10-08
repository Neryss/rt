#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ray.h"
#include <stdint.h>
// For hit_record
// #include "sphere.h"

struct s_engine;

typedef Vec3 t_color;

t_color rayColor(struct s_engine *engine, t_ray r);
uint32_t    convertToRBGA(t_color *color);

#endif