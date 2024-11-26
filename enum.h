#pragma once

enum Scene {
	Title,
	Tutorial,
	Game,
	Clear
};

//攻撃手段
enum situation_ {
	moving,
	fallingAttack,
	rushAttack,
	allDerectionShot,
	beam,
};

//突進攻撃回数
enum rushAttackNumber {
	firstAttack,
	secondAttack,
	thirdAttack,
	remove
};
