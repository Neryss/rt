#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

typedef struct  s_camera
{
    double  focal_len;
    double  vp_height;
    double  vp_width;
    Vec3    center;
}               t_camera;

void    initCamera(t_camera *cam, int width, int height);

#endif