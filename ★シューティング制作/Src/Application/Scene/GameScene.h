//GameScene.h
#pragma once
#include "SceneBase.h"
#include "../Stage.h"

#include "../Player.h"

#include "../Manager/TextureManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/BulletManager.h"
#include "../Manager/EffectManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/EnemyManager.h"

//画面端変数
#define SCREEN_PADDING 8	//内側の余白
#define SCREENTOP 360		//画面上端
#define SCREENDOWN -360		//画面下端
#define SCREENRIGHT 640		//画面右端
#define SCREENLEFT -640		//画面左端


class C_GameScene :public C_SceneBase
{
private:

	//========= インスタンス ===========
	C_Stage m_stage;

	C_Player m_player;

public:
	C_GameScene(){}
	~C_GameScene(){}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ImGui()override;

	//============ ゲッター ============

	C_Player* GetPlayer() { return &m_player; }								//Playerクラスのインスタンス情報を取得する

private:
};