#pragma once
#include <Novice.h>

//構造体の宣言
struct Vector2 {
	float x;
	float y;
};

struct IntVector2 {
	int x;
	int y;
};

//アニメーション関係
struct Animation {
	int x;
	int timeSet;
	int timer;
};

//画像を入れておく構造体
struct Images {
	//サンプル
	int white1x1 = Novice::LoadTexture("./Resources./Images./white1x1.png");
	//数字 32 * n
	int num = Novice::LoadTexture("./Resources./Images./Num.png");
	//ウルト
	int playerUlt = Novice::LoadTexture("./Resources./Images./cutIn.png");
	int ULTGo = Novice::LoadTexture("./Resources./Images./ULT.png");
	int notULT = Novice::LoadTexture("./Resources./Images./notULT.png");
	//hud
	int AKey = Novice::LoadTexture("./Resources./Images./A.png");
	int onAKey = Novice::LoadTexture("./Resources./Images./onA.png");
	int Dkey = Novice::LoadTexture("./Resources./Images./D.png");
	int onDKey = Novice::LoadTexture("./Resources./Images./onD.png");
	int QKey = Novice::LoadTexture("./Resources./Images./Q.png");
	int onQKey = Novice::LoadTexture("./Resources./Images./onQ.png");
	int SPACEKey = Novice::LoadTexture("./Resources./Images./SPACE.png");
	int onSPACEKey = Novice::LoadTexture("./Resources./Images./onSPACE.png");
	int weponGuide = Novice::LoadTexture("./Resources./Images./weponGuide.png");
	//プレイヤーの動き
	int playerStand = Novice::LoadTexture("./Resources./Images./stand.png");
	int playerLeft = Novice::LoadTexture("./Resources./Images./walk_left.png");
	int playerRight = Novice::LoadTexture("./Resources./Images./walk_right.png");
	//playerBullet
	int playerBullet = Novice::LoadTexture("./Resources./Images./playerBullet.png");
	//enemyBullet
	int enemyBullet = Novice::LoadTexture("./Resources./Images./enemyBullet.png");
	//BackGround
	int backGround = Novice::LoadTexture("./Resources./Images./backGround.png");
	int gameBackGround = Novice::LoadTexture("./Resources./Images./gameBackground.png");
	int gameBackGroundCover = Novice::LoadTexture("./Resources./Images./gameBackGround_cover.png");
	//boss
	int bossStupidFace = Novice::LoadTexture("./Resources./Images./AHO.png");//stupid
	int bossStupidLeftFace = Novice::LoadTexture("./Resources./Images./AHOLeft.png");//stupidLeft
	int bossStupidRightFace = Novice::LoadTexture("./Resources./Images./AHORight.png");//stupidRight
	int bossNormalFace = Novice::LoadTexture("./Resources./Images./normalFace.png");//Normal
	int bossNormalLeftFace = Novice::LoadTexture("./Resources./Images./normalLeft.png");//NormalLeft
	int bossNormalRightFace = Novice::LoadTexture("./Resources./Images./normalRight.png");//NormalRight
	int bossAngryYellowFace = Novice::LoadTexture("./Resources./Images./OKOyellow.png");//angry
	int bossAngryYellowLeftFace = Novice::LoadTexture("./Resources./Images./OKOLeft.png");//angryLeft
	int bossAngryYellowRightFace = Novice::LoadTexture("./Resources./Images./OKORight.png");//angryRight
	int bossAngryRedFace = Novice::LoadTexture("./Resources./Images./OKOred.png");//angryRed
	int bossAngryRedLeftFace = Novice::LoadTexture("./Resources./Images./OKORedLeft.png");//angryRedLeft
	int bossAngryRedRightFace = Novice::LoadTexture("./Resources./Images./OKORedRight.png");//angryRedRight
	//beam
	int dangerSignal = Novice::LoadTexture("./Resources./Images./dangerSignal.png");
	int beam = Novice::LoadTexture("./Resources./Images./beam.png");
	//title
	int title = Novice::LoadTexture("./Resources./Images./title.png");
	//gameClear
	int gameClear = Novice::LoadTexture("./Resources./Images./gameClear.png");
	//gameOver
	int gameOver = Novice::LoadTexture("./Resources./Images./gameOver.png");
	//プレイヤーの剣
	int SWORD = Novice::LoadTexture("./Resources/Images/sword.png");
};

struct BGMs {
	//title
	int title = Novice::LoadAudio("./Resources./Audios./BGMs./title.mp3");
	//game
	int game = Novice::LoadAudio("./Resources./Audios./BGMs./game.mp3");
	//gameClear
	int gameClear = Novice::LoadAudio("./Resources./Audios./BGMs./gameClear.mp3");
	//gameOver
	int gameOver = Novice::LoadAudio("./Resources./Audios./BGMs./gameOver.mp3");
};

struct SEs {
	//sistemClick
	int sistemClick = Novice::LoadAudio("./Resources./Audios./SEs./sistemClick.mp3");
	//Enemy
	//fallingAttack
	int enemyFallingAttack = Novice::LoadAudio("./Resources./Audios./SEs./enemyFallingAttack.mp3");
	//rushAttack
	int enemyRushAttack = Novice::LoadAudio("./Resources./Audios./SEs./enemyRushAttack.mp3");
	//allDerectionShot
	int enemyAllDerectionShot = Novice::LoadAudio("./Resources./Audios./SEs./enemyAllDerectionShot.mp3");
	//bullet
	int enemyBullet = Novice::LoadAudio("./Resources./Audios./SEs./enemyBullet.mp3");
	//beam
	int enemyBeam = Novice::LoadAudio("./Resources./Audios./SEs./enemyBeam.mp3");
	int enemyDuringBeam = Novice::LoadAudio("./Resources./Audios./SEs./enemyDuringBeam.mp3");
	//bom
	int enemyBom = Novice::LoadAudio("./Resources./Audios./SEs./enemyBom.mp3");
	int enemyDuringBom = Novice::LoadAudio("./Resources./Audios./SEs./enemyDuringBom.mp3");
	//playerHit
	int playerHitAll = Novice::LoadAudio("./Resources./Audios./SEs./Hit1.mp3");
	int playerHitRush = Novice::LoadAudio("./Resources./Audios./SEs./Hit2.mp3");

	//ULT
	int ULT = Novice::LoadAudio("./Resources./Audios./SEs./ULT.mp3");
	int ULTReady = Novice::LoadAudio("./Resources./Audios./SEs./ULTReady.mp3");

};

//オブジェクトの構造体====================
struct Box {
	Vector2 pos;
	Vector2 drawPos;
	float width;
	float height;
	float angle;
	int color;
	FillMode shape;
};

struct Circle {
	Vector2 pos;
	Vector2 drawPos;
	Vector2 radius;
	float angle;
	int color;
	FillMode shape;
};

struct Quad {
	Vector2 pos;
	Vector2 drawPos;
	Vector2 radius;
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightBottom;
	Vector2 rightTop;
	Vector2 drawLeftTop;
	Vector2 drawLeftBottom;
	Vector2 drawRightBottom;
	Vector2 drawRightTop;
	IntVector2 imagePos;
	int imageWidth;
	int imageHeight;
	int image;
	int color;
};
//=====================================

