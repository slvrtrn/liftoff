#include "Ball.h"
#include <iostream>

Ball::Ball(
  int gameFieldWidth,
  int gameFieldHeight,
  int pxPerBlock
) :
  gameFieldHeight(gameFieldHeight),
  gameFieldWidth(gameFieldWidth) {

  xStartPos = gameFieldWidth / 2;
  yStartPos = pxPerBlock;
}

Ball::~Ball() = default;

void Ball::launch() {
  if (!isLaunched) {
    std::cout << "Ball is launched" << std::endl;
    isLaunched = true;
  }
}

bool Ball::getIsLaunched() {
  return isLaunched;
}

void Ball::updateStartPos(int xPos) {
  xStartPos = xPos;
}
