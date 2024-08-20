#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

typedef struct  s_pixel_deltas
{
    Vec3    pixel_delta_u;
    Vec3    pixel_delta_v;
}               t_pixel_deltas;
typedef struct  s_camera
{
    double          focal_len;
    double          vp_height;
    double          vp_width;
    Vec3            center;
    Vec3            origin_loc;
    t_pixel_deltas  pixel_deltas;
}               t_camera;

void    initCamera(t_camera *cam, int width, int height);

#endif