#pragma once
#include <math.h>
#include "struct.h"
#include <Novice.h>
#include "Easing.h"

void startCutIn(Enemy* enemy);

void DrawCutIn(int ghCutIn);

void ULTUpdate(char* keys, char* preKeys,Enemy* enemy); 

void DrawBar(int ULTGo,int notULT, char* keys, char* preKeys);

int Stop(int isStop);

void resetULT();