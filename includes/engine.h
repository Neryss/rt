#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

typedef struct s_engine
{
    int             width;
    int             height;
    char            *title;
    unsigned char   *pixels;
    Image           *image;
    Texture2D       texture;
}               Engine;

Engine  *initEngine(int width, int height, char *title);
void    freeEngine(Engine *engine);
void    generateGradient(Engine *engine);
void    render(Engine *engine);

#endif