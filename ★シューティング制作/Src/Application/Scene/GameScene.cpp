//GameScene.cpp
#include "GameScene.h"
#include "../Stage.h"
#include "../Player.h"
#include "../Manager/TextureManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/BulletManager.h"
#include "../Manager/EffectManager.h"
#include "../Manager/CollisionManager.h"
#include "../Manager/EnemyManager.h"

void C_GameScene::Init()
{
	srand(timeGetTime());

	m_stage = make_shared <C_Stage>();
	m_player = make_shared<C_Player>();

	//========== 初期化関数 ===========
	m_stage->Init(this,Stage::Saturn);
	m_player->Init(this);

	TEXTUREMANAGER.ReadFile("TextureData.txt");
	SOUNDMANAGER.Init(this);
	ENEMYMANAGER.Init(this);
	BULLETMANAGER.Init(this);
	EFFECTMANAGER.Init(this);

	if(ENEMYMANAGER.GetNormalEnemy() == nullptr)ENEMYMANAGER.SpawnNormalEnemy();	//NULLチェックを入れると1体しか生成されなくなる
	if(ENEMYMANAGER.GetLuckyEnemy() == nullptr)ENEMYMANAGER.SpawnLuckyEnemy();
	if(ENEMYMANAGER.GetAreaEnemy() == nullptr)ENEMYMANAGER.SpawnAreaEnemy();
	if(ENEMYMANAGER.GetItemEnemy() == nullptr)ENEMYMANAGER.SpawnItemEnemy();
	if(ENEMYMANAGER.GetBoss() == nullptr)ENEMYMANAGER.SpawnBoss();
}

void C_GameScene::Update()
{
	m_stage->Update();

	m_player->Action();
	m_player->Update();
	m_player->LateAction();

	//衝突判定
	COLLISIONMANAGER.AllCollision(*m_player, ENEMYMANAGER.GetEnemyList(), BULLETMANAGER.GetPlayerBulletList(), BULLETMANAGER.GetEnemyBulletList());

	ENEMYMANAGER.Action(m_player->GetPos());
	ENEMYMANAGER.Update();
	BULLETMANAGER.Update(m_player->GetPos());
	if(BULLETMANAGER.GetChargeBullet() != nullptr)EFFECTMANAGER.Update(BULLETMANAGER.GetChargeBullet()->GetPos());
}

void C_GameScene::Draw()
{
	m_stage->Draw();

	m_player->Draw();

	ENEMYMANAGER.Draw();
	BULLETMANAGER.Draw();
	EFFECTMANAGER.Draw();
}

void C_GameScene::ImGui()
{
	m_player->ImGui();
	ENEMYMANAGER.cImGui();
	EFFECTMANAGER.eImGui();
}
