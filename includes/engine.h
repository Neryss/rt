#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "camera.h"
typedef struct s_engine
{
    int             width;
    int             height;
    char            *title;
    unsigned char   *pixels;
    Image           *image;
    Texture2D       texture;
    t_camera          camera;
}               Engine;

Engine  *initEngine(int width, int height, char *title);
void    freeEngine(Engine *engine);
void    raytrace(Engine *engine);
void    render(Engine *engine);

#endif