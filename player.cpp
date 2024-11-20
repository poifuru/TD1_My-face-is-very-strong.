#include <Novice.h>
#include "player.h"

Player::Player(){
	quad_.pos = { 300.0f, 868.0f };
	quad_.radius = { 32.0f, 32.0f };
	quad_.leftTop;
	quad_.leftBottom;
	quad_.rightBottom;
	quad_.rightTop;
	quad_.imagePos = { 0, 0 };
	quad_.imageWidth = 32;
	quad_.imageHeight = 32;
	quad_.color = WHITE;
	velocity_ = { 8.0f, 0.0f };
	color_ = WHITE;
	isParry_ = 0;
	parryFlame_ = 12;
	isJump_ = 0;
	stickX_ = 0;
	stickY_ = 0;

	attack_ = none;
	attackingTimer_ = 15;
	weapon_ = new Weapon();
}

Player::~Player(){
	delete weapon_;
}

void Player::Update(const char keys[], const char preKeys[]) {
	//移動の処理
	Novice::GetAnalogInputLeft(0, &stickX_, &stickY_);
	if (keys[DIK_A] || stickX_ < 0) {
		quad_.pos.x -= velocity_.x;
	}
	else if (keys[DIK_D] || stickX_ > 0) {
		quad_.pos.x += velocity_.x;
	}

	//==============攻撃！=================
	//武器の切り替え
	weapon_->wheelScroll_ += Novice::GetWheel();
	if (weapon_->wheelScroll_ < 60) {
		weapon_->wheelScroll_ = -60;
	}
	else if (weapon_->wheelScroll_ > 60) {
		weapon_->wheelScroll_ = 60;
	}

	//剣モードの処理
	if (weapon_->wheelScroll_ <= 0) {
		//武器をプレイヤーの近くに出すよ
		weapon_->sword_.leftTop = { quad_.pos.x + quad_.radius.x, quad_.pos.y + quad_.radius.y };
		// weapon_->sword_.rihgtTop = {}

		if (attack_ == 0 && Novice::IsTriggerMouse(0)) {
			attack_ = 1;
		}
		else if (attack_ == 1 && Novice::IsTriggerMouse(0)) {
			attack_ = 2;
		}
		else if (attack_ == 2 && Novice::IsTriggerMouse(0)) {
			attack_ = 3;
		}
	}
	//銃モードの処理
	else if (weapon_->wheelScroll_ >= 0) {

	}

	//パリィの処理
	if (!isParry_ && Novice::IsTriggerMouse(1) == 1 ||	!isParry_ && Novice::IsTriggerButton(0, kPadButton10)) {
		isParry_ = 1;
		color_ = BLUE;
	}
	if (isParry_) {
		parryFlame_--;
	}
	if (parryFlame_ <= 0) {
		isParry_ = 0;
		parryFlame_ = 12;
		color_ = WHITE;
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

	//4頂点の座標を更新
	quad_.leftTop = { quad_.pos.x - quad_.radius.x, quad_.pos.y - quad_.radius.y };
	quad_.leftBottom = { quad_.pos.x - quad_.radius.x, quad_.pos.y + quad_.radius.y };
	quad_.rightBottom = { quad_.pos.x + quad_.radius.x, quad_.pos.y + quad_.radius.y };
	quad_.rightTop = { quad_.pos.x + quad_.radius.x, quad_.pos.y - quad_.radius.y };
}

void Player::Draw() {
	Novice::DrawQuad(
		int(quad_.leftTop.x), int(quad_.leftTop.y),
		int(quad_.rightTop.x), int(quad_.rightTop.y),
		int(quad_.leftBottom.x), int(quad_.leftBottom.y),
		int(quad_.rightBottom.x), int(quad_.rightBottom.y),
		quad_.imagePos.x, quad_.imagePos.y, quad_.imageWidth, quad_.imageHeight, quad_.image.white1x1, quad_.color
	);

	//デバッグ用
	Novice::ScreenPrintf(20, 20, "wheelScroll:%d", weapon_->wheelScroll_);
	Novice::ScreenPrintf(20, 40, "attack:%d", attack_);
	//Novice::ScreenPrintf(20, 60, "isJump%d", isJump_);
	//Novice::ScreenPrintf(20, 80, "velocity X:%5.1f, Y:%5.1f", velocity_.x, velocity_.y);
	//Novice::ScreenPrintf(20, 100, ":%d", velocity_.x, velocity_.y);
}
