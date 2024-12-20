﻿#include "CollisionCheck.h"
#include "struct.h"

void collisionCheck(Player* player, Enemy* enemy)
{
	SEs SE;

	int allSE = SE.playerHitAll;
	int allSEHandle = -1;
	int rushSE = SE.playerHitRush;
	int rushSEHandle = -1;
	int swordSE = SE.sword;
	int swordSEHandle = -1;

	//弾と敵の当たり判定
	for (int i = 0; i < 30; i++) {
		if (player->weapon_->isShot_[i]) {
			if (player->weapon_->bullet_[i].pos.x + player->weapon_->bullet_[i].radius.x > enemy->quad_.pos.x - enemy->quad_.radius.x &&
				player->weapon_->bullet_[i].pos.x - player->weapon_->bullet_[i].radius.x < enemy->quad_.pos.x + enemy->quad_.radius.x &&
				player->weapon_->bullet_[i].pos.y + player->weapon_->bullet_[i].radius.y > enemy->quad_.pos.y - enemy->quad_.radius.y &&
				player->weapon_->bullet_[i].pos.y - player->weapon_->bullet_[i].radius.y < enemy->quad_.pos.y + enemy->quad_.radius.y) {
				allSEHandle = Novice::PlayAudio(allSE, false, 0.2f);
				if (enemy->status_ != angry) {
					//敵のHPを減らす
					enemy->hp_ -= player->weapon_->bulletAttackPower_;
				}
				//弾を消す
				player->weapon_->isShot_[i] = false;
			}
		}
	}

	//無敵時間のフラグが立ってない時
	if (!enemy->invincible_) {
		//剣と敵の当たり判定
		if (player->weapon_->weaponMode_ == 0) {
			if (player->weapon_->attack_ != 0) {
				if (player->weapon_->sword_.pos.x + player->weapon_->sword_.radius.x > enemy->quad_.pos.x - enemy->quad_.radius.x &&
					player->weapon_->sword_.pos.x - player->weapon_->sword_.radius.x < enemy->quad_.pos.x + enemy->quad_.radius.x &&
					player->weapon_->sword_.pos.y + player->weapon_->sword_.radius.y > enemy->quad_.pos.y - enemy->quad_.radius.y &&
					player->weapon_->sword_.pos.y - player->weapon_->sword_.radius.y < enemy->quad_.pos.y + enemy->quad_.radius.y) {

					swordSEHandle = Novice::PlayAudio(swordSE, false, 0.2f);
					//敵のHPを減らす
					enemy->hp_ -= player->weapon_->swordAttackPower_;
					enemy->invincible_ = 1;
				}
			}
		}
	}

	//無敵時間のフラグが立ってない時
	if (!player->invincible_) {
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
					rushSEHandle = Novice::PlayAudio(rushSE, false, 0.2f);
					player->HP_ -= enemy->fallingAttackPower_;
				}
				if (enemy->situation_ == rushAttack) {
					rushSEHandle = Novice::PlayAudio(rushSE, false, 0.2f);
					player->HP_ -= enemy->rushAttackPower_;
				}
				if (enemy->situation_ == allDerectionShot) {
					rushSEHandle = Novice::PlayAudio(rushSE, false, 0.2f);
					player->HP_ -= enemy->allDerectionPower_;
				}
				player->invincible_ = 1;
			}
		}

		for (int i = 0; i < 16; i++) {
			if (enemy->situation_ == allDerectionShot) {
				//プレイヤーと敵の弾の当たり判定
				if (player->quad_.pos.x + player->quad_.radius.x > enemy->bullet_->quad_[i].pos.x - enemy->bullet_->quad_[i].radius.x &&
					player->quad_.pos.x - player->quad_.radius.x < enemy->bullet_->quad_[i].pos.x + enemy->bullet_->quad_[i].radius.x &&
					player->quad_.pos.y + player->quad_.radius.y > enemy->bullet_->quad_[i].pos.y - enemy->bullet_->quad_[i].radius.y &&
					player->quad_.pos.y - player->quad_.radius.y < enemy->bullet_->quad_[i].pos.y + enemy->bullet_->quad_[i].radius.y) {

					allSEHandle = Novice::PlayAudio(allSE, false, 0.2f);
					//プレイヤーのHPを減らす
					player->HP_ -= enemy->allDerectionShotPower_;
					//弾を消す
					enemy->bullet_->isShotFlag_[i] = false;

					player->invincible_ = 1;
				}
			}
		}

		//プレイヤーとビームの当たり判定
		for (int i = 0; i < 3; i++) {
			if (enemy->beam_->beamFlag_[i]) {
				if (player->quad_.pos.x + player->quad_.radius.x > enemy->beam_->beam_[i].pos.x - enemy->beam_->beam_[i].radius.x &&
					player->quad_.pos.x - player->quad_.radius.x < enemy->beam_->beam_[i].pos.x + enemy->beam_->beam_[i].radius.x &&
					player->quad_.pos.y + player->quad_.radius.y > enemy->beam_->beam_[i].pos.y - enemy->beam_->beam_[i].radius.y &&
					player->quad_.pos.y - player->quad_.radius.y < enemy->beam_->beam_[i].pos.y + enemy->beam_->beam_[i].radius.y) {
					//プレイヤーのHPを減らす
					player->HP_ -= enemy->beamPower_;
					player->invincible_ = 1;
				}
			}
		}

		//プレイヤーとボムの当たり判定
		if (enemy->bom_->bomFlag_) {
			if (player->quad_.pos.x + player->quad_.radius.x > enemy->bom_->quad_.pos.x - enemy->bom_->quad_.radius.x &&
				player->quad_.pos.x - player->quad_.radius.x < enemy->bom_->quad_.pos.x + enemy->bom_->quad_.radius.x &&
				player->quad_.pos.y + player->quad_.radius.y > enemy->bom_->quad_.pos.y - enemy->bom_->quad_.radius.y &&
				player->quad_.pos.y - player->quad_.radius.y < enemy->bom_->quad_.pos.y + enemy->bom_->quad_.radius.y) {
				//プレイヤーのHPを減らす
				player->HP_ -= enemy->bomPower_;
				player->invincible_ = 1;
			}
		}
	}


	//無敵時間つけていくよ～
	if (player->invincible_ == 1) {
		player->invincibleTimer_--;
	}
	if (player->invincibleTimer_ <= 0) {
		player->invincible_ = 0;
		player->invincibleTimer_ = 120;
	}

	if (enemy->invincible_ == 1) {
		enemy->invincibleTime_--;
	}
	if (enemy->invincibleTime_ <= 0) {
		enemy->invincible_ = 0;
		enemy->invincibleTime_ = 120;
	}



}