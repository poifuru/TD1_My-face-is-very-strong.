#include <Novice.h>
#include "player.h"

Player::Player(){
	quad_.pos = { 300.0f, 868.0f };
	quad_.radius = 32.0f;
	quad_.leftTop;
	quad_.leftBottom;
	quad_.rightBottom;
	quad_.rightTop;
	quad_.imagePos = { 0, 0 };
	quad_.width = 32;
	quad_.height = 32;
	quad_.color = WHITE;
	velocity_ = { 8.0f, 0.0f };
	color_ = WHITE;
	isParry_ = 0;
	parryFlame_ = 12;
	isJump_ = 0;
	stickX_ = 0;
	stickY_ = 0;
}

Player::~Player(){

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

	//攻撃！


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
	quad_.leftTop = { quad_.pos.x - quad_.radius, quad_.pos.y - quad_.radius };
	quad_.leftBottom = { quad_.pos.x - quad_.radius, quad_.pos.y + quad_.radius };
	quad_.rightBottom = { quad_.pos.x + quad_.radius, quad_.pos.y + quad_.radius };
	quad_.rightTop = { quad_.pos.x + quad_.radius, quad_.pos.y - quad_.radius };
}

void Player::Draw() {
	Novice::DrawQuad(
		int(quad_.leftTop.x), int(quad_.leftTop.y),
		int(quad_.rightTop.x), int(quad_.rightTop.y),
		int(quad_.leftBottom.x), int(quad_.leftBottom.y),
		int(quad_.rightBottom.x), int(quad_.rightBottom.y),
		quad_.imagePos.x, quad_.imagePos.y, quad_.width, quad_.height, quad_.image.white1x1, quad_.color
	);

	Novice::ScreenPrintf(20, 20, "pos X:%5.1f Y:%5.1f", quad_.pos.x, quad_.pos.y);
	Novice::ScreenPrintf(20, 40, "parryFlame:%d", parryFlame_);
	Novice::ScreenPrintf(20, 60, "isJump%d", isJump_);
	Novice::ScreenPrintf(20, 80, "velocity X:%5.1f, Y:%5.1f", velocity_.x, velocity_.y);
	//Novice::ScreenPrintf(20, 100, ":%d", velocity_.x, velocity_.y);
}
