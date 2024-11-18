#include <Novice.h>
#include "player.h"

Player::Player(){
	pos_ = { 300.0f, 868.0f };
	radius_ = 32.0f;
	leftTop_;
	leftBottom_;
	rightBottom_;
	rightTop_;
	velocity_ = { 8.0f, 0.0f };
	color_ = WHITE;
	isParry_ = 0;
	parryFlame_ = 12;
	isJump_ = 0;
	//*sticksPos = { 300.0f, 868.0f };
}

Player::~Player(){

}

void Player::Update(const char keys[], const char preKeys[]) {
	//移動の処理
	if (keys[DIK_A]) {
		pos_.x -= velocity_.x;
	}
	else if (keys[DIK_D]) {
		pos_.x += velocity_.x;
	}

	//攻撃！


	//パリィの処理
	if (!isParry_ && Novice::IsTriggerMouse(1) == 1) {
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
	if (!isJump_ && keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		isJump_ = 1;
		velocity_.y = -20.0f;
	}
	if (isJump_) {
		velocity_.y += 0.8f;
		pos_.y += velocity_.y;
	}
	//着地の調整
	if (isJump_ && velocity_.y >= 0 && leftBottom_.y + 10.0f >= 900.0f) {
		pos_.y = 868.0f;
		velocity_.y = 0;
		isJump_ = 0;
	}

	//4頂点の座標を更新
	leftTop_ = { pos_.x - radius_, pos_.y - radius_ };
	leftBottom_ = { pos_.x - radius_, pos_.y + radius_ };
	rightBottom_ = { pos_.x + radius_, pos_.y + radius_ };
	rightTop_ = { pos_.x + radius_, pos_.y - radius_ };
}

void Player::Draw() {
	Novice::DrawQuad(
		int(leftTop_.x), int(leftTop_.y),
		int(rightTop_.x), int(rightTop_.y),
		int(leftBottom_.x), int(leftBottom_.y),
		int(rightBottom_.x), int(rightBottom_.y),
		0, 0, 1, 1, image.white1x1, color_
	);

	Novice::ScreenPrintf(20, 20, "pos X:%5.1f Y:%5.1f", pos_.x, pos_.y);
	Novice::ScreenPrintf(20, 40, "parryFlame:%d", parryFlame_);
	Novice::ScreenPrintf(20, 60, "isJump%d", isJump_);
	Novice::ScreenPrintf(20, 80, "velocity X:%5.1f, Y:%5.1f", velocity_.x, velocity_.y);
	Novice::ScreenPrintf(20, 80, ":%d", velocity_.x, velocity_.y);
}
