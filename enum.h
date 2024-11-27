#pragma once

//画面遷移
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
	bom,
	ult
};

//突進攻撃回数
enum rushAttackNumber {
	firstAttack,
	secondAttack,
	thirdAttack,
	remove
};

//敵の向き
enum enemyDirection {
	left,
	right,
	front
};

//敵の状態
enum enemyState {
	normal,
	halfAngry,
	angry
};