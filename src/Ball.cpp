#include "Ball.h"
#include "Platform.h"
#include <iostream>
#include <math.h>

Ball::Ball(
  int gameFieldWidth,
  int gameFieldHeight,
  int ballSizePx,
  Platform *platform
) :
  gameFieldHeight(gameFieldHeight),
  gameFieldWidth(gameFieldWidth),
  platform(platform),
  ballSizePx(ballSizePx),
  halfBallSizePx(ballSizePx / 2) {

  // Platform starts centered, so does the ball
  startPos.x = gameFieldWidth / 2;

  // Assuming that platform block is just a square,
  // setting the start position to the middle of the circle on top of the block
  //
  //    (·)
  // [ ][ ][ ]
  int yStartPos = platform->getDimensions()->pxPerBlock + halfBallSizePx;
  startPos.y = yStartPos;
}

Ball::~Ball() = default;

void Ball::launch() {
  if (!isLaunched) {

    printf("Lift off with %d %d\n", startPos.x, startPos.y);

    currentPos.x = startPos.x;
    currentPos.y = startPos.y;

    // Ball is launched from the middle of the platform, so it goes straight up at the first time
    angle = 90.0;
    velocity = 5;
    isLaunched = true;
    std::cout << "Ball is launched" << std::endl;
  }
}

bool Ball::getIsLaunched() {
  return isLaunched;
}

void Ball::updateStartPos() {
  PlatformDimensions *dims = platform->getDimensions();
  startPos.x = dims->center;
}

void Ball::move() {
  double rads = 2 * M_PI * (angle / 360);

  double cosRes = cos(rads);
  double sinRes = sin(rads);

  int xPxTraversed = (int) cosRes * velocity;
  int yPxTraversed = (int) sinRes * velocity;

  int xNewPos = currentPos.x + xPxTraversed;
  int yNewPos = currentPos.y + yPxTraversed;

  printf("xNewPos, yNewPos %d %d\n", xNewPos, yNewPos);

  if (angle < 180.0) {
    if (gameFieldWidth < (xNewPos + halfBallSizePx)) {
      currentPos.x = gameFieldWidth - halfBallSizePx;
      wallBounce();
      return;
    }
    if (gameFieldHeight < (yNewPos + halfBallSizePx)) {
      currentPos.y = gameFieldHeight - halfBallSizePx;
      wallBounce();
      return;
    }
  } else {
    if ((xNewPos + halfBallSizePx) < 0) {
      currentPos.x = halfBallSizePx;
      wallBounce();
      return;
    }
    if ((yNewPos + halfBallSizePx) < 0) {
      currentPos.y = halfBallSizePx;
      wallBounce();
      return;
    }
  }

  currentPos.x = xNewPos;
  currentPos.y = yNewPos;
}

BallPosition *Ball::getCurrentPosition() {
  return &currentPos;
}

void Ball::wallBounce() {
  double newAngle;
  if (angle < 180.0) {
    newAngle = angle + 180;
  } else {
    newAngle = angle - 180;
  }

  printf("Wall bounce! Angle before: %lf, after: %lf", angle, newAngle);
  angle = newAngle;
}

void Ball::platformBounce() {

}
