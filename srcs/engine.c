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
    engine->sphere = createSphere(createVector(0, 0, -1), 0.5);
    engine->scene = createScene();
    return(engine);
}

static Vec3 sampleSquare()
{
    return(createVector(random_double(0.0, 1.0) - .5, random_double(0.0, 1.0) - .5, 0));
}

static t_ray    getPixelRay(Engine *engine, int x, int y)
{
    Vec3    offset = sampleSquare();
    // printf("%f%f%f\n", offset.e[0], offset.e[1], offset.e[2]);
    // Vec3 pixel_sample = vectorAdd(
    //     vectorAdd(engine->camera.origin_loc, vectorMultD(engine->camera.pixel_deltas.pixel_delta_u, (x + offset.e[0]))),
    //     vectorMultD(engine->camera.pixel_deltas.pixel_delta_v, (y + offset.e[1]))
    // );
    Vec3 pixel_sample = vectorAdd(engine->camera.origin_loc, vectorAdd(vectorMultD(engine->camera.pixel_deltas.pixel_delta_u, x + offset.e[0]),
                            vectorMultD(engine->camera.pixel_deltas.pixel_delta_v, y + offset.e[1])));
    Vec3    r_dir = vectorSub(pixel_sample, engine->camera.center);
    t_ray   r = {
        .origin = engine->camera.center,
        .dir = r_dir
    };
    return(r);
    // Vec3 ray_dir = (vectorSub(pixel_center, engine->camera.center));
    // t_ray   r = {
    //     .origin = engine->camera.center,
    //     .dir = ray_dir
    // };
    // return(r);
}

void    raytrace(Engine *engine)
{
    for (int y = 0; y < engine->height; y++)
    {
        for (int x = 0; x < engine->width; x++)
        {
            t_color color = createVector(0, 0, 0);
            for (int sample = 0; sample < engine->camera.sample_pp; sample++)
            {
                t_ray   r = getPixelRay(engine, x, y);
                color = vectorAdd(color, rayColor(engine, r));
            }
            writeColor(engine, x, y, vectorMultD(color, engine->camera.pixels_samples_scale));
        }
    }
}

void    handleInputs(Engine *engine)
{
    Vec3    new_pos = engine->camera.center;
    if (IsKeyDown(KEY_A))
        new_pos.e[0] -= 0.05;
    if (IsKeyDown(KEY_D))
        new_pos.e[0] += 0.05;
    if (IsKeyDown(KEY_W))
        new_pos.e[2] -= 0.05;
    if (IsKeyDown(KEY_S))
        new_pos.e[2] += 0.05;
    if (IsKeyDown(KEY_SPACE))
        new_pos.e[1] += 0.05;
    if (IsKeyDown(KEY_LEFT_SHIFT))
        new_pos.e[1] -= 0.05;
    updateCamera(&engine->camera, new_pos, engine->width, engine->height);
}

void    render(Engine *engine)
{
    BeginDrawing();
    handleInputs(engine);
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
    freeScene(&engine->scene);
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
    // printf("Color: %f %f %f\n", r, g, b);
    pixels[index] = (unsigned char)(255.999 * clamp(r, 0.000, 0.999));
    pixels[index + 1] = (unsigned char)(255.999 * clamp(g, 0.000, 0.999));
    pixels[index + 2] = (unsigned char)(255.999 * clamp(b, 0.000, 0.999));
    // pixels[index] = (unsigned char)(255.999 * r);
    // pixels[index + 1] = (unsigned char)(255.999 * g);
    // pixels[index + 2] = (unsigned char)(255.999 * b);
    // printf("%d %d %d\n", pixels[index], pixels[index + 1], pixels[index + 2]);
    // printf("%d %d %d\n", pixels[index], pixels[index + 1], pixels[index + 2]);
}