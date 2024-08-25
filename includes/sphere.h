#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include "stdbool.h"

typedef struct s_hit_record
{
    Vec3    point;
    Vec3    normal;
    double  t;
    bool    front_face;
}               t_hit_record;

typedef struct s_sphere
{
    Vec3    pos;
    double  radius;
}               t_sphere;


bool    hit_sphere(t_sphere *sphere, t_ray *r, double r_tmin, double r_tmax, t_hit_record *rec);
void    set_face_normal(t_hit_record *rec, t_ray *r, Vec3 *normal);
t_sphere    createSphere(Vec3   pos, double r);

#endif