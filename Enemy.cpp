#include <Novice.h>
#include "Player.h"
#include "Enemy.h"

//コンストラクタ
Enemy::Enemy() {
	quad_.pos = { 980.0f,540.0f };
	quad_.radius = { 50.0f,50.0f };
	quad_.leftTop = {};
	quad_.leftBottom = {};
	quad_.rightBottom = {};
	quad_.rightTop = {};
	quad_.imagePos = {};
	quad_.imageWidth = {};
	quad_.imageHeight = {};
	quad_.image = {};
	quad_.color = {};
	length_ = 0.0f;
	velocity_ = { 5.0f,5.0f };
	acceleration_ = { 0.0f,0.0f };
}

//デストラクタ
Enemy::~Enemy() {

}

//敵の基本的な動き
void Enemy::Move() {
	//左右移動
	quad_.pos.x += velocity_.x;
	if (quad_.pos.x - quad_.radius.x <= 0.0f || quad_.pos.x + quad_.radius.x >= 1920.0f) {
		velocity_.x *= -1;
	}

	//矩形4点の更新
	quad_.leftTop = { quad_.pos.x - quad_.radius.x,quad_.pos.y - quad_.radius.y };
	quad_.rightTop = { quad_.pos.x + quad_.radius.x,quad_.pos.y - quad_.radius.y };
	quad_.leftBottom = { quad_.pos.x - quad_.radius.x,quad_.pos.y + quad_.radius.y };
	quad_.rightBottom = { quad_.pos.x + quad_.radius.x,quad_.pos.y + quad_.radius.y };
}

//敵を描画する関数
void Enemy::Draw() {
	Novice::DrawQuad(
		int(quad_.leftTop.x), int(quad_.leftTop.y),
		int(quad_.rightTop.x), int(quad_.rightTop.y),
		int(quad_.leftBottom.x), int(quad_.leftBottom.y),
		int(quad_.rightBottom.x), int(quad_.rightBottom.y),
		quad_.imagePos.x, quad_.imagePos.y,
		quad_.imageWidth, quad_.imageHeight,
		quad_.image.white1x1, WHITE
	);
}
