#include "../includes/camera.h"

void    initCamera(t_camera *cam, int width, int height)
{
    // Code for the 16/9 aspect ratio I'm not using rn
    // auto aspect_ratio = 16.0 / 9.0;
    // int image_width = 400;

    // // Calculate the image height, and ensure that it's at least 1.
    // int image_height = int(image_width / aspect_ratio);
    // image_height = (image_height < 1) ? 1 : image_height;

    // // Viewport widths less than one are ok since they are real valued.
    // auto viewport_height = 2.0;
    // auto viewport_width = viewport_height * (double(image_width)/image_height);
    cam->focal_len = 1.0;
    cam->vp_height = 2.0;
    cam->vp_width = cam->vp_height * ((double)width / height);
    cam->center = createVector(0, 0, 0);

    // this might need to be recalculated evey resize and/or camera movement
    // Calculates the vectors for the horizontal and vertical viewport length
    Vec3    vp_u = createVector(cam->vp_width, 0, 0);
    Vec3    vp_v = createVector(0, -cam->vp_height, 0);

    // calculates the offset between pixels
    Vec3    pixel_delta_u = vectorDiv(vp_u, width);
    Vec3    pixel_delta_v = vectorDiv(vp_v, height);

    Vec3    vp_u_div2 = vectorDiv(vp_u, 2);
    Vec3    vp_v_div2 = vectorDiv(vp_v, 2);

    Vec3    tmp1 = vectorSub(cam->center, createVector(0, 0, cam->focal_len));
    Vec3    tmp2 = vectorSub(tmp1, vp_u_div2);
    Vec3    vp_upper_left = vectorSub(tmp2, vp_v_div2);

    // upper left pixel location
    cam->origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
    cam->pixel_deltas.pixel_delta_u = pixel_delta_u;
    cam->pixel_deltas.pixel_delta_v = pixel_delta_v;
}