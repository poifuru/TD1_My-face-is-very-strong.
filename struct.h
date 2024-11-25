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
	Vector2 drawPos;
	float width;
	float height;
	float angle;
	int color;
	FillMode shape;
};

struct Circle {
	Vector2 pos;
	Vector2 drawPos;
	Vector2 radius;
	float angle;
	int color;
	FillMode shape;
};

struct Quad {
	Vector2 pos;
	Vector2 drawPos;
	Vector2 radius;
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
	Vector2 rightTop;
	Vector2 drawLeftTop;
	Vector2 drawLeftBottom;
	Vector2 drawRightBottom;
	Vector2 drawRightTop;
	IntVector2 imagePos;
	int imageWidth;
	int imageHeight;
	Images image;
	int color;
};
//=====================================

//銃弾
struct Bullet {

};