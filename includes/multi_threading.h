#ifndef MULTI_THREADING_H
#define MULTI_THREADING_H

#include <pthread.h>
#include <unistd.h>

struct s_engine;

void    multi_thread(struct s_engine *engine);

#endif
