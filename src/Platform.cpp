#include "Platform.h"
#include <iostream>

Platform::Platform(
  int gameFieldWidth,
  int pxPerBlock,
  int movementStep
) :
  gameFieldWidth(gameFieldWidth),
  movementStep(movementStep),
  pxPerBlock(pxPerBlock) {

  blocks = 5;

  dims.height = pxPerBlock;
  dims.width = blocks * pxPerBlock;

  int halfWidth = dims.width / 2;
  dims.center = gameFieldWidth / 2;

  dims.xRightEdge = dims.center + halfWidth;
  dims.xLeftEdge = dims.center - halfWidth;

  canMoveRight = true;
  canMoveLeft = true;

  isMovingLeft = false;
  isMovingRight = false;
}

PlatformDimensions *Platform::getDimensions() {
  return &dims;
}

void Platform::startMoveToLeft() {
  isMovingLeft = true;
  isMovingRight = false;
}

void Platform::startMoveToRight() {
  isMovingLeft = false;
  isMovingRight = true;
}

void Platform::stopMovement() {
  isMovingLeft = false;
  isMovingRight = false;
}

void Platform::move() {
  if (isMovingLeft) {
    moveLeft();
    return;
  }
  if (isMovingRight) {
    moveRight();
    return;
  }
}

void Platform::moveLeft() {
  if (!canMoveLeft) {
    return;
  }
  canMoveRight = true;
  int nextLeftEdge = dims.xLeftEdge - movementStep;
  if (nextLeftEdge <= 0) {
    dims.xLeftEdge = 0;
    canMoveLeft = false;
  } else {
    dims.xLeftEdge = nextLeftEdge;
  }
  dims.xRightEdge = dims.xLeftEdge + dims.width;
  dims.center = dims.xLeftEdge + (dims.width / 2);
}

void Platform::moveRight() {
  if (!canMoveRight) {
    return;
  }
  canMoveLeft = true;
  int nextRightEdge = dims.xRightEdge + movementStep;
  if (nextRightEdge >= gameFieldWidth) {
    dims.xRightEdge = gameFieldWidth;
    canMoveRight = false;
  } else {
    dims.xRightEdge = nextRightEdge;
  }
  dims.xLeftEdge = dims.xRightEdge - dims.width;
  dims.center = dims.xLeftEdge + (dims.width / 2);
}

Platform::~Platform() = default;
