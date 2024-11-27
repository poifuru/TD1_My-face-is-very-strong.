#pragma once
#include "struct.h"
#include "player.h"
#include <math.h>
#define PI 3.141592653589793

void lerp(Vector2 start, Vector2 end, Vector2& pos, float t);

void lerpX(float startX, float endX, float& posX, float t);

void lerpY(float startY, float endY, float& posY, float t);

//イージングの関数
float easeInExpo(float x);

float easeInBack(float x);

float easeOutQuint(float x);

float easeInSine(float x);

float easeOutBack(float x);