#include "../includes/camera.h"

void    initCamera(t_camera *cam, int width, int height)
{
    cam->focal_len = 1.0;
    cam->vp_height = 2.0;
    cam->vp_width = cam->vp_height * (double)(width / height);
    cam->center = createVector(0, 0, 0);
}