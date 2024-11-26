#include "debug.h"

void debugprint(Player* player, Enemy* enemy)
{
	Novice::ScreenPrintf(20, 20, "Bullet PosX:%5.1f Y:%5.1f", player->weapon_->bullet_[0].pos.x, player->weapon_->bullet_[0].pos.y);
	Novice::ScreenPrintf(20, 40, "weaponMode:%d", player->weapon_->weaponMode_);
	Novice::ScreenPrintf(20, 60, "coolTime:%d", player->weapon_->shotCoolTime_);
	Novice::ScreenPrintf(20, 80, "readyToFire:%d", player->weapon_->readyToFire_);
	Novice::ScreenPrintf(20, 100, "isParry%d", player->parry_->isParry_);

	
	Novice::ScreenPrintf(32, 500, "HP:%d", player->HP_);
	Novice::ScreenPrintf(32, 520, "situation:%d", enemy->situation_);
	Novice::ScreenPrintf(32, 540, "HP:%d", enemy->hp_);

	//Ultimate.cppも消す

}
