#ifndef SCENE_H
#define SCENE_H

#include "sphere.h"
#include "stdlib.h"

typedef struct  s_scene
{
    t_sphere    **spheres;
}               t_scene;

t_scene     createScene();
void        freeScene(t_scene *scene);

#endif