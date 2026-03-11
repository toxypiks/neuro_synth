#include <stdio.h>
#include "raylib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Draw a number");

    SetTargetFPS(60);
    Vector2* points = NULL;

    while(!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            arrput(points, GetMousePosition());
        }

        if(IsKeyPressed(KEY_S))
        {
            TakeScreenshot("screenshot.png");
        }

        if(IsKeyPressed(KEY_R))
        {
            arrfree(points);
            points = NULL;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0; i < arrlen(points); i++)
        {
            DrawCircleV(points[i], 5, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
