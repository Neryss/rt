#include "../includes/engine.h"

Engine *initEngine(int width, int height, char *title)
{
    Engine  *engine;
    if (!(engine = malloc(sizeof(Engine))))
        return(NULL);
    engine->title = title;
    engine->width = width;
    engine->height = height;
    InitWindow(engine->width, engine->height, engine->title);
    SetTargetFPS(165);
    if (!(engine->pixels = calloc(engine->width * engine->height * 3, sizeof(unsigned char))))
        return(NULL);
    if (!(engine->image = malloc(sizeof(Image))))
        return(NULL);
    generateGradient(engine);
    engine->image->data = engine->pixels;
    engine->image->width = engine->width;
    engine->image->height = engine->height;
    engine->image->mipmaps = 1;
    engine->image->format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
    engine->texture = LoadTextureFromImage(*engine->image);
    return(engine);
}

void    generateGradient(Engine *engine)
{
    for (int y = 0; y < engine->height; y++)
    {
        for (int x = 0; x < engine->width; x++)
        {
            int index = (y * engine->width + x) * 3;
            double r = (double)x / (engine->width - 1);
            double g = (double)y / (engine->height - 1);
            double b = 0;
            engine->pixels[index] = (unsigned char)(255.999 * r);
            engine->pixels[index + 1] = (unsigned char)(255.999 * g);
            engine->pixels[index + 2] = (unsigned char)(255.999 * b);
            // printf("%d %d %d\n", engine->pixels[index], engine->pixels[index + 1], engine->pixels[index + 2]);
        }
    }
}

void    render(Engine *engine)
{
    BeginDrawing();
    UpdateTexture(engine->texture, engine->image->data);
    ClearBackground(RAYWHITE);
    DrawTextureEx(engine->texture, (Vector2){0,0}, 0.0f, 1.0f, WHITE);
    EndDrawing();
}

void    freeEngine(Engine *engine)
{
    if (engine->pixels)
        free(engine->pixels);
    if (engine->image)
        free(engine->image);
    UnloadTexture(engine->texture);
    free(engine);
    return;
}