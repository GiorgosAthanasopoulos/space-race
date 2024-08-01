#include <raylib.h>

#include "util.hpp"

float GetWindowWidth() { return GetRenderWidth(); }
float GetWindowHeight() { return GetRenderHeight(); }
Vector2 GetWindowSize() { return {GetWindowWidth(), GetWindowHeight()}; }

Vector2 operator*(Vector2 a, float b) { return {a.x * b, a.y * b}; }
void operator+=(Vector2 &a, Vector2 b) {
  a.x += b.x;
  a.y += b.y;
}
Vector2 operator/(Vector2 a, float b) { return {a.x / b, a.y / b}; }
Vector2 operator/(Vector2 a, Vector2 b) { return {a.x / b.x, a.y / b.y}; }
Vector2 operator*(Vector2 a, Vector2 b) { return {a.x * b.x, a.y * b.y}; }

Vector2 CalculateSpeed(float speedToWinSizeRatio) {
  return GetWindowSize() / speedToWinSizeRatio;
}
Vector2 CalculateSize(float sizeToWinSizeRatio) {
  return GetWindowSize() / sizeToWinSizeRatio;
}
Vector2 MaintainPosAfterResize(Vector2 old, Vector2 nnew, Vector2 pos) {
  return pos / old * nnew;
}

Vector2 AssertTextFitsInViewport(const char *text, int fontSize,
                                 Vector2 maxSize) {
  float textW = MeasureText(text, fontSize);

  while (textW > maxSize.x || fontSize > maxSize.y) {
    fontSize--;
    textW = MeasureText(text, fontSize);
  }

  return {textW, (float)fontSize};
}