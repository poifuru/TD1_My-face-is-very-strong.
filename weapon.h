#pragma once
#include "Struct.h"
#include "Object.h"
#include "Player.h"

class Weapon : public Object {
public:
	//メンバ変数
	Quad bullet_;
	Quad sword_;

	int weaponMode_;
	int attack_;
	int attackingTimer_;
	int wheelScroll_;

	//コンストラクタ
	Weapon();

	//メンバ関数
	void Update(Quad* quad);
	void Draw();
};

