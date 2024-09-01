#include "../includes/scene.h"

static t_sphere    *addSphere(Vec3 pos, double r, t_color color)
{
    t_sphere    *sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (NULL);
    sphere->pos = pos;
    sphere->radius = r;
    sphere->color = color;
    return (sphere);
}

t_scene    createScene()
{
    t_scene scene;
    scene.spheres = malloc(sizeof(t_sphere) * 4);
    scene.spheres[0] = addSphere(createVector(0, 0, -1), 0.5, createVector(1, 0, 1));
    scene.spheres[1] = addSphere(createVector(-1, 0, -1.5), 0.3, createVector(0, 0, 1));
    scene.spheres[2] = addSphere(createVector(1, 0, -2), 0.5, createVector(0, 1, 1));
    scene.spheres[3] = NULL;
    return (scene);
}

void        freeScene(t_scene *scene)
{
    int i = 0;
    while (scene->spheres[i])
    {
        free(scene->spheres[i]);
        i++;
    }
    free(scene->spheres);
}