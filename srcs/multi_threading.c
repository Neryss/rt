#include "../includes/multi_threading.h"
#include "../includes/engine.h"

t_threads_manager   *createThreadsManager(Engine *engine)
{
    t_threads_manager   *threads_manager = (t_threads_manager *)malloc(sizeof(t_threads_manager));
    int                 to = 0;

    if (!threads_manager)
        return NULL;
    threads_manager->avail_threads = sysconf(_SC_NPROCESSORS_ONLN);
    if (!(threads_manager->threads = (pthread_t *)malloc(sizeof(pthread_t) * threads_manager->avail_threads)))
        return NULL;
    if (!(threads_manager->args = (t_thread_args *)malloc(sizeof(t_thread_args) * threads_manager->avail_threads)))
        return NULL;
    for (int i = 0; i < threads_manager->avail_threads; i++)
    {
        threads_manager->args[i].from_to[0] = to;
        to += min(engine->height - 1, (engine->height / threads_manager->avail_threads));
        threads_manager->args[i].from_to[1] = to;
        threads_manager->args[i].id = i;
        threads_manager->args[i].engine = engine;
    }
    return (threads_manager);
}

void    *multi_raytracing(void *args)
{
    t_thread_args *handler = (t_thread_args *)args;
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

int                runThreads(t_threads_manager *manager)
{
    for (int i = 0; i < manager->avail_threads; i++)
    {
        if (pthread_create(&manager->threads[i], NULL, (void *)multi_raytracing, &manager->args[i]))
            return(1);
    }
    for (int i = 0; i < manager->avail_threads; i++)
        pthread_join(manager->threads[i], NULL);
    return(0);
}

void                freeManager(t_threads_manager *manager)
{
    free(manager->threads);
    free(manager->args);
    free(manager);
}