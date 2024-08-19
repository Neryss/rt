#include <stdio.h>
#include "../includes/engine.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    Engine  *engine = NULL;

    engine = initEngine(800, 450, "This is a test");
    while (!WindowShouldClose())
    {
        render(engine);
    }
    freeEngine(engine);
    CloseWindow();
    return (0);
}