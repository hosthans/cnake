#include "keyboard/input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL3/SDL_video.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define SNAKE_HEAD_SIZE 20
#define SNAKE_TAIL_SIZE 16

#define MAX_TAIL 150

typedef struct {
  int r, g, b, alpha;
} Color;

typedef struct {
  int x, y;
  struct TailNode *next;
} Head;

typedef struct {
  int x, y;
  int position;
} Tail;

typedef struct TailNode {
  Tail data;
  struct TailNode *next;
} TailNode;

typedef enum { HEAD, TAIL } COMPONENTS;

#define SNAKE_HEAD_COLOR (Color){0, 200, 255, 255};
#define SNAKE_TAIL_COLOR (Color){170, 230, 250, 255};

Color get_color(COMPONENTS component) {
  switch (component) {
  case HEAD:
    return SNAKE_HEAD_COLOR;
  case TAIL:
    return SNAKE_TAIL_COLOR;
  default:
    return SNAKE_HEAD_COLOR;
  }
}

void render_component(SDL_Renderer *renderer, COMPONENTS component, int x,
                      int y, int w, int h) {
  SDL_Rect rectangle = {x, y, w, h};
  Color color = get_color(component);

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.alpha);
  SDL_RenderFillRect(renderer, &rectangle);
}

int main(void) {

  srand(time(NULL));

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *w =
      SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_INPUT_FOCUS);

  SDL_Renderer *renderer = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

  SDL_Event e;
  int run = 1;

  int random_x = rand() % (WINDOW_WIDTH + 1);
  int random_y = rand() % (WINDOW_HEIGHT + 1);

  Head head = {random_x, random_y};
  GameStates gameStates = {false, false, false, false, false, false, RIGHT};

  while (run) {

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Hintergrund schwarz
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    handle_input(&gameStates);
    print_game_states(&gameStates);

    if (gameStates.running) {
      render_component(renderer, HEAD, head.x, head.y, SNAKE_HEAD_SIZE,
                       SNAKE_HEAD_SIZE);
      switch (gameStates.current) {
      case UP:
        head.y -= 1;
        break;
      case DOWN:
        head.y += 1;
        break;
      case LEFT:
        head.x -= 1;
        break;
      case RIGHT:
        head.x += 1;
        break;
      }
    }

    if (gameStates.quit) {
      run = 0;
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);

    /*
    SDL_Rect pixel;
    pixel.x = head.x;
    pixel.y = head.y;
    pixel.w = SNAKE_TAIL_SIZE;
    pixel.h = SNAKE_TAIL_SIZE;

    SDL_Rect pixel_head;
    pixel_head.x = SNAKE_HEAD_SIZE;
    pixel_head.y = 0;
    pixel_head.w = SNAKE_HEAD_SIZE;
    pixel_head.h = SNAKE_HEAD_SIZE;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Hintergrund schwarz
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_component(renderer, TAIL, pixel);
    render_component(renderer, HEAD, pixel_head);

    // Grüner Pixel
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect pixel2 = {WINDOW_WIDTH, WINDOW_HEIGHT, 10, 10};
    SDL_RenderFillRect(renderer, &pixel2);

    SDL_RenderPresent(renderer);
    head.x += 1;
    SDL_Delay(16);

    if (gameStates.quit) {
      run = 0;
    }*/
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(w);
  SDL_Quit();
  return EXIT_SUCCESS;
}
