#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "engine.h"
#include "ray.h"

typedef Vec3 t_color;

t_color rayColor(t_ray r);

#endif