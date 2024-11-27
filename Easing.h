#pragma once
#include "struct.h"
#include "player.h"
#include <math.h>

void lerp(Vector2 start, Vector2 end, Vector2& pos, float t);

void lerpX(float startX, float endX, float& pos, float t);

void lerpY(float startY, Vector2 end, Vector2& pos, float t);

float easeInExpo(float x);

float easeInBack(float x);


