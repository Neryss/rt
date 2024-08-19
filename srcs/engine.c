#include "../includes/engine.h"

Engine *initEngine(int width, int height, char *title)
{
    Engine  *engine;
    if (!(engine = malloc(sizeof(Engine))))
        return(NULL);
    engine->title = title;
    engine->width = width;
    engine->height = height;
    InitWindow(engine->width, engine->height, engine->title);
    SetTargetFPS(165);
    if (!(engine->pixels = calloc(engine->width * engine->height * 3, sizeof(unsigned char))))
        return(NULL);
    if (!(engine->image = malloc(sizeof(Image))))
        return(NULL);
    engine->image->data = engine->pixels;
    engine->image->width = engine->width;
    engine->image->height = engine->height;
    engine->image->mipmaps = 1;
    engine->image->format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
    engine->texture = LoadTextureFromImage(*engine->image);
    initCamera(&engine->camera, engine->width, engine->height);
    return(engine);
}

void    raytrace(Engine *engine)
{
    // this seems ok
    Vec3    vp_u = createVector(engine->camera.vp_width, 0, 0);
    Vec3    vp_v = createVector(0, -engine->camera.vp_height, 0);

    Vec3    pixel_delta_u = vectorDiv(vp_u, engine->width);
    Vec3    pixel_delta_v = vectorDiv(vp_v, engine->height);

    Vec3    vp_u_div2 = vectorDiv(vp_u, 2);
    Vec3    vp_v_div2 = vectorDiv(vp_v, 2);

    Vec3    tmp1 = vectorSub(engine->camera.center, createVector(0, 0, engine->camera.focal_len));
    Vec3    tmp2 = vectorSub(tmp1, vp_u_div2);
    Vec3    vp_upper_left = vectorSub(tmp2, vp_v_div2);

    Vec3    origin_loc = vectorAdd(vp_upper_left, vectorMultD(vectorAdd(pixel_delta_u, pixel_delta_v), 0.5));
    (void)origin_loc;
    for (int y = 0; y < engine->height; y++)
    {
        for (int x = 0; x < engine->width; x++)
        {
            Vec3 pixel_center = vectorAdd(origin_loc, vectorAdd(vectorMultD(pixel_delta_u, x), vectorMultD(pixel_delta_v, y)));
            Vec3 ray_dir = unitVector(vectorSub(pixel_center, engine->camera.center));
            t_ray   r = {
                .origin = engine->camera.center,
                .dir = ray_dir
            };
            t_color p_color = rayColor(r);
            writeColor(engine, x, y, p_color);
        }
    }
}

void    render(Engine *engine)
{
    BeginDrawing();
    raytrace(engine);
    UpdateTexture(engine->texture, engine->image->data);
    int fps = GetFPS();
    ClearBackground(RAYWHITE);
    DrawTextureEx(engine->texture, (Vector2){0,0}, 0.0f, 1.0f, WHITE);
    DrawText(TextFormat("FPS: %i", fps), 10, 10, 20, BLACK);
    EndDrawing();
}

void    freeEngine(Engine *engine)
{
    if (engine->pixels)
        free(engine->pixels);
    if (engine->image)
        free(engine->image);
    UnloadTexture(engine->texture);
    free(engine);
    return;
}

void    writeColor(Engine *engine, int x, int y, t_color color)
{
    int index = (y * engine->width + x) * 3;
    unsigned char *pixels = (unsigned char *)engine->image->data;
    double r = color.e[0];
    double g = color.e[1];
    double b = color.e[2];
    pixels[index] = (unsigned char)(255.999 * r);
    pixels[index + 1] = (unsigned char)(255.999 * g);
    pixels[index + 2] = (unsigned char)(255.999 * b);
    // printf("%d %d %d\n", pixels[index], pixels[index + 1], pixels[index + 2]);
}

double    hit_sphere(Vec3 center, double radius, t_ray r)
{
    Vec3 oc = vectorSub(center, r.origin);
    double a = dot(r.dir, r.dir);
    double b = -2.0 * dot(r.dir, oc);
    double c = dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    // return (discriminant >= 0);
    if (discriminant < 0)
        return (-1.0);
    else
        return ((-b - sqrt(discriminant)) / (2.0 * a));
}