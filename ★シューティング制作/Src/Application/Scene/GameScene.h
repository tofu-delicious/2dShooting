//GameScene.h
#pragma once
#include "SceneBase.h"

//前方宣言
class C_Stage;
class C_Player;

class C_TextureManager;
class C_SoundManager;
class C_BulletManager;
class C_EffectManager;
class C_CollisionManager;
class C_EnemyManager;

//画面端変数
#define SCREEN_PADDING 8	//内側の余白
#define SCREENTOP 360		//画面上端
#define SCREENDOWN -360		//画面下端
#define SCREENRIGHT 640		//画面右端
#define SCREENLEFT -640		//画面左端

using namespace std;


class C_GameScene :public C_SceneBase
{
private:

	//========= インスタンス ===========
	shared_ptr<C_Stage> m_stage = nullptr;
	shared_ptr<C_Player>m_player = nullptr;

public:
	C_GameScene() {}
	~C_GameScene(){}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ImGui()override;

	//============ ゲッター ============
	shared_ptr<C_Player> &GetPlayer() {return m_player;}//Playerクラスのインスタンス情報を取得する

private:
};