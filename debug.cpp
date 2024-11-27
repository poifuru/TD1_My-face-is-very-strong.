#include "debug.h"

void debugprint(Player* player, Enemy* enemy)
{
	Novice::ScreenPrintf(20, 20, "Bullet PosX:%5.1f Y:%5.1f", player->weapon_->bullet_[0].pos.x, player->weapon_->bullet_[0].pos.y);
	Novice::ScreenPrintf(20, 40, "attack:%d", player->weapon_->attack_);
	Novice::ScreenPrintf(20, 60, "attackingTimer", player->weapon_->attackingTimer_);
	Novice::ScreenPrintf(20, 80, "bulletSpeed X:%5.1f Y:%5.1f", player->weapon_->bulletSpeed_[0].x, player->weapon_->bulletSpeed_[0].y);
	Novice::ScreenPrintf(20, 100, "invincibleTimer:%d", player->invincibleTimer_);

	//デバッグ用
	/*Novice::ScreenPrintf(20, 20, "Bullet PosX:%5.1f Y:%5.1f", weapon_->bullet_[0].pos.x, weapon_->bullet_[0].pos.y);
	Novice::ScreenPrintf(20, 40, "isShot:%d", weapon_->isShot_[0]);
	Novice::ScreenPrintf(20, 60, "bulletVec X:%5.1f Y:%5.1f", weapon_->bulletVec_[0].x, weapon_->bulletVec_[0].y);
	Novice::ScreenPrintf(20, 80, "bulletSpeed X:%5.1f Y:%5.1f", weapon_->bulletSpeed_[0].x, weapon_->bulletSpeed_[0].y);
	Novice::ScreenPrintf(20, 100, "isParry%d", parry_->isParry_);*/

	
	Novice::ScreenPrintf(32, 500, "HP:%d", player->HP_);
	Novice::ScreenPrintf(32, 520, "situation:%d", enemy->situation_);
	Novice::ScreenPrintf(32, 540, "HP:%d", enemy->hp_);

	//Ultimate.cppも消す

}
