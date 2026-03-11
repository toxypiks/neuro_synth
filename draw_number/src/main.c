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

    Vector2** strokes = NULL;
    Vector2* current_stroke = NULL;

    while(!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            arrput(current_stroke, GetMousePosition());
        }

        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (current_stroke != NULL)
            {
                arrput(strokes, current_stroke);
                current_stroke = NULL;
            }
        }

        if(IsKeyPressed(KEY_S))
        {
            TakeScreenshot("screenshot.png");
        }

        if(IsKeyPressed(KEY_R))
        {
            for (int i = 0; i < arrlen(strokes); i++)
            {
                arrfree(strokes[i]);
            }
            arrfree(strokes);
            strokes = NULL;

            arrfree(current_stroke);
            current_stroke = NULL;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < arrlen(strokes); i++)
        {
            if (arrlen(strokes[i]) > 1)
                DrawLineStrip(strokes[i], arrlen(strokes[i]), WHITE);
        }

        if (current_stroke != NULL && arrlen(current_stroke) > 1)
            DrawLineStrip(current_stroke, arrlen(current_stroke), WHITE);

        EndDrawing();
    }

    for (int i = 0; i < arrlen(strokes); i++) {
        arrfree(strokes[i]);
    }
    arrfree(strokes);
    arrfree(current_stroke);

    CloseWindow();

    return 0;
}
