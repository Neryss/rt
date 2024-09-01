#include "../includes/sphere.h"

t_sphere    createSphere(Vec3   pos, double r, t_color color)
{
    t_sphere    sphere = {
        pos = pos,
        r = r,
        color = color
    };
    return (sphere);
}

void    set_face_normal(t_hit_record *rec, t_ray *r, Vec3 *normal)
{
    rec->front_face = dot(r->dir, *normal) < 0;
    rec->normal = rec->front_face ? *normal : vectorSub(createVector(0, 0, 0), *normal);
}

bool    hit_sphere(t_sphere *sphere, t_ray  *r, double r_tmin, double r_tmax, t_hit_record *rec)
{
    Vec3 oc = vectorSub(sphere->pos, r->origin);
    double a = lengthSqrd(r->dir);
    double b = dot(r->dir, oc);
    double c = lengthSqrd(oc) - sphere->radius * sphere->radius;
    double discriminant = b*b - a*c;
    if (discriminant < 0)
        return (false);
    double  sqrtd = sqrt(discriminant);
    double  root = (b - sqrtd) / a;
    if (root <= r_tmin || r_tmax <= root)
    {
        root = (b + sqrtd) / a;
        if (root <= r_tmin || r_tmax <= root)
            return (false);
    }
    rec->t = root;
    rec->point = at(r, rec->t);
    rec->normal = unitVector(vectorDiv(vectorSub(rec->point, sphere->pos), sphere->radius));

    Vec3    light_dir = unitVector(createVector(-1, -1, -1));

    float   d = maxd(dot(rec->normal, negate(light_dir)), 0.0);

    rec->color = vectorMultD(sphere->color, d);

    set_face_normal(rec, r, &rec->normal);
    return (true);
}