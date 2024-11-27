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

//画像を入れておく構造体
struct Images {
	//サンプル
	int white1x1 = Novice::LoadTexture("./Resources./Images./white1x1.png");
	//ウルト
	int playerUlt = Novice::LoadTexture("./Resources./Images./cutIn.png");
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

