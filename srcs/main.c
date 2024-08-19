#include <stdio.h>
#include "../includes/engine.h"

int main(int argc, char **argv)
{
    Engine  *engine = NULL;

    engine = initEngine(800, 450, "This is a test");
    SetTargetFPS(165);
    while (!WindowShouldClose())
    {
        // render();
        render(engine);
    }
    freeEngine(engine);
    CloseWindow();
    (void)argc;
    (void)argv;
    printf("Hello there!");
    return (0);
}