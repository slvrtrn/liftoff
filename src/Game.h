#ifndef LIFTOFF_GAME_H
#define LIFTOFF_GAME_H

#include <SDL2/SDL.h>
#include "Platform.h"
#include "Ball.h"
#include "Controls.h"

struct GameParams {
  const char *title;
  int xpos;
  int ypos;
  int winWidth;
  int winHeight;
  int platformPxPerBlock;
  int ballSizePx;
  int platformBlocks;
  int platformMovementPerFrame;
};

class Game {

public:
  explicit Game(GameParams *params);

  ~Game();

  // Process game world data
  void process();

  // Display the data in the window
  void render();

  // Handle keyboard events etc
  void handleEvents();

  // Flag for the main game loop
  bool getIsRunning();

  // Destroy everything and prepare to exit 0
  void quit();

private:
  int winWidth;
  int winHeight;
  bool isRunning;

  int platformPxPerBlock;
  int platformBlocks;
  int ballSizePx;

  Platform *platform;
  Ball *ball;

  Controls *controls;

  SDL_GLContext ctx;
  SDL_Renderer *renderer;
  SDL_Window *window;
  SDL_Event event;

  SDL_Rect platformRect;
  SDL_Rect ballTextureDestRect;
  SDL_Texture *ballTexture;
};

#endif //LIFTOFF_GAME_H
