#ifndef LIFTOFF_BALL_H
#define LIFTOFF_BALL_H

class Ball {

public:
  Ball(
    int gameFieldWidth,
    int gameFieldHeight,
    int pxPerBlock
  );

  ~Ball();

  void launch();

  bool getIsLaunched();

  void updateStartPos(int xPos);

private:
  const int gameFieldWidth;
  const int gameFieldHeight;

  int xStartPos;
  int yStartPos;

  bool isLaunched;

  float angle;
  int velocity;
  int r;
};

#endif //LIFTOFF_BALL_H
