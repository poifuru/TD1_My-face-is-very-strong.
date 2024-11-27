#include "Easing.h"

void lerp(Vector2 start, Vector2 end, Vector2& pos, float t) {
    pos.x = (1.0f - t) * start.x + t * end.x;
    pos.y = (1.0f - t) * start.y + t * end.y;
}

void lerpX(float startX, float endX, float& posX, float t) {
    posX = (1.0f - t) * startX + t * endX;
}

void lerpY(float startY, float endY, float& posY, float t) {
    posY = (1.0f - t) * startY + t * endY;
}

float easeInExpo(float x) {
    x = static_cast<float>(0 ? 0 : pow(2, 10 * x - 10));

    return x;
}

float easeInBack(float x) {
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;

    return c3 * x * x * x - c1 * x * x;
}

float easeOutQuint(float x) {
    return 1 - float(pow(1 - x, 5));
}

float easeInSine(float x) {
    return 1 - cosf((x * float(PI)) / 2);
}
