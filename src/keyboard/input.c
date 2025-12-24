#include "input.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <stdbool.h>

void print_game_states(GameStates *state) {
  printf("UP: %d | DOWN: %d | LEFT: %d | RIGHT: %d | QUIT: %d\n", state->up,
         state->down, state->left, state->right, state->quit);
}

void handle_input(GameStates *state) {
  SDL_Event ev;

  while (SDL_PollEvent(&ev)) {
    switch (ev.type) {
    case SDL_KEYDOWN:
      switch (ev.key.keysym.sym) {
      case SDLK_UP:
        state->up = true;
        state->current = UP;
        break;
      case SDLK_DOWN:
        state->down = true;
        state->current = DOWN;
        break;
      case SDLK_LEFT:
        state->left = true;
        state->current = LEFT;
        break;
      case SDLK_RIGHT:
        state->right = true;
        state->current = RIGHT;
        break;
      case SDLK_SPACE:
        state->running = true;
        break;
      case SDLK_ESCAPE:
        state->quit = true;
        break;
      }
      break;

    case SDL_KEYUP:
      switch (ev.key.keysym.sym) {
      case SDLK_UP:
        state->up = false;
        break;
      case SDLK_DOWN:
        state->down = false;
        break;
      case SDLK_LEFT:
        state->left = false;
        break;
      case SDLK_RIGHT:
        state->right = false;
        break;
      }
      break;

      /*case SDL_QUIT:
        state->quit = true;
        break;*/
    }
  }
}
