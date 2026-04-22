//GameScene.cpp
#include "GameScene.h"
#include "../Scene.h"

void C_GameScene::Init()
{
	srand(timeGetTime());

	//========== 初期化関数 ===========
	m_stage.Init(this,Stage::Saturn);
	m_player.Init(this);

	TEXTUREMANAGER.ReadFile("TextureData.txt");
	SOUNDMANAGER.Init(this);
	BULLETMANAGER.Init(this);
	EFFECTMANAGER.Init(this);

	if(ENEMYMANAGER.GetNormalEnemy() == nullptr)ENEMYMANAGER.SpawnNormalEnemy();	//NULLチェックを入れると1体しか生成されなくなる
}

void C_GameScene::Update()
{
	m_stage.Update();

	m_player.Action();
	m_player.Update();
	m_player.LateAction();

	//衝突判定
	COLLISIONMANAGER.AllCollision(m_player, ENEMYMANAGER.GetEnemyList(), BULLETMANAGER.GetPlayerBulletList(), BULLETMANAGER.GetEnemyBulletList());

	ENEMYMANAGER.Update();
	BULLETMANAGER.Update();
	EFFECTMANAGER.Update();
}

void C_GameScene::Draw()
{
	m_stage.Draw();

	m_player.Draw();

	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	EFFECTMANAGER.Draw();
}

void C_GameScene::ImGui()
{
	m_player.ImGui();
	EFFECTMANAGER.eImGui();
}
