#include "cgui/cgui.h"
#include <cstdio>
#include "GL/gl.h"
#include "GrDirectContext.h"
#include "GrGLInterface.h"
#include "SkCanvas.h"
#include "SkData.h"
#include "SkImage.h"
#include "SkStream.h"
#include "SkSurface.h"
#include "SDL.h"

static
void render(SkCanvas* canvas) {
    SkPaint paint;
    paint.setAntiAlias(true);
    SkRect rect = SkRect::MakeXYWH(10.0f, 10.0f, 100.0f, 100.0f);
    canvas->drawRoundRect(rect, 20.0f, 20.0f, paint);
}

static
int render(SDL_Window* window) {
    sk_sp<GrDirectContext> grContext(GrDirectContext::MakeGL());
    SkASSERT(grContext);
    GrGLint fbInfoId;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbInfoId);
    GrGLFramebufferInfo fbInfo;
    fbInfo.fFBOID = (GrGLuint) fbInfoId;
    fbInfo.fFormat = GL_RGB8;
    int pxWidth, pxHeight;
    SDL_GL_GetDrawableSize(window, &pxWidth, &pxHeight);
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    float horizontalDpi, verticalDpi;
    if (SDL_GetDisplayDPI(displayIndex, nullptr, &horizontalDpi,
        &verticalDpi) != 0) {
        fprintf(stderr, "SDL_GetDisplayDPI failed: %s\n", SDL_GetError());
        return -1;
    }
    GrBackendRenderTarget renderTarget(pxWidth, pxHeight, 0, 8, fbInfo);
    sk_sp<SkSurface> surface(
        SkSurface::MakeFromBackendRenderTarget(grContext.get(), renderTarget,
            kBottomLeft_GrSurfaceOrigin, kRGB_888x_SkColorType, nullptr,
            nullptr));
    SkASSERT(surface);
    SkCanvas* canvas = surface->getCanvas();
    canvas->scale(
        SkFloatToScalar(horizontalDpi / 96.0f),
        SkFloatToScalar(verticalDpi / 96.0f));
    canvas->clear(SK_ColorWHITE);
    render(canvas);
    canvas->flush();
    SDL_GL_SwapWindow(window);
    return 0;
}

static
int run(SDL_Window* window) {
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN: {
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                }
                case SDL_QUIT: {
                    running = false;
                    break;
                }
            }
        }
        int result = render(window);
        if (result != 0) {
            return result;
        }
    }
    return 0;
}

static
int initGLContext(SDL_Window* window) {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        return -1;
    }
    int result = run(window);
    SDL_GL_DeleteContext(glContext);
    return result;
}

static
int initWindow() {
    SDL_Window* window = SDL_CreateWindow(
        "cgui",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (window == nullptr) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return -1;
    }
    int result = initGLContext(window);
    SDL_DestroyWindow(window);
    return result;
}

int init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }
    int result = initWindow();
    SDL_Quit();
    return result;
}
