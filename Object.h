#pragma once
#include "struct.h"

class IntObject{
protected:
	//メンバ変数
	IntVector2 pos_;
	IntVector2 leftTop_;
	IntVector2 leftBottom_;
	IntVector2 rightBottom_;
	IntVector2 rightTop_;
	int radius_;
	Images image;
};

class FloatObject {
protected:
	//メンバ変数
	Vector2 pos_;
	Vector2 leftTop_;
	Vector2 leftBottom_;
	Vector2 rightBottom_;
	Vector2 rightTop_;
	float radius_;
	Images image;
};

