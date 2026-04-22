//EnemyManager.h
#pragma once
#include <vector>
#include "../Enemy/NormalEnemy.h"
#include "../Enemy/LuckyEnemy.h"
#include "../Enemy/AreaEnemy.h"
#include "../Enemy/ItemEnemy.h"
#include "../Enemy/Boss.h"

using namespace std;

//前方宣言
class C_GameScene;

class C_EnemyManager
{
public:
	
	~C_EnemyManager(){}

	static C_EnemyManager& GetInstance()
	{
		static C_EnemyManager Instance;
		return Instance;
	}

	//=========== 生成処理 ============
	void SpawnNormalEnemy()
	{
		C_NormalEnemy* normal = new C_NormalEnemy();
		normal->Init(m_pGameScene);
		normal->SetTex(TEXTUREMANAGER.GetTex("NormalEnemy"));
		normal->Activate();
		m_enemies.push_back(normal);
	}

	void SpawnLuckyEnemy()
	{
		C_LuckyEnemy* lucky = new C_LuckyEnemy();
		lucky->Init(m_pGameScene);
		lucky->SetTex(TEXTUREMANAGER.GetTex("LuckyEnemy"));
		lucky->Activate();
		m_enemies.push_back(lucky);
	}

	void SpawnAreaEnemy()
	{
		C_AreaEnemy* area = new C_AreaEnemy();
		area->Init(m_pGameScene);
		area->SetTex(TEXTUREMANAGER.GetTex("AreaEnemy"));
		area->Activate();
		m_enemies.push_back(area);
	}

	void SpawnItemEnemy()
	{
		C_ItemEnemy* item = new C_ItemEnemy();
		item->Init(m_pGameScene);
		item->SetTex(TEXTUREMANAGER.GetTex("ItemEnemy"));
		item->Activate();
		m_enemies.push_back(item);
	}

	void SpawnBoss()
	{
		C_Boss* boss = new C_Boss();
		boss->Init(m_pGameScene);
		boss->SetTex(TEXTUREMANAGER.GetTex("Boss"));
		boss->Activate();
		m_enemies.push_back(boss);
	}

	//=========== 更新処理 ============
	void Update()
	{
		//全エフェクトをループで更新
		for (auto it = m_enemies.begin(); it != m_enemies.end();)
		{
			(*it)->Update();

			//非表示状態のエフェクトはメモリ解放する
			if (!(*it)->IsActive())
			{
				delete (*it);				//メモリ解放
				it = m_enemies.erase(it);	//erase関数は、引数の要素を削除した後、その要素よりも後に位置していたデータが前に詰めてくる（空間を自動的になくす）性質を持つ。
											//左辺の「it」変数には削除した次の要素の箱が格納されているため、「++it」のようにインクリメントをする必要がない。
			}
			else
			{
				//(*it)->Update();			//もしここにUpdate関数を呼び出した場合、エフェクトが消える際に、すぐに消えないということが発生するから
				++it;						//次の要素へ進む
			}
		}
	}

	//=========== 描画処理 ============
	void Draw()
	{
		for (auto& enemy : m_enemies)
		{
			enemy->Draw();
		}
	}

	//=========== ゲッター ============
	vector<C_EnemyBase*> &GetEnemyList(){ return m_enemies; }

	//NormalEnemyのインスタンス情報を取得
	C_NormalEnemy* GetNormalEnemy()
	{
		for (auto* enemy : m_enemies)
		{
			auto* normal = dynamic_cast<C_NormalEnemy*>(enemy);
			if(normal)return normal;
		}
		return nullptr;
	}

	//LuckyEnemyのインスタンス情報を取得
	C_LuckyEnemy* GetLuckyEnemy()
	{
		for (auto* enemy : m_enemies)
		{
			auto* lucky = dynamic_cast<C_LuckyEnemy*>(enemy);
			if (lucky)return lucky;
		}
		return nullptr;
	}

	//AreaEnemyのインスタンス情報を取得
	C_AreaEnemy* GetAreaEnemy()
	{
		for (auto* enemy : m_enemies)
		{
			auto* area = dynamic_cast<C_AreaEnemy*>(enemy);
			if (area)return area;
		}
		return nullptr;
	}

	//ItemEnemyのインスタンス情報を取得
	C_ItemEnemy* GetItemEnemy()
	{
		for (auto* enemy : m_enemies)
		{
			auto* item = dynamic_cast<C_ItemEnemy*>(enemy);
			if (item)return item;
		}
		return nullptr;
	}

	//Bossのインスタンス情報を取得
	C_Boss* GetBoss()
	{
		for (auto* enemy : m_enemies)
		{
			auto* boss = dynamic_cast<C_Boss*>(enemy);
			if (boss)return boss;
		}
		return nullptr;
	}

private:

	C_EnemyManager(){}

	//生成した敵を格納するリスト
	vector <C_EnemyBase*> m_enemies;

	C_GameScene* m_pGameScene = nullptr;;

};

#define ENEMYMANAGER C_EnemyManager::GetInstance()