#include "parry.h"
#include "player.h"
#include <Novice.h>

Parry::Parry(){
	isParry_ = 0;
	parryFlame_ = 12;
}

void Parry::Update(){
	//パリィの処理
	if (!isParry_ && Novice::IsTriggerMouse(1) == 1 || !isParry_ && Novice::IsTriggerButton(0, kPadButton10)) {
		isParry_ = 1;
	}
	if (isParry_) {
		parryFlame_--;
		//quad_.color = BLUE;
	}
	if (parryFlame_ <= 0) {
		isParry_ = 0;
		parryFlame_ = 12;
		//quad_.color = WHITE;
	}
}
