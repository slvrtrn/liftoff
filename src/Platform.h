#ifndef LIFTOFF_PLATFORM_H
#define LIFTOFF_PLATFORM_H

struct PlatformDimensions {
  int width;
  int height;

  /*
   * X coords for the Platform
   *
   *  LE     C     RE
   *  ↓      ↓      ↓
   *  [ ][ ][ ][ ][ ]
   */
  int center;
  int xLeftEdge;
  int xRightEdge;
};

class Platform {
public:

  Platform(
    int gameFieldWidth,
    int pxPerBlock,
    int movementStep
  );

  ~Platform();

  void move();

  PlatformDimensions *getDimensions();

  void startMoveToLeft();

  void startMoveToRight();

  void stopMovement();

private:
  const int gameFieldWidth;
  const int movementStep; // Movement in PX per frame
  const int pxPerBlock;

  int blocks; // Platform size in blocks, like [ ][ ][ ][ ][ ]

  PlatformDimensions dims;

  bool canMoveRight;
  bool canMoveLeft;

  bool isMovingRight;
  bool isMovingLeft;

  void moveLeft();

  void moveRight();
};

#endif //LIFTOFF_PLATFORM_H
