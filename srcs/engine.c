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
    if (!(engine->pixels = (uint32_t *)calloc(engine->width * engine->height, sizeof(uint32_t))))
        return(NULL);
    if (!(engine->image = (Image *)malloc(sizeof(Image))))
        return(NULL);
    engine->image->data = engine->pixels;
    engine->image->width = engine->width;
    engine->image->height = engine->height;
    engine->image->mipmaps = 1;
    engine->image->format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
    engine->texture = LoadTextureFromImage(*engine->image);
    initCamera(&engine->camera, engine->width, engine->height);
    engine->scene = createScene();
    return(engine);
}

// static Vec3 sampleSquare()
// {
//     return(createVector(random_double(0.0, 1.0) - .5, random_double(0.0, 1.0) - .5, 0));
// }

t_ray    getPixelRay(Engine *engine, int x, int y)
{
    Vec3 pixel_sample = vectorAdd(engine->camera.origin_loc, vectorAdd(vectorMultD(engine->camera.pixel_deltas.pixel_delta_u, x),
                            vectorMultD(engine->camera.pixel_deltas.pixel_delta_v, y)));
    Vec3    r_dir = vectorSub(pixel_sample, engine->camera.center);
    t_ray   r = {
        .origin = engine->camera.center,
        .dir = r_dir
    };
    return(r);
}

void    raytrace(Engine *engine)
{
    for (int y = 0; y < engine->height; y++)
    {
        for (int x = 0; x < engine->width; x++)
        {
            t_color color = createVector(0, 0, 0);
            t_ray   r = getPixelRay(engine, x, y);
            color = rayColor(engine, r);
            writeColor(engine, x, y, convertToRBGA(&color));
        }
    }
}

void handleInputs(Engine *engine)
{
    t_camera *cam = &engine->camera;
    Vec3 forward = unitVector(vectorSub(cam->look_at, cam->center));
    Vec3 right = unitVector(cross(cam->up, forward));
    Vec3 up = cam->up;

    // Camera movement
    if (IsKeyDown(KEY_A)) // Move left
        moveCamera(cam, right, -.05);
    if (IsKeyDown(KEY_D)) // Move right
        moveCamera(cam, right, .05);
    if (IsKeyDown(KEY_W)) // Move forward
        moveCamera(cam, forward, .05);
    if (IsKeyDown(KEY_S)) // Move backward
        moveCamera(cam, forward, -.05);
    if (IsKeyDown(KEY_SPACE)) // Move up
        moveCamera(cam, up, .05);
    if (IsKeyDown(KEY_LEFT_SHIFT)) // Move down
        moveCamera(cam, up, -.05);

    // Camera rotation
    if (IsKeyDown(KEY_LEFT)) // Look left
        rotateCamera(cam, .005, 0);
    if (IsKeyDown(KEY_RIGHT)) // Look right
        rotateCamera(cam, -.005, 0);
    if (IsKeyDown(KEY_UP)) // Look up
        rotateCamera(cam, 0, .005);
    if (IsKeyDown(KEY_DOWN)) // Look down
        rotateCamera(cam, 0, -.005);

    // Update camera state based on new position and orientation
    updateCamera(cam, engine->width, engine->height);
}

void    render(Engine *engine)
{
    BeginDrawing();
    handleInputs(engine);
    // raytrace(engine);
    multi_thread(engine);
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

void    writeColor(Engine *engine, int x, int y, uint32_t color)
{
    int index = (y * engine->width + x);
    uint32_t *pixels = (uint32_t *)engine->image->data;
    pixels[index] = color;
}