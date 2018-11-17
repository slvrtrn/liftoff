#include "Controls.h"

Controls::Controls(
  Ball *ball,
  Platform *platform
) :
  ball(ball),
  platform(platform) {
}

Controls::~Controls() = default;

void Controls::handleKeyUp(SDL_Event *event) {
  switch (event->key.keysym.sym) {
    case SDLK_LEFT:
    case SDLK_RIGHT:
      platform->stopMovement();
      break;
    case SDLK_SPACE:
      ball->launch();
      break;
    default:
      break;
  }
}

void Controls::handleKeyDown(SDL_Event *event) {
  switch (event->key.keysym.sym) {
    case SDLK_LEFT:
      platform->startMoveToLeft();
      break;
    case SDLK_RIGHT:
      platform->startMoveToRight();
      break;
    default:
      break;
  }
}
