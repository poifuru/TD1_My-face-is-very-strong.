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

//オブジェクトの構造体
struct Circle {
	Vector2 pos;
	Vector2 radius;
	float angle;
	int color;
	FillMode shape;
};

struct Box {
	Vector2 pos;
	float width;
	float height;
	float angle;
	int color;
	FillMode shape;
};

//プレイヤーの変数
struct Player {
	Vector2 pos;

	//4頂点
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;

	Vector2 velocity;

};