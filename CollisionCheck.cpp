#include "CollisionCheck.h"

void collisionCheck(Player* player, Enemy* enemy)
{
	//プレイヤーと敵の当たり判定
	if (player->quad_.pos.x + player->quad_.radius.x > enemy->quad_.pos.x - enemy->quad_.radius.x &&
		player->quad_.pos.x - player->quad_.radius.x < enemy->quad_.pos.x + enemy->quad_.radius.x &&
		player->quad_.pos.y + player->quad_.radius.y > enemy->quad_.pos.y - enemy->quad_.radius.y &&
		player->quad_.pos.y - player->quad_.radius.y < enemy->quad_.pos.y + enemy->quad_.radius.y) {
		if (player->parry_->isParry_) {
			//プレイヤーがパリィしているとき

		} else {
			//プレイヤーがパリィしていないとき
			//プレイヤーのHPを減らす
			if (enemy->situation_ == fallingAttack) {
				player->HP_ -= enemy->fallingAttackPower_;
			}
			if (enemy->situation_ == rushAttack) {
				player->HP_ -= enemy->rushAttackPower_;
			}
			if (enemy->situation_ == allDerectionShot) {
				player->HP_ -= enemy->allDerectionPower_;
			}
		}
	}

	for (int i = 0; i < 16; i++) {
		if (enemy->situation_ == allDerectionShot) {
			//プレイヤーと敵の弾の当たり判定
			if (player->quad_.pos.x + player->quad_.radius.x > enemy->bullet_.quad_[i].pos.x - enemy->bullet_.quad_[i].radius.x &&
				player->quad_.pos.x - player->quad_.radius.x < enemy->bullet_.quad_[i].pos.x + enemy->bullet_.quad_[i].radius.x &&
				player->quad_.pos.y + player->quad_.radius.y > enemy->bullet_.quad_[i].pos.y - enemy->bullet_.quad_[i].radius.y &&
				player->quad_.pos.y - player->quad_.radius.y < enemy->bullet_.quad_[i].pos.y + enemy->bullet_.quad_[i].radius.y) {
				//プレイヤーのHPを減らす
				player->HP_ -= enemy->allDerectionShotPower_;
				//弾を消す
				enemy->bullet_.isShotFlag_[i] = false;
			}
		}
	}
}


