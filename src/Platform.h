#ifndef LIFTOFF_PLATFORM_H
#define LIFTOFF_PLATFORM_H

enum PlatformMovementStatus {
  Still = 0,
  Left = 1,
  Right = 2
};

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

  /*
   * Platform size in blocks
   * So total width is just `pxPerBlock` * `blocks`
   */
  int blocks;
  int pxPerBlock;
};

class Platform {
public:

  Platform(
    int gameFieldWidth,
    int pxPerBlock,
    int movementPerFrame,
    int blocks
  );

  ~Platform();

  void move();

  PlatformDimensions *getDimensions();

  void startMoveToLeft();

  void startMoveToRight();

  void stopMovement();

  PlatformMovementStatus *getMovementStatus();

private:
  const int gameFieldWidth;
  const int movementPerFrame; // Movement in PX per frame

  PlatformDimensions dims;

  bool canMoveRight;
  bool canMoveLeft;

  PlatformMovementStatus movementStatus;

  void moveLeft();

  void moveRight();
};

#endif //LIFTOFF_PLATFORM_H
