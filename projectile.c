#include "raylib.h"
#include "raymath.h"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    const float GRAVITY = -9.81f;

    InitWindow(screenWidth, screenHeight, "projectile motion");
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Camera2D camera = {0};

    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 1.0f;

    Vector2 ballPosition = {-250.0f, 0.0f};
    Vector2 currentBalLPosition = ballPosition;

    float startVelocity = 2.0f;
    Vector2 curVelocity = {0.0f, 0.0f};

    curVelocity.x = startVelocity;
    curVelocity.y = startVelocity;

    float time = 0.0f;
    double angle = 0.0;

    SetTargetFPS(60);

    bool started = false;

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_ENTER))
            started = !started;

        if (IsKeyDown(KEY_A) && angle > -asin(1.0))
            angle -= 0.1;

        if (IsKeyDown(KEY_D) && angle < asin(1.0))
            angle += 0.1;

        if (IsKeyDown(KEY_W) && startVelocity < 100.0f)
            startVelocity += 5.0f;

        if (IsKeyDown(KEY_S) && startVelocity > 5.0f)
            startVelocity -= 5.0f;

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        Vector2 endPosition = (Vector2){currentBalLPosition.x + (startVelocity * cos(angle)), currentBalLPosition.y + (startVelocity * sin(angle))};

        DrawCircleV(currentBalLPosition, 15.0f, RED);
        DrawLineEx(currentBalLPosition, endPosition, 2.0f, WHITE);

        if (started)
        {
            float deltaTime = GetFrameTime();

            time += deltaTime;

            // ballPosition.x += curVelocity.x;
            currentBalLPosition.y -= curVelocity.y;

            if (curVelocity.y > GRAVITY)
                curVelocity.y += startVelocity + GRAVITY * time;
        }

        EndMode2D();

        DrawText("PROJECTILE MOTION", 15.0f, 15.0f, 24, RED);
        DrawText(TextFormat("Velocity: %.2f, Angle %.2f, Time: %.2f", startVelocity, angle, time), 15.0f, 45.0f, 18, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}