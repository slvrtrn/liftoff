#ifndef LIFTOFF_CONTROLS_H
#define LIFTOFF_CONTROLS_H

#include <SDL2/SDL_events.h>
#include "Ball.h"
#include "Platform.h"

class Controls {
public:

  Controls(
    Ball *ball,
    Platform *platform
  );

  ~Controls();

  void handleKeyUp(SDL_Event *event);

  void handleKeyDown(SDL_Event *event);

private:
  Ball *ball;
  Platform *platform;
};

#endif //LIFTOFF_CONTROLS_H
