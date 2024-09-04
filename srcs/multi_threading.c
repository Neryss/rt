#include "../includes/multi_threading.h"
#include "../includes/engine.h"

typedef struct s_thread_handler {
    int     from_to[2];
    int     id;
    Engine *engine;
}       t_thread_handler;

void    *multi_raytracing(void *args)
{
    t_thread_handler *handler = (t_thread_handler *)args;
    for (int y = handler->from_to[0]; y < handler->from_to[1]; y++)
    {
        for (int x = 0; x < handler->engine->width; x++)
        {
            t_color color = createVector(0, 0, 0);
            t_ray   r = getPixelRay(handler->engine, x, y);
            color = rayColor(handler->engine, r);
            writeColor(handler->engine, x, y, convertToRBGA(&color));
        }
    }
    return(NULL);
}

void    multi_thread(Engine *engine)
{
    // TODO: get rid of allocation here, out of the loop = less malloc->free
    long                avail_threads;
    pthread_t           *threads;
    t_thread_handler    *args;
    int                 to = 0;

    avail_threads = sysconf(_SC_NPROCESSORS_ONLN);
    // avail_threads = 4;
    if (!(threads = (pthread_t *)malloc(sizeof(pthread_t) * avail_threads)))
        return;
    if (!(args = (t_thread_handler *)malloc(sizeof(t_thread_handler) * avail_threads)))
        return;
    for (int i = 0; i < avail_threads; i++)
    {
        args[i].from_to[0] = to;
        // TODO: better check since it misses a scanline
        to += min(engine->height - 1, (engine->height / avail_threads));
        args[i].from_to[1] = to;
        args[i].id = i;
        args[i].engine = engine;
        if (pthread_create(&threads[i], NULL, (void *)multi_raytracing, &args[i]))
            return;
    }
    for (int i = 0; i < avail_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(args);
    return;
}