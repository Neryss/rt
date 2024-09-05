#include "../includes/camera.h"

// static void calculateOrigin(t_camera *cam, int width, int height)
// {
//     Vec3    look_from = createVector(-2, 2, 1);
//     Vec3    look_at = createVector(0, 0, -1);
//     Vec3    up = createVector(0, 1, 0);
//     Vec3    u, v, w;

//     w = unitVector(vectorSub(cam->center, look_at));
//     u = unitVector(cross(up, w));
//     v = cross(w, u);

//     Vec3    vp_u = vectorMultD(u, cam->vp_width);
//     Vec3    vp_v = vectorMultD(negate(v), cam->vp_height);

//     // calculates the offset between pixels
//     Vec3    pixel_delta_u = vectorDiv(vp_u, width);
//     Vec3    pixel_delta_v = vectorDiv(vp_v, height);

//     Vec3 tmp1 = vectorSub(cam->center, vectorMultD(w, cam->focal_len));
//     Vec3 tmp2 = vectorSub(tmp1, vectorDiv(vp_u, 2));
//     Vec3 vp_upper_left = vectorSub(tmp2, vectorDiv(vp_v, 2));

//     // upper left pixel location
//     cam->origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
//     cam->pixel_deltas.pixel_delta_u = pixel_delta_u;
//     cam->pixel_deltas.pixel_delta_v = pixel_delta_v;
// }

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
    Vec3    look_from = createVector(-2, 2, 1);
    Vec3    look_at = createVector(0, 0, -1);
    Vec3    up = createVector(0, 1, 0);

    Vec3    u, v, w;

    cam->center = look_from;
    cam->fov = 90;
    cam->focal_len = length(vectorSub(cam->center, look_at));
    double  theta = degrees_to_radians(cam->fov);
    double  h = tan(theta/2);
    cam->vp_height = 2.0 * h * cam->focal_len;
    cam->vp_width = cam->vp_height * ((double)width / height);

    w = unitVector(vectorSub(cam->center, look_at));
    u = unitVector(cross(up, w));
    v = cross(w, u);
    // cam->sample_pp = 10;
    // cam->pixels_samples_scale = 1.0 / cam->sample_pp;

    // this might need to be recalculated evey resize and/or camera movement
    // Calculates the vectors for the horizontal and vertical viewport length
    // Vec3    vp_u = createVector(cam->vp_width, 0, 0);
    // Vec3    vp_v = createVector(0, -cam->vp_height, 0);
    Vec3    vp_u = vectorMultD(u, cam->vp_width);
    Vec3    vp_v = vectorMultD(negate(v), cam->vp_height);

    // calculates the offset between pixels
    Vec3    pixel_delta_u = vectorDiv(vp_u, width);
    Vec3    pixel_delta_v = vectorDiv(vp_v, height);

    Vec3 tmp1 = vectorSub(cam->center, vectorMultD(w, cam->focal_len));
    Vec3 tmp2 = vectorSub(tmp1, vectorDiv(vp_u, 2));
    Vec3 vp_upper_left = vectorSub(tmp2, vectorDiv(vp_v, 2));

    // Vec3    vp_u_div2 = vectorDiv(vp_u, 2);
    // Vec3    vp_v_div2 = vectorDiv(vp_v, 2);

    // Vec3    tmp1 = vectorSub(cam->center, createVector(0, 0, cam->focal_len));
    // Vec3    tmp2 = vectorSub(tmp1, vp_u_div2);
    // Vec3    vp_upper_left = vectorSub(tmp2, vp_v_div2);

    // upper left pixel location
    cam->origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
    cam->pixel_deltas.pixel_delta_u = pixel_delta_u;
    cam->pixel_deltas.pixel_delta_v = pixel_delta_v;
}

void    updateCamera(t_camera *cam, Vec3 new_pos, Vec3 look_at, int width, int height)
{
    // printf("camera update\n");
    cam->center = new_pos;
    cam->look_at = look_at;

    // Vec3    look_at = createVector(0, 0, -1);
    Vec3    up = createVector(0, 1, 0);


    Vec3    u, v, w;

    w = unitVector(vectorSub(cam->center, look_at));
    u = unitVector(cross(up, w));
    v = cross(w, u);
    // cam->sample_pp = 10;
    // cam->pixels_samples_scale = 1.0 / cam->sample_pp;

    // this might need to be recalculated evey resize and/or camera movement
    // Calculates the vectors for the horizontal and vertical viewport length
    // Vec3    vp_u = createVector(cam->vp_width, 0, 0);
    // Vec3    vp_v = createVector(0, -cam->vp_height, 0);
    Vec3    vp_u = vectorMultD(u, cam->vp_width);
    Vec3    vp_v = vectorMultD(negate(v), cam->vp_height);

    // calculates the offset between pixels
    Vec3    pixel_delta_u = vectorDiv(vp_u, width);
    Vec3    pixel_delta_v = vectorDiv(vp_v, height);

    Vec3 tmp1 = vectorSub(cam->center, vectorMultD(w, cam->focal_len));
    Vec3 tmp2 = vectorSub(tmp1, vectorDiv(vp_u, 2));
    Vec3 vp_upper_left = vectorSub(tmp2, vectorDiv(vp_v, 2));
    
    cam->origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
    cam->pixel_deltas.pixel_delta_u = pixel_delta_u;
    cam->pixel_deltas.pixel_delta_v = pixel_delta_v;
    // Vec3    vp_u = createVector(cam->vp_width, 0, 0);
    // Vec3    vp_v = createVector(0, -cam->vp_height, 0);

    // // calculates the offset between pixels
    // Vec3    pixel_delta_u = vectorDiv(vp_u, width);
    // Vec3    pixel_delta_v = vectorDiv(vp_v, height);

    // Vec3    vp_u_div2 = vectorDiv(vp_u, 2);
    // Vec3    vp_v_div2 = vectorDiv(vp_v, 2);

    // Vec3    tmp1 = vectorSub(cam->center, createVector(0, 0, cam->focal_len));
    // Vec3    tmp2 = vectorSub(tmp1, vp_u_div2);
    // Vec3    vp_upper_left = vectorSub(tmp2, vp_v_div2);

    // // upper left pixel location
    // cam->origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
    // cam->pixel_deltas.pixel_delta_u = pixel_delta_u;
    // cam->pixel_deltas.pixel_delta_v = pixel_delta_v;
}