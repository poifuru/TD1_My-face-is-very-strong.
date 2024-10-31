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

//�I�u�W�F�N�g�̍\����
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

//�v���C���[�̕ϐ�
struct Player {
	Vector2 pos;

	//4���_
	Vector2 leftTop;
	Vector2 rightTop;
	Vector2 leftBottom;
	Vector2 rightBottom;

	Vector2 velocity;

};