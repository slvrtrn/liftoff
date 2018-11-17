#ifndef LIFTOFF_BALL_H
#define LIFTOFF_BALL_H

#include "Platform.h"

struct BallPosition {
  int x;
  int y;
};

class Ball {

public:
  Ball(
    int gameFieldWidth,
    int gameFieldHeight,
    int ballSizePx,
    Platform *platform
  );

  ~Ball();

  void launch();

  bool getIsLaunched();

  void updateStartPos();

  void move();

  BallPosition *getCurrentPosition();

private:
  Platform *platform;

  const int gameFieldWidth;
  const int gameFieldHeight;

  BallPosition startPos;
  BallPosition currentPos;

  bool isLaunched;

  int ballSizePx;
  int halfBallSizePx;
  double angle;
  int velocity;
  int r;

  void wallBounce();

  void platformBounce();
};

#endif //LIFTOFF_BALL_H
