#pragma once
#include "struct.h"
#include "Object.h"


class Player : protected FloatObject{
public:
	//メンバ変数
	Vector2 velocity_;

	//コンストラクタ
	Player();

	//メンバ関数
	void Update(const char keys[]);
	void Draw();
};

