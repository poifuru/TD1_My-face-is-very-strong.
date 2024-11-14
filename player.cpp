#include "player.h"

Player::Player(){
	pos_ = { 300.0f, 900.0f };
	radius_ = 16.0f;
	leftTop_;
	leftBottom_;
	rightBottom_;
	rightTop_;
	velocity_ = { 8.0f, 8.0f };
}

void Player::Update(const char keys[]) {
	//移動の処理
	if (keys[DIK_A]) {
		pos_.x -= velocity_.x;
	}
	else if (keys[DIK_D]) {
		pos_.x += velocity_.x;
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
		0, 0, 1, 1, image.white1x1, WHITE
	);
}
