#include "raylib.h"
#include "raymath.h"

#define GRAVITY 9.81f

int main(void)
{
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "projectile motion");
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    Camera2D camera = {0};

    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 0.5f;

    Vector2 ballStartPosition = {-250.0f, 0.0f};
    float ballRadius = 25.0f;

    Vector2 currentBallPosition = ballStartPosition;

    Vector2 groundPosition = {-screenWidth, ballStartPosition.y + 100};

    float startVelocity = 2.0f;
    Vector2 curVelocity = {0.0f, 0.0f};

    float time = 0.0f;
    double angle = 0.0;

    SetTargetFPS(60);

    bool started, paused = false;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER))
            started = !started;

        if (IsKeyPressed(KEY_SPACE))
            paused = !paused;

        if (IsKeyDown(KEY_A) && angle > -PI / 2)
            angle -= PI / 16;

        if (IsKeyDown(KEY_D) && angle < PI / 2)
            angle += PI / 16;

        if (IsKeyDown(KEY_W) && startVelocity < 50.0f)
            startVelocity += 2.0f;

        if (IsKeyDown(KEY_S) && startVelocity > 0.0f)
            startVelocity -= 2.0f;

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        Vector2 endPosition = (Vector2){(currentBallPosition.x + startVelocity * cos(angle)), (currentBallPosition.y + startVelocity * sin(angle))};

        DrawCircleV(currentBallPosition, ballRadius, RED);
        DrawLineEx(currentBallPosition, endPosition, 2.0f, WHITE);

        Vector2 groundSize = {screenWidth * 2, 100};
        DrawRectangleV(groundPosition, groundSize, DARKGREEN);

        if (started && !paused)
        {
            float deltaTime = GetFrameTime();

            time += deltaTime;

            currentBallPosition.x += curVelocity.x;
            currentBallPosition.y += curVelocity.y;

            bool grounded = (currentBallPosition.y + ballRadius) >= groundPosition.y;

            if (curVelocity.y < GRAVITY && !grounded)
            {
                curVelocity.y += GRAVITY * time;
            }
            else if (grounded)
            {
                curVelocity.y = 0.0f;
            }
        }
        else if (!started)
        {
            currentBallPosition = ballStartPosition;
            if (paused)
                paused = false;

            time = 0.0f;
            curVelocity.x = startVelocity * cos(angle);
            curVelocity.y = startVelocity * sin(angle);
        }

        EndMode2D();

        DrawText("PROJECTILE MOTION", 15.0f, 15.0f, 24, RED);
        DrawText(TextFormat("Starting Velocity: %.2f, Angle %.2f pi, Time: %.2f", startVelocity, angle / PI, time), 15.0f, 45.0f, 18, WHITE);
        DrawText(TextFormat("Current Velocity: (%.2f,%.2f)", curVelocity.x, curVelocity.y), 15.0f, 65.0f, 18, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}