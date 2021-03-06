#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

// Window we'll be rendering to
SDL_Window *gWindow = NULL;

// Surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// Image shown on screen
// SDL_Surface uses CPU to render the images
SDL_Surface *gHelloWorld = NULL;

int main(int argc, char *args[]) {
  if (!init()) {
    printf("Failed to initialize\n");
  } else {
    if (!loadMedia()) {
      printf("Failed to load media\n");
    } else {
      SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
      SDL_UpdateWindowSurface(gWindow);
      SDL_Delay(2000);
    }
  }
  close();
}

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window not created! Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  gHelloWorld = SDL_LoadBMP("hello_world.bmp");
  if (gHelloWorld == NULL) {
    printf("Image not loaded! Error: %s\n", SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}
