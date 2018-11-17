#include "Game.h"
#include "Platform.h"

#include <iostream>
#include <SDL_image.h>

using namespace std;

Game::Game(GameParams *params) :
  platformPxPerBlock(params->platformPxPerBlock),
  ballSizePx(params->ballSizePx),
  winWidth(params->winWidth),
  winHeight(params->winHeight) {

  isRunning = false;

  cout << "Initializing SDL..." << endl;

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return;
  }

  window = SDL_CreateWindow(params->title, params->xpos, params->ypos, params->winWidth, params->winHeight,
                            SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return;
  }

  ctx = SDL_GL_CreateContext(window);
  if (ctx == nullptr) {
    SDL_DestroyWindow(window);
    cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return;
  }

#ifdef __APPLE__
  // MacOSX Mojave hack to display window contents immediately
  SDL_PumpEvents();
#endif

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr) {
    SDL_DestroyWindow(window);
    cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return;
  }

  // Init ball's texture, since there is no built-in tools for circles
  SDL_Surface *surf = IMG_Load("assets/ball.png");
  ballTexture = SDL_CreateTextureFromSurface(renderer, surf);
  SDL_FreeSurface(surf);
  if (ballTexture == nullptr) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    cout << "[Ball] SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
    SDL_Quit();
    return;
  }

  cout << "SDL initialized successfully!" << endl;

  platform = new Platform(winWidth, platformPxPerBlock, 10);
  ball = new Ball(winHeight, winWidth, platformPxPerBlock);

  controls = new Controls(ball, platform);

  isRunning = true;
};

Game::~Game() = default;

bool Game::getIsRunning() {
  return isRunning;
}

void Game::handleEvents() {
  if (SDL_PollEvent(&event) != 0) {
    switch (event.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
      case SDL_KEYDOWN:
        controls->handleKeyDown(&event);
        break;
      case SDL_KEYUP:
        controls->handleKeyUp(&event);
        break;
      default:
        break;
    }
  }
}

void Game::quit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  cout << "Will now quit..." << endl;
}

void Game::render() {

  // BG
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);

  // Platform
  PlatformDimensions *dims = platform->getDimensions();
  platformRect.x = dims->xLeftEdge;
  platformRect.y = winHeight - dims->height;
  platformRect.w = dims->width;
  platformRect.h = dims->height;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &platformRect);

  // Ball: emulation of circle using the texture with some transparent pixels inside the rect
  // Start position is in the middle of the platform unless the ball is launched
  if (!ball->getIsLaunched()) {
    ballTextureDestRect.x = dims->center - (ballSizePx / 2);
    ballTextureDestRect.y = winHeight - (dims->height + ballSizePx);
    ballTextureDestRect.h = ballTextureDestRect.w = ballSizePx;
    SDL_RenderCopy(renderer, ballTexture, nullptr, &ballTextureDestRect);
  }

  // Show
  SDL_RenderPresent(renderer);
}

void Game::process() {

  platform->move();

  // Until the ball is launched, it is sticked to the middle of the platform
  // Update is required to launch the ball from the correct position
  if (!ball->getIsLaunched()) {
    PlatformDimensions *dims = platform->getDimensions();
    ball->updateStartPos(dims->width / 2);
  }
}
