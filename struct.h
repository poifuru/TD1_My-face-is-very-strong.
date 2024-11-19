#pragma once
#include <Novice.h>

//構造体の宣言
struct Vector2 {
	float x;
	float y;
};

struct IntVector2 {
	int x;
	int y;
};

//画像を入れておく構造体
struct Images {
	int white1x1 = Novice::LoadTexture("./Resources./Images./white1x1.png");
};

//オブジェクトの構造体====================
struct Box {
	Vector2 pos;
	float width;
	float height;
	float angle;
	int color;
	FillMode shape;
};

struct Circle {
	Vector2 pos;
	Vector2 radius;
	float angle;
	int color;
	FillMode shape;
};

struct Quad {
	Vector2 pos;
	float radius;
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
	Vector2 rightTop;
	IntVector2 imagePos;
	int width;
	int height;
	Images image;
	int color;
};
//=====================================