#include <stdio.h>
#include <stdint.h>
#include "raylib.h"
#include <assert.h>
#include <errno.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

#define WIDTH 800
#define HEIGHT 600
#define FPS 60

// hack that returns the value of the argument of macro as a string
#define STR2(x) #x
#define STR(x) STR2(x)

int main()
{
    int pipefd[2];

    if (pipe(pipefd) < 0) {
        fprintf(stderr, "ERROR: could not create pipe: %s\n", strerror(errno));
        return 1;
    }

    pid_t child = fork();
    if (child < 0) {
        fprintf(stderr, "ERROR: could not fork a child: %s\n", strerror(errno));
        return 1;
    }
    if (child == 0) {
        // replace standard input of ffmpeg with the read end of the pipe (pipefd[0])
        // dup2(pipefd[READ_END], STDIN_FILENO);
        if (dup2(pipefd[READ_END], STDIN_FILENO) < 0) {
            fprintf(stderr, "ERROR: could not reopen read end of pipe as stdin: %s\n", strerror(errno));
            return 1;
        }
        close(pipefd[WRITE_END]);
        int ret = execlp("ffmpeg",
                         "ffmpeg",
                         "-loglevel", "verbose",
                         "-y",
                         "-f", "rawvideo",
                         "-pix_fmt", "rgba",
                         "-s", STR(WIDTH) "x" STR(HEIGHT),
                         "-r", STR(FPS),
                         "-an",
                         "-i", "-",
                         "-c:v", "libx264",

                         "../video_output/draw_a_cow",
                         NULL
        );
        if (ret < 0) {
            fprintf(stderr, "ERROR: could not run ffmpeg as a child process: %s\n", strerror(errno));
            return 1;
        }
        assert(0 && "unreachable");
    }

    close(pipefd[READ_END]);

    InitWindow(WIDTH, HEIGHT, "Draw something");

    SetTargetFPS(FPS);
    Vector2* points = NULL;

    while(!WindowShouldClose())
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            arrput(points, GetMousePosition());
        }
        BeginDrawing();
        ClearBackground(BLACK);

        for(int i = 0; i < arrlen(points); i++)
        {
            DrawCircleV(points[i], 5, WHITE);
        }

        EndDrawing();
        Image screen = LoadImageFromScreen();
        write(pipefd[WRITE_END], screen.data, screen.width * screen.height * 4);
        UnloadImage(screen);
    }

    CloseWindow();

    return 0;
}
