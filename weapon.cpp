#include "Weapon.h"
#include <Novice.h>

Weapon::Weapon() {
	gun_.pos = { 300.0f, 868.0f };
	gun_.radius = { 32.0f, 32.0f };
	gun_.leftTop = {};
	gun_.leftBottom = {};
	gun_.rightBottom = {};
	gun_.rightTop = {};
	gun_.drawLeftTop = {};
	gun_.drawLeftBottom = {};
	gun_.drawRightBottom = {};
	gun_.drawRightTop = {};
	gun_.imagePos = {};
	gun_.imageWidth = 32;
	gun_.imageHeight = 32;
	gun_.image;
	gun_.color = BLUE;

	sword_.pos = { 300.0f, 868.0f };
	sword_.radius = { 32.0f, 32.0f };
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

void Weapon::Update() {
	//プレイヤーの近くに武器をだすよ
	sword_.leftTop = { sword_.pos.x + (sword_.radius.x * 2), sword_.pos.y - sword_.radius.y };
	sword_.rightTop = { sword_.pos.x + (sword_.radius.x * 3), sword_.pos.y - sword_.radius.y };
	sword_.leftBottom = { sword_.pos.x + (sword_.radius.x * 2), sword_.pos.y + sword_.radius.y };
	sword_.rightBottom = { sword_.pos.x + (sword_.radius.x * 3), sword_.pos.y + sword_.radius.y };

	gun_.leftTop = { gun_.pos.x + (gun_.radius.x * 2), gun_.pos.y - (gun_.radius.y / 2) };
	gun_.rightTop = { gun_.pos.x + (gun_.radius.x * 4), gun_.pos.y - (gun_.radius.y / 2) };
	gun_.leftBottom = { gun_.pos.x + (gun_.radius.x * 2), gun_.pos.y + (gun_.radius.y / 2) };
	gun_.rightBottom = { gun_.pos.x + (gun_.radius.x * 4), gun_.pos.y + (gun_.radius.y / 2) };

	//==============攻撃！=================
	//武器の切り替え
	wheelScroll_ += Novice::GetWheel();
	if (wheelScroll_ == 60) {
		weaponMode_ = 0;
	}
	if (wheelScroll_ > 60) {
		wheelScroll_ = 60;
	}
	if (wheelScroll_ == -60) {
		weaponMode_ = 1;
	}
	if (wheelScroll_ < -60) {
		wheelScroll_ = -60;
	}

	//剣モードの処理
	if (weaponMode_ == 0) {
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

	//描画用に座標を更新
	sword_.drawLeftTop = { sword_.leftTop };
	sword_.drawRightTop = { sword_.rightTop };
	sword_.drawLeftBottom = { sword_.leftBottom };
	sword_.drawRightBottom = { sword_.rightBottom };

	gun_.drawLeftTop = { gun_.leftTop };
	gun_.drawRightTop = { gun_.rightTop };
	gun_.drawLeftBottom = { gun_.leftBottom };
	gun_.drawRightBottom = { gun_.rightBottom };
}

void Weapon::Draw() {
	if (weaponMode_ == 0) {
		Novice::DrawQuad(
			int(sword_.drawLeftTop.x), int(sword_.drawLeftTop.y),
			int(sword_.drawRightTop.x), int(sword_.drawRightTop.y),
			int(sword_.drawLeftBottom.x), int(sword_.drawLeftBottom.y),
			int(sword_.drawRightBottom.x), int(sword_.drawRightBottom.y),
			sword_.imagePos.x, sword_.imagePos.y, sword_.imageWidth, sword_.imageHeight,
			sword_.image.white1x1, sword_.color
		);
	}
	else if (weaponMode_ == 1) {
		Novice::DrawQuad(
			int(gun_.drawLeftTop.x), int(gun_.drawLeftTop.y),
			int(gun_.drawRightTop.x), int(gun_.drawRightTop.y),
			int(gun_.drawLeftBottom.x), int(gun_.drawLeftBottom.y),
			int(gun_.drawRightBottom.x), int(gun_.drawRightBottom.y),
			gun_.imagePos.x, gun_.imagePos.y, gun_.imageWidth, gun_.imageHeight,
			gun_.image.white1x1, gun_.color
		);
	}
}
