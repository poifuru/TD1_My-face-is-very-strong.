#pragma once
#include <Novice.h>

//�\���̂̐錾
struct Vector2 {
	float x;
	float y;
};

struct IntVector2 {
	int x;
	int y;
};

//�摜�����Ă����\����
struct Images {
	int white1x1 = Novice::LoadTexture("./Resources./Images./white1x1.png");
};

//�I�u�W�F�N�g�̍\����====================
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
	Vector2 radius;
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
	Vector2 rightTop;
	IntVector2 imagePos;
	int imageWidth;
	int imageHeight;
	Images image;
	int color;
};
//=====================================