#include "hud.h"

void DrawHud(char* keys, int A[2], int D[2], int Q[2], int SPACE[2],int weponGuide/*, int num*/)
{
	if (keys[DIK_A]) {
		Novice::DrawSprite(620, 958, A[1], 1.0f, 1.0f, 0.0f, WHITE);
	} else {
		Novice::DrawSprite(620, 958, A[0], 1.0f, 1.0f, 0.0f, WHITE);
	}

	if (keys[DIK_SPACE]) {
		Novice::DrawSprite(714, 958, SPACE[1], 1.0f, 1.0f, 0.0f, WHITE);
	} else {
		Novice::DrawSprite(714, 958, SPACE[0], 1.0f, 1.0f, 0.0f, WHITE);
	}
	if (keys[DIK_D]) {
		Novice::DrawSprite(1000, 958, D[1], 1.0f, 1.0f, 0.0f, WHITE);
	} else {
		Novice::DrawSprite(1000, 958, D[0], 1.0f, 1.0f, 0.0f, WHITE);
	}
	if (keys[DIK_Q]) {
		Novice::DrawSprite(502, 1030, Q[1], 0.8f, 0.8f, 0.0f, WHITE);
	} else {
		Novice::DrawSprite(502, 1030, Q[0], 0.8f, 0.8f, 0.0f, WHITE);
	}

	Novice::DrawSprite(1100, 900, weponGuide, 1.0f, 1.0f, 0.0f, WHITE);

	//Novice::DrawSprite(0, 0, Num, 1.0f / 9.0f, 1.0f, 0.0f, WHITE);

}
