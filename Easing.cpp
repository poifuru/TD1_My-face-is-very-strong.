#include "Easing.h"

void lerp(Vector2 start, Vector2 end, Vector2& pos, float t) {
    pos.x = (1.0f - t) * start.x + t * end.x;
    pos.y = (1.0f - t) * start.y + t * end.y;
}

float easeInExpo(float x)
{
    x = static_cast<float>(0 ? 0 : pow(2, 10 * x - 10));

    return x;
}

float easeInBack(float x) {
    const float c1 = 1.70158f;
    const float c3 = c1 + 1;

    return c3 * x * x * x - c1 * x * x;
}
