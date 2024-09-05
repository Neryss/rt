#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "utils.h"

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
    Vec3            look_at;
    Vec3            origin_loc;
    t_pixel_deltas  pixel_deltas;
    // int             sample_pp;
    // double          pixels_samples_scale;
    double          fov;
}               t_camera;

void    initCamera(t_camera *cam, int width, int height);
void    updateCamera(t_camera *cam, Vec3 new_pos, Vec3 look_at, int width, int height);

#endif