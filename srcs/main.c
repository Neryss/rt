#include <stdio.h>
#include "../includes/engine.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    for (int i = 0; i < argc; i++)
    {
        printf("arg: %s\n", argv[i]);
        if (ft_strcmp(argv[i], "-save"))
            printf("yipee");
    }
    // return (0);
    Engine  *engine = NULL;

    engine = initEngine(800, 450, "Now with more threads!");
    while (!WindowShouldClose())
    {
        render(engine);
    }
    freeEngine(engine);
    CloseWindow();
    return (0);
}