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

void rotateCamera(t_camera *cam, double yaw, double pitch) {
    // Calculate the right and forward direction from camera basis vectors
    Vec3 forward = unitVector(vectorSub(cam->look_at, cam->center));
    Vec3 right = unitVector(cross(cam->up, forward));
    
    // Apply yaw (left/right) rotation around the up vector
    Vec3 new_forward = vectorAdd(vectorMultD(forward, cos(yaw)), vectorMultD(right, sin(yaw)));
    
    // Apply pitch (up/down) rotation around the right vector
    new_forward = vectorAdd(vectorMultD(new_forward, cos(pitch)), vectorMultD(cam->up, sin(pitch)));
    
    // Update the look_at vector to be the new forward direction
    cam->look_at = vectorAdd(cam->center, unitVector(new_forward));
}

void moveCamera(t_camera *cam, Vec3 direction, double amount) {
    Vec3 displacement = vectorMultD(direction, amount);
    cam->center = vectorAdd(cam->center, displacement);
    cam->look_at = vectorAdd(cam->look_at, displacement);  // Maintain look direction
}


void    initCamera(t_camera *cam, int width, int height)
{
    cam->look_at = createVector(0, 0, -1);
    cam->up = createVector(0, 1, 0);

    cam->center = createVector(-2, 2, 1);
    cam->fov = 90;
    updateCamera(cam, width, height);
}

void    updateCamera(t_camera *cam, int width, int height)
{
    cam->focal_len = length(vectorSub(cam->center, cam->look_at));
    double theta = degrees_to_radians(cam->fov);
    double h = tan(theta / 2);
    cam->vp_height = 2.0 * h * cam->focal_len;
    cam->vp_width = cam->vp_height * ((double)width / height);

    cam->w = unitVector(vectorSub(cam->center, cam->look_at));
    cam->u = unitVector(cross(cam->up, cam->w));
    cam->v = cross(cam->w, cam->u);

    // Viewport vectors
    Vec3 vp_u = vectorMultD(cam->u, cam->vp_width);
    Vec3 vp_v = vectorMultD(negate(cam->v), cam->vp_height);

    Vec3 pixel_delta_u = vectorDiv(vp_u, width);
    Vec3 pixel_delta_v = vectorDiv(vp_v, height);

    Vec3 tmp1 = vectorSub(cam->center, vectorMultD(cam->w, cam->focal_len));
    Vec3 tmp2 = vectorSub(tmp1, vectorDiv(vp_u, 2));
    Vec3 vp_upper_left = vectorSub(tmp2, vectorDiv(vp_v, 2));

    // Upper left pixel location
    cam->origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
    cam->pixel_deltas.pixel_delta_u = pixel_delta_u;
    cam->pixel_deltas.pixel_delta_v = pixel_delta_v;
}