#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

enum Direction { UP, DOWN, LEFT, RIGHT };

typedef struct {
  bool running;
  bool up, down, left, right, quit;
  enum Direction current;
} GameStates;

void handle_input(GameStates *state);
void print_game_states(GameStates *state);
#endif
