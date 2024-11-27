#pragma once
#include "Struct.h"
#include "Object.h"
#include "Enemy.h"
#include "Player.h"
#include "Easing.h"

const int kBulletNum = 30;
const int kMaxAttack = 3;

class Weapon : public Object {
public:
    //画像
    Images images_;
    
    SEs SE;
    //slash
    int slash1 = SE.airSlash;
    int slash1Handle = -1;
   /* int slash2 = SE.slash2;
    int slash2Handle = -1;
    int slash3 = SE.slash3;
    int slash3Handle = -1;*/

    //メンバ変数
    Quad sword_;
    Quad gun_;

    int weaponMode_;

    // 剣モードの変数 /
    int attack_;
    int attackingTimer_;
    int wheelScroll_;
    int swordAttackPower_;

    //動作の始点と終点
    Vector2 startPos[kMaxAttack];
    Vector2 endPos[kMaxAttack];
    Vector2 easeT[kMaxAttack];
    int isPushX[kMaxAttack];
    int isPushY[kMaxAttack];
    int isEaseX[kMaxAttack];
    int isEaseY[kMaxAttack];

   // 銃モードの変数 /
    Quad bullet_[kBulletNum];
    Vector2 bulletSpeed_[kBulletNum];
    int isShot_[kBulletNum];
    Vector2 bulletVec_[kBulletNum];
    Vector2 vectorToTarget_[kBulletNum]; //弾発射時の座標と敵の座標を結ぶベクトル
    int readyToFire_;
    int shotCoolTime_;
    int bulletAttackPower_;

    //コンストラクタ
    Weapon();

    //メンバ関数
    void Update(Enemy* enemy);
    void Draw();
};