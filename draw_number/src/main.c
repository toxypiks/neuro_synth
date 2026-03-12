#include <stdio.h>
#include "raylib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Draw a number");

    SetTargetFPS(60);

    Vector2** strokes = NULL;
    Vector2* current_stroke = NULL;
    size_t screenshot_index = 0;

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
            Image img = LoadImageFromScreen();
            ImageResize(&img, 28, 28);
            ImageColorGrayscale(&img);
            char buffer[256];
            sprintf(buffer, "screenshot_%d.png", screenshot_index);
            ExportImage(img, buffer);
            UnloadImage(img);
            screenshot_index++;
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

        float thickness = 20.0f;

        for (int i = 0; i < arrlen(strokes); i++)
        {
            for (int j = 1; j < arrlen(strokes[i]); j++)
            {
                DrawLineEx(strokes[i][j-1], strokes[i][j], thickness, WHITE);
            }
        }

        if (current_stroke != NULL)
        {
            for (int j = 1; j < arrlen(current_stroke); j++)
            {
                DrawLineEx(current_stroke[j-1], current_stroke[j], thickness, WHITE);
            }
        }

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
