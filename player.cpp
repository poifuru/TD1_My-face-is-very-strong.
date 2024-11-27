#include <Novice.h>
#include "Player.h"

Player::Player() {
	quad_.pos = { 300.0f, 868.0f };
	quad_.radius = { 32.0f, 32.0f };
	quad_.leftTop = {};
	quad_.leftBottom = {};
	quad_.rightBottom = {};
	quad_.rightTop = {};
	quad_.drawLeftTop = {};
	quad_.drawLeftBottom = {};
	quad_.drawRightBottom = {};
	quad_.drawRightTop = {};
	quad_.imagePos = { 0, 0 };
	quad_.imageWidth = 32;
	quad_.imageHeight = 32;
	quad_.image = images_.white1x1;
	quad_.color = WHITE;
	velocity_ = { 8.0f, 0.0f };
	direction_ = 1; //0が左向き　1が右向き
	isJump_ = 0;
	stickX_ = 0;
	stickY_ = 0;
	HP_ = 1000;
	invincible_ = 0;
	invincibleTimer_ = 60;

	parry_ = new Parry();
	weapon_ = new Weapon();
}

Player::~Player() {
	delete parry_;
	delete weapon_;
}

void Player::Update(const char keys[], const char preKeys[], Enemy* enemy) {
	//移動の処理
	Novice::GetAnalogInputLeft(0, &stickX_, &stickY_);
	if ((keys[DIK_A] || stickX_ < 0) && quad_.pos.x - quad_.radius.x > 0) {
		direction_ = 0;
		quad_.pos.x -= velocity_.x;
	}
	else if ((keys[DIK_D] || stickX_ > 0) && quad_.pos.x + quad_.radius.x < 1920) {
		direction_ = 1;
		quad_.pos.x += velocity_.x;
	}

	//プレイヤーの向きで半径をいじいじ
	if (direction_ == 0) {
		//quad_.radius.x = -32.0f;
		//quad_.radius.y = -32.0f;
		//weapon_->sword_.radius.x = -32.0f;
		//weapon_->sword_.radius.y = -32.0f;
		//weapon_->gun_.radius.x = -32.0f;
		//weapon_->gun_.radius.y = -32.0f;
	}
	else if (direction_ == 1) {
		//quad_.radius.x = 32.0f;
		//quad_.radius.y = 32.0f;
		//weapon_->sword_.radius.x = 32.0f;
		//weapon_->sword_.radius.y = 32.0f;
		//weapon_->gun_.radius.x = 32.0f;
		//weapon_->gun_.radius.y = 32.0f;
	}

	//ジャンプするお＾~＾
	if (!isJump_ && keys[DIK_SPACE] && !preKeys[DIK_SPACE] || !isJump_ && Novice::IsTriggerButton(0, kPadButton13)) {
		isJump_ = 1;
		velocity_.y = -20.0f;
	}
	if (isJump_) {
		velocity_.y += 0.8f;
		quad_.pos.y += velocity_.y;
	}
	//着地の調整
	if (isJump_ && velocity_.y >= 0 && quad_.leftBottom.y + 10.0f >= 900.0f) {
		quad_.pos.y = 868.0f;
		velocity_.y = 0;
		isJump_ = 0;
	}

	//パリィの処理
	parry_->Update();
	if (parry_->isParry_) {
		quad_.color = BLUE;
	}
	else {
		quad_.color = WHITE;
	}

	//攻撃処理
	if (weapon_->attackingTimer_ == 0) {
		weapon_->sword_.pos = { quad_.pos.x + (quad_.radius.x * 2.5f), quad_.pos.y };
	}
	weapon_->gun_.pos = { quad_.pos };
	for (int i = 0; i < kBulletNum; i++) {
		//撃ってない間は弾の座標をプレイヤーに合わせる
		if (!weapon_->isShot_[i]) {
			weapon_->bullet_[i].pos = { quad_.pos };
		}
	}
	weapon_->Update(enemy);

	//4頂点の座標を更新
	quad_.leftTop = { quad_.pos.x - quad_.radius.x, quad_.pos.y - quad_.radius.y };
	quad_.leftBottom = { quad_.pos.x - quad_.radius.x, quad_.pos.y + quad_.radius.y };
	quad_.rightBottom = { quad_.pos.x + quad_.radius.x, quad_.pos.y + quad_.radius.y };
	quad_.rightTop = { quad_.pos.x + quad_.radius.x, quad_.pos.y - quad_.radius.y };
}

void Player::Draw() {
	//プレイヤーの描画
	if (!invincible_) {
		Novice::DrawQuad(
			int(quad_.leftTop.x), int(quad_.leftTop.y),
			int(quad_.rightTop.x), int(quad_.rightTop.y),
			int(quad_.leftBottom.x), int(quad_.leftBottom.y),
			int(quad_.rightBottom.x), int(quad_.rightBottom.y),
			quad_.imagePos.x, quad_.imagePos.y, quad_.imageWidth, quad_.imageHeight, quad_.image, quad_.color
		);
		//武器の描画
		weapon_->Draw();
	}
	else if (invincible_ && invincibleTimer_ % 3 == 0) {
		Novice::DrawQuad(
			int(quad_.leftTop.x), int(quad_.leftTop.y),
			int(quad_.rightTop.x), int(quad_.rightTop.y),
			int(quad_.leftBottom.x), int(quad_.leftBottom.y),
			int(quad_.rightBottom.x), int(quad_.rightBottom.y),
			quad_.imagePos.x, quad_.imagePos.y, quad_.imageWidth, quad_.imageHeight, quad_.image, quad_.color
		);
		//武器の描画
		weapon_->Draw();
	}

}
	Novice::DrawQuad(
		int(quad_.leftTop.x), int(quad_.leftTop.y),
		int(quad_.rightTop.x), int(quad_.rightTop.y),
		int(quad_.leftBottom.x), int(quad_.leftBottom.y),
		int(quad_.rightBottom.x), int(quad_.rightBottom.y),
		quad_.imagePos.x, quad_.imagePos.y, quad_.imageWidth, quad_.imageHeight, quad_.image, quad_.color
	);

	//プレイヤーのHPバーの描画
	//HPバーの背景
	Novice::DrawBox(26, 926, 412, 47, 0.0f, 0x847e87FF, kFillModeSolid);

	//HPバーの描画
	Novice::DrawBox(
		32, 932,
		400, 35,
		0.0f, BLACK, kFillModeSolid
	);

	//HPバーの描画
	Novice::DrawBox(
		32, 932,
		static_cast<int>(HP_ * 0.4f), 35,
		0.0f, GREEN, kFillModeSolid
	);

	//武器の描画
	weapon_->Draw();
}
