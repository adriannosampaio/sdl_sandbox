// Lightning.cpp: define o ponto de entrada para o aplicativo.
//

#include "Lightning.h"

#define SDL_MAIN_HANDLED  // insert this
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include <array>
#include <functional>
#include <iostream>
#include <memory>

void initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
}

void cleanup() {
    // close SDL
    SDL_Quit();
}

struct WindowDeleter {
    void operator()(SDL_Window* win) { SDL_DestroyWindow(win); }
};

struct RendererDeleter {
    void operator()(SDL_Renderer* rend) { SDL_DestroyRenderer(rend); }
};

class Window {
    std::unique_ptr<SDL_Window, WindowDeleter> _window;
    std::unique_ptr<SDL_Renderer, RendererDeleter> _renderer;

   public:
    Window(const std::string& title, unsigned width, unsigned height) {
        _window = std::unique_ptr<SDL_Window, WindowDeleter>(SDL_CreateWindow(
            "GAME",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            0));

        // triggers the program that controls
        // your graphics hardware and sets flags
        Uint32 render_flags = SDL_RENDERER_ACCELERATED;
        // creates a renderer to render our images
        _renderer = std::unique_ptr<SDL_Renderer, RendererDeleter>(
            SDL_CreateRenderer(_window.get(), -1, render_flags));
    }

    void clear() { SDL_RenderClear(_renderer.get()); }

    void display() { SDL_RenderPresent(_renderer.get()); }

    void render_texture_in_rectangle(
        SDL_Texture* tex, SDL_Rect rendered_object) {
        SDL_RenderCopy(_renderer.get(), tex, NULL, &rendered_object);
    }

    SDL_Renderer* get_renderer() { return _renderer.get(); }
};

int main(int argc, char* argv[]) {
    initialize();
    // returns zero on success else non-zero

    Window win = Window(std::string("GAME"), 800, 600);

    // creates a surface to load an image into the main memory
    SDL_Surface* surface;
    // please provide a path for your image
    surface = IMG_Load("C:/Users/Adrianno/Downloads/proc2.png");
    if (!surface) {
        printf("IMG_Load: %s\n", IMG_GetError());
        exit(1);
    }

    // loads image to our graphics hardware memory.
    SDL_Texture* tex =
        SDL_CreateTextureFromSurface(win.get_renderer(), surface);

    // clears main-memory
    SDL_FreeSurface(surface);

    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;

    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;

    // sets initial x-position of object
    dest.x = (1000 - dest.w) / 2;

    // sets initial y-position of object
    dest.y = (1000 - dest.h) / 2;

    // controls animation loop
    int close = 0;

    // speed of box
    int speed = 300;

    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // handling of close button
                    close = 1;
                    break;

                case SDL_KEYDOWN:
                    auto scancode = event.key.keysym.scancode;
                    if (event.key.keysym.scancode == SDL_SCANCODE_W ||
                        event.key.keysym.scancode == SDL_SCANCODE_UP)
                        dest.y -= speed / 30;
                    if (event.key.keysym.scancode == SDL_SCANCODE_S ||
                        event.key.keysym.scancode == SDL_SCANCODE_DOWN)
                        dest.y += speed / 30;
                    if (event.key.keysym.scancode == SDL_SCANCODE_A ||
                        event.key.keysym.scancode == SDL_SCANCODE_LEFT)
                        dest.x -= speed / 30;
                    if (event.key.keysym.scancode == SDL_SCANCODE_D ||
                        event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                        dest.x += speed / 30;
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000) dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0) dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000) dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0) dest.y = 0;

        // clears the screen
        win.clear();
        win.render_texture_in_rectangle(tex, dest);

        // triggers the double buffers
        // for multiple rendering
        win.display();

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }

    // destroy texture
    SDL_DestroyTexture(tex);

    cleanup();

    return 0;
}