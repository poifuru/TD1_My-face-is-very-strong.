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
		}
	}
}
