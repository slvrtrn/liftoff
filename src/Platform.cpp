#include "Platform.h"
#include <iostream>

Platform::Platform(
  int gameFieldWidth,
  int pxPerBlock,
  int movementPerFrame,
  int blocks
) :
  gameFieldWidth(gameFieldWidth),
  movementPerFrame(movementPerFrame) {

  dims.blocks = blocks;
  dims.pxPerBlock = pxPerBlock;

  dims.height = pxPerBlock;
  dims.width = dims.blocks * pxPerBlock;

  int halfWidth = dims.width / 2;
  dims.center = gameFieldWidth / 2;

  dims.xRightEdge = dims.center + halfWidth;
  dims.xLeftEdge = dims.center - halfWidth;

  canMoveRight = true;
  canMoveLeft = true;

  movementStatus = Still;
}

PlatformDimensions *Platform::getDimensions() {
  return &dims;
}

void Platform::startMoveToLeft() {
  movementStatus = Left;
}

void Platform::startMoveToRight() {
  movementStatus = Right;
}

void Platform::stopMovement() {
  movementStatus = Still;
}

void Platform::move() {
  if (movementStatus == Left) {
    moveLeft();
    return;
  }
  if (movementStatus == Right) {
    moveRight();
    return;
  }
}

void Platform::moveLeft() {
  if (!canMoveLeft) {
    return;
  }
  canMoveRight = true;
  int nextLeftEdge = dims.xLeftEdge - movementPerFrame;
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
  int nextRightEdge = dims.xRightEdge + movementPerFrame;
  if (nextRightEdge >= gameFieldWidth) {
    dims.xRightEdge = gameFieldWidth;
    canMoveRight = false;
  } else {
    dims.xRightEdge = nextRightEdge;
  }
  dims.xLeftEdge = dims.xRightEdge - dims.width;
  dims.center = dims.xLeftEdge + (dims.width / 2);
}

PlatformMovementStatus *Platform::getMovementStatus() {
  return &movementStatus;
}

Platform::~Platform() = default;
