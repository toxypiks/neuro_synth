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

    // drawing area
    const int canvas_size = 280;
    Rectangle canvas_rect = {260, 85, canvas_size, canvas_size};

    RenderTexture2D canvas = LoadRenderTexture(canvas_size, canvas_size);

    BeginTextureMode(canvas);
    ClearBackground(BLACK);
    EndTextureMode();

    Vector2** strokes = NULL;
    Vector2* current_stroke = NULL;

    size_t screenshot_index = 0;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // drawing
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mouse, canvas_rect))
            {
                Vector2 canvas_pos = {
                    mouse.x - canvas_rect.x,
                    mouse.y - canvas_rect.y
                };

                arrput(current_stroke, canvas_pos);

                // draw on canvas
                if (arrlen(current_stroke) > 1)
                {
                    BeginTextureMode(canvas);

                    float thickness = 10.0f;

                    DrawLineEx(
                        current_stroke[arrlen(current_stroke)-2],
                        current_stroke[arrlen(current_stroke)-1],
                        thickness,
                        WHITE
                    );

                    EndTextureMode();
                }
            }
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            if (current_stroke != NULL)
            {
                arrput(strokes, current_stroke);
                current_stroke = NULL;
            }
        }

        // screenshot (28x28 export)
        if (IsKeyPressed(KEY_S))
        {
            Image img = LoadImageFromTexture(canvas.texture);

            ImageFlipVertical(&img);
            ImageResize(&img, 28, 28);
            ImageColorGrayscale(&img);

            char buffer[256];
            sprintf(buffer, "digit_%zu.png", screenshot_index);

            ExportImage(img, buffer);
            UnloadImage(img);

            screenshot_index++;
        }

        // reset
        if (IsKeyPressed(KEY_R))
        {
            BeginTextureMode(canvas);
            ClearBackground(BLACK);
            EndTextureMode();

            for (int i = 0; i < arrlen(strokes); i++)
                arrfree(strokes[i]);

            arrfree(strokes);
            strokes = NULL;

            arrfree(current_stroke);
            current_stroke = NULL;
        }

        // rendering
        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawText("Draw a digit", 20, 20, 20, WHITE);
        DrawText("S = Save 28x28", 20, 50, 20, WHITE);
        DrawText("R = Reset", 20, 80, 20, WHITE);

        DrawRectangleLines(canvas_rect.x-1, canvas_rect.y-1, canvas_rect.width+2, canvas_rect.height+2, WHITE);

        DrawTexturePro(
            canvas.texture,
            (Rectangle){0, 0, canvas_size, -canvas_size},
            canvas_rect,
            (Vector2){0,0},
            0,
            WHITE
        );

        EndDrawing();
    }

    for (int i = 0; i < arrlen(strokes); i++)
        arrfree(strokes[i]);

    arrfree(strokes);
    arrfree(current_stroke);

    UnloadRenderTexture(canvas);
    CloseWindow();

    return 0;
}
