#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "camera.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "scene.h"
#include "utils.h"

typedef Vec3 t_color;
typedef struct s_engine
{
    int             width;
    int             height;
    char            *title;
    uint32_t        *pixels;
    Image           *image;
    Texture2D       texture;
    t_camera        camera;
    t_scene         scene;
}               Engine;

Engine  *initEngine(int width, int height, char *title);
void    freeEngine(Engine *engine);
void    raytrace(Engine *engine);
void    render(Engine *engine);
void    writeColor(Engine *engine, int x, int y, uint32_t color);
void    handleInputs(Engine *engine);

#endif