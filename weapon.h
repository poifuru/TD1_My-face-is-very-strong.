#pragma once
#include "Struct.h"
#include "Object.h"

const int kBulletNum = 30;

class Weapon : public Object {
public:
	//メンバ変数
	Quad gun_;
	Quad sword_;

	int weaponMode_;

	/*剣モードの変数*/
	int attack_;
	int attackingTimer_;
	int wheelScroll_;

	/*銃モードの変数*/
	


	//コンストラクタ
	Weapon();

	//メンバ関数
	void Update();
	void Draw();
};

