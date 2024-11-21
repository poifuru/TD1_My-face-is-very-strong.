#include "weapon.h"
#include "player.h"
#include <Novice.h>

Weapon::Weapon(){
	bullet_.pos = {};
	bullet_.leftTop = {};
	bullet_.leftBottom = {};
	bullet_.rightBottom = {};
	bullet_.rightTop = {};
	bullet_.imagePos = {};
	bullet_.imageWidth = 32;
	bullet_.imageHeight = 32;
	bullet_.image;
	bullet_.color = WHITE;

	sword_.pos = {};
	sword_.leftTop = {};
	sword_.leftBottom = {};
	sword_.rightBottom = {};
	sword_.rightTop = {};
	sword_.drawLeftTop = {};
	sword_.drawLeftBottom = {};
	sword_.drawRightBottom = {};
	sword_.drawRightTop = {};
	sword_.imagePos = {};
	sword_.imageWidth = 32;
	sword_.imageHeight = 32;
	sword_.image;
	sword_.color = RED;

	weaponMode_ = 0; //0が剣　1が銃
	wheelScroll_ = 60;
	attack_ = 0;
	attackingTimer_ = 0;
}

void Weapon::Update(){
	//==============攻撃！=================
	//武器の切り替え
	wheelScroll_ += Novice::GetWheel();
	if (wheelScroll_ < 60) {
		weaponMode_ = 1;
		wheelScroll_ = -60;
	}
	else if (wheelScroll_ > 60) {
		weaponMode_ = 0;
		wheelScroll_ = 60;
	}

	//剣モードの処理
	if (weaponMode_ == 0) {
		//武器をプレイヤーの近くに出すよ
		sword_.pos = { quad_.pos.x + quad_.radius.x, quad_.pos.y };
		sword_.leftTop = { quad_.pos.x - quad_.radius.x, quad_.pos.y - quad_.radius.y };
		sword_.rightTop = { quad_.pos.x + quad_.radius.x, quad_.pos.y - quad_.radius.y };
		sword_.leftBottom = { quad_.pos.x - quad_.radius.x, quad_.pos.y + quad_.radius.y };
		sword_.rightBottom = { quad_.pos.x + quad_.radius.x, quad_.pos.y + quad_.radius.y };
		sword_.drawLeftTop = { sword_.leftTop };
		sword_.drawRightTop = { sword_.rightTop };
		sword_.drawRightBottom = { sword_.rightBottom };
		sword_.drawLeftBottom = { sword_.leftBottom };

		//連続攻撃の状態(受付時間を過ぎたら自動的に1段目の攻撃からになる)
		if (attack_ == 0 && Novice::IsTriggerMouse(0)) {
			attack_ = 1;
			attackingTimer_ = 60;
		}
		else if (attack_ == 1 && Novice::IsTriggerMouse(0) && attackingTimer_ <= 30) {
			attack_ = 2;
			attackingTimer_ = 60;
		}
		else if (attack_ == 2 && Novice::IsTriggerMouse(0) && attackingTimer_ <= 30) {
			attack_ = 3;
			attackingTimer_ = 60;
		}
		if (attack_ >= 1 && attackingTimer_ == 0) {
			attack_ = 0;
		}

		//連続攻撃一個一個の処理
		if (attack_ == 1) {
			attackingTimer_--;
		}
		else if (attack_ == 2) {
			attackingTimer_--;
		}
		else if (attack_ == 3) {
			attackingTimer_--;
		}
	}
	//銃モードの処理
	else if (wheelScroll_ == 1) {

	}
}

void Weapon::Draw(){
	if (weaponMode_ == 0) {
		Novice::DrawQuad(
			int(sword_.drawLeftTop.x), int(sword_.drawLeftTop.y),
			int(sword_.drawRightTop.x), int(sword_.drawRightTop.y),
			int(sword_.drawRightBottom.x), int(sword_.drawRightBottom.y),
			int(sword_.drawLeftBottom.x), int(sword_.drawLeftBottom.y),
			sword_.imagePos.x, sword_.imagePos.y, sword_.imageWidth, sword_.imageHeight,
			sword_.image.white1x1, sword_.color
		);
	}
	else if (weaponMode_ == 1) {

	}
}
