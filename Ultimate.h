#pragma once
#include <math.h>
#include "struct.h"
#include <Novice.h>

float easeInExpo(float x);

void lerp(Vector2 start, Vector2 end, Vector2& pos, float t);

void startCutIn();

void DrawCutIn();

void ULTUpdate(char* keys, char* preKeys); 
