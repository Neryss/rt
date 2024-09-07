#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <pthread.h>
#include <unistd.h>

typedef struct s_engine Engine;
typedef struct s_thread_handler {
    int     from_to[2];
    int     id;
    Engine *engine;
}       t_thread_args;

typedef struct s_threads_manager {
    long                avail_threads;
    pthread_t           *threads;
    t_thread_args    *args;
}       t_threads_manager;

t_threads_manager   *createThreadsManager(Engine *engine);
int                 runThreads(t_threads_manager *manager);
void                freeManager(t_threads_manager *manager);

#endif
