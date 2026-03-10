#include <stdio.h>
#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Draw a number");

    SetTargetFPS(120);
    Vector2 points[1000];
    int point_count = 0;

    while(!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if(point_count < 1000)
            {
                points[point_count] = GetMousePosition();
                point_count++;
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0; i < point_count; i++)
        {
            DrawCircleV(points[i], 5, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
