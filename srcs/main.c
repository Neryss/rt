#include <stdio.h>
#include "../includes/engine.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../includes/stb_image_write.h"

void    saveImage(Engine *engine, const char *filename)
{
    multi_thread(engine);
    if (!stbi_write_png(filename, engine->width, engine->height, 4, engine->pixels, 4 * engine->width))
        printf("Error during the save\n");
    else
        printf("Image save successfuly\n");
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    Engine  *engine = NULL;

    engine = initEngine(800, 450, "Now with more threads!");
    for (int i = 0; i < argc; i++)
    {
        printf("arg: %s\n", argv[i]);
        if (!ft_strcmp(argv[i], "-save"))
        {
            saveImage(engine, "test.png");
            return (1);
        }
    }
    // return (0);
    while (!WindowShouldClose())
    {
        render(engine);
    }
    freeEngine(engine);
    CloseWindow();
    return (0);
}