#include "Parry.h"
#include "Player.h"
#include <Novice.h>

Parry::Parry(){
	isParry_ = 0;
	parryFlame_ = 12;
}

void Parry::Update(){
	//パリィの処理
	if ((!isParry_ && Novice::IsTriggerMouse(1)) || (!isParry_ && Novice::IsTriggerButton(0, kPadButton10))) {
		isParry_ = 1;
	}
	if (isParry_) {
		parryFlame_--;
	}
	if (parryFlame_ <= 0) {
		isParry_ = 0;
		parryFlame_ = 12;
	}
}
