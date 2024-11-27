#include <Novice.h>
#include "EnemyBom.h"

//コンストラクタ
Bom::Bom() {
	//DrawQuadで主に使う
	quad_.pos = {};
	quad_.radius = { 0.0f,0.0f };
	quad_.leftTop = {};
	quad_.leftBottom = {};
	quad_.rightBottom = {};
	quad_.rightTop = {};
	quad_.imagePos = { 0,0 };
	quad_.imageWidth = { 105 };
	quad_.imageHeight = { 105 };
	quad_.image = images_.bossAngryRedFace;
	quad_.color = {};
	//速度
	velocity_ = {};
	//加速度
	acceleration_ = { 1.0f,1.0f };
	//ボムフラグ
	bomFlag_ = false;
	//音
	enemyDuringBomSE_ = SE_.enemyDuringBom;
	enemyDuringBomHandle_ = -1;
}

//デストラクタ
Bom::~Bom() {

}

//基本的な動き
void Bom::Move() {
	if (quad_.radius.x <= 900.0f && quad_.radius.y <= 900.0f) {
		//速度Xに加速度を追加
		if (velocity_.x <= 15.0f) {
			velocity_.x += acceleration_.x;
		} else {
			velocity_.x = -5.0f;
			//音
			enemyDuringBomHandle_ = Novice::PlayAudio(enemyDuringBomSE_, false, 0.03f);
		}
		//速度Yに加速度を追加
		if (velocity_.y <= 15.0f) {
			velocity_.y += acceleration_.y;
		} else {
			velocity_.y = -5.0f;
		}
		//半径に速度を追加
		quad_.radius.x += velocity_.x;
		quad_.radius.y += velocity_.y;
	} else {
		velocity_.x = 0.0f;
		velocity_.y = 0.0f;
	}

	//矩形4点の更新
	quad_.leftTop = { quad_.pos.x - quad_.radius.x,quad_.pos.y - quad_.radius.y };
	quad_.rightTop = { quad_.pos.x + quad_.radius.x,quad_.pos.y - quad_.radius.y };
	quad_.leftBottom = { quad_.pos.x - quad_.radius.x,quad_.pos.y + quad_.radius.y };
	quad_.rightBottom = { quad_.pos.x + quad_.radius.x,quad_.pos.y + quad_.radius.y };
}

//描画
void Bom::Draw() {
	if (bomFlag_) {
		Novice::DrawQuad(
			int(quad_.leftTop.x), int(quad_.leftTop.y),
			int(quad_.rightTop.x), int(quad_.rightTop.y),
			int(quad_.leftBottom.x), int(quad_.leftBottom.y),
			int(quad_.rightBottom.x), int(quad_.rightBottom.y),
			quad_.imagePos.x, quad_.imagePos.y,
			quad_.imageWidth, quad_.imageHeight,
			quad_.image, WHITE
		);
	}
}