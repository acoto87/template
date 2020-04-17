#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __GNUC__
// this is to silence GCC about this warning since nanovg is full of them
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
#endif

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>

#if __DEBUG__
#include <execinfo.h>
#endif

// #define NDEBUG // define this to deactivate assertions
#include <assert.h>

// Guide to predefined macros in C compilers gcc, clang, msvc, etc.
// https://blog.kowalczyk.info/article/j/guide-to-predefined-macros-in-c-compilers-gcc-clang-msvc-etc..html
#include <glad/glad.h>

#define GLFW_DLL
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "nanovg/nanovg.c"
#define NVG_DISABLE_CULL_FACE
#define NANOVG_GLES2_IMPLEMENTATION
#include "nanovg/nanovg_gl.h"
#include "nanovg/nanovg_gl_utils.h"

// https://github.com/dr-soft/miniaudio
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb/stb_image_resize.h"

#include "shl/array.h"
#include "shl/list.h"
#include "shl/queue.h"
#include "shl/binary_heap.h"
#include "shl/map.h"
#include "shl/set.h"
#define SHL_MEMORY_BUFFER_IMPLEMENTATION
#include "shl/memory_buffer.h"
#define SHL_WAVE_WRITER_IMPLEMENTATION
#include "shl/wave_writer.h"

#include "mutex.h"
#include "log.h"
#include "utils.h"
#include "math.h"
#include "io.h"
#include "glutils.h"
#include "types.h"
#include "game.h"
#include "audio.c"
#include "render.c"
#include "sprites.c"
#include "game.c"

void glfwErrorCallback(int error, const char* description)
{
    logError("Error: %d, %s\n", error, description);
}

int main()
{
    srand(time(NULL));

    initLog(LOG_SEVERITY_DEBUG);

    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        logError("Error initializing GLFW!\n");
        return -1;
    }

    GameContext context = {0};
    if (!initGame(&context))
    {
        logError("Can't initialize the game!\n");
        return -1;
    }

    glfwSetWindowUserPointer(context.window, &context);
    glfwSetCharCallback(context.window, inputCharCallback);

    while (!glfwWindowShouldClose(context.window))
    {
        sprintf(context.windowTitle, "Game: %.2fs at %d fps (%.4fs)", context.time, context.fps, context.deltaTime);
        glfwSetWindowTitle(context.window, context.windowTitle);

        inputGame(&context);
        updateGame(&context);
        renderGame(&context);
        presentGame(&context);
    }

    ma_device_uninit(&context.sfx);
    nvgDeleteGLES2(context.gfx);
    glfwDestroyWindow(context.window);
    glfwTerminate();
	return 0;
}
