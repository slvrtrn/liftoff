#include "Game.h"
#include <iostream>

using namespace std;

int main() {

  const int fps = 60;
  const Uint32 maxFrameTime = (Uint32) 1000 / fps;

  GameParams params = {
    "LiftOff!", 0, 0, 800, 600, 20, 16
  };
  Game *game = new Game(&params);

  Uint32 frameTime;
  Uint32 frameStart;
  while (game->getIsRunning()) {

    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->process();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;
    if (maxFrameTime > frameTime) {
      SDL_Delay(maxFrameTime - frameTime);
    }
  }

  game->quit();
  return 0;
}
