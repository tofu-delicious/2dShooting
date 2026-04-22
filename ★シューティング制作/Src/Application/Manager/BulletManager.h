//BulletManager.h
#pragma once
#include "../Manager/TextureManager.h"
#include "../Bullet/NormalBullet.h"
#include "../Bullet/ChargeBullet.h"
#include "../Bullet/EnemyBullet.h"

//前方宣言
class C_GameScene;

using namespace std;

class C_BulletManager
{
public:

	~C_BulletManager() { Clear(); }	//念のためアプリ終了時にデータを全消去しておく！

	static C_BulletManager& GetInstance()
	{
		static C_BulletManager Instance;
		return Instance;
	}

	void Init(C_GameScene* a_pGameScene)
	{
		Clear();	//シーンの切り替え時に古い弾を全消去
		m_pGameScene = a_pGameScene;
	}

	//通常弾
	void CreateNormalBullet(Math::Vector2 a_pos)
	{
		C_NormalBullet* bullet = new C_NormalBullet();			//インスタンスを生成
		bullet->Init(m_pGameScene);								//預かっているGameSceneを返す
		bullet->SetTex(TEXTUREMANAGER.GetTex("NormalBullet"));	//画像セット
		bullet->Activate(a_pos);								//表示状態へ移行
		m_playerBullets.push_back(bullet);						//リストに追加
	}

	//チャージ攻撃
	void CreateChargeBullet(Math::Vector2 a_pos)
	{
		C_ChargeBullet* bullet = new C_ChargeBullet();			//インスタンスを生成
		bullet->Init(m_pGameScene);								//預かっているGameSceneを渡す
		bullet->SetTex(TEXTUREMANAGER.GetTex("ChargeBullet"));	//画像セット
		bullet->Activate(a_pos);								//表示状態へ移行
		m_playerBullets.push_back(bullet);						//リストに追加
	}

	//敵の弾
	void CreateEnemyBullet(Math::Vector2 a_pos)
	{
		C_EnemyBullet* bullet = new C_EnemyBullet();
		bullet->Init(m_pGameScene);
		bullet->SetTex(TEXTUREMANAGER.GetTex("EnemyBullet"));
		bullet->Activate(a_pos);
		m_enemyBullets.push_back(bullet);
	}

	void Update()
	{
		UpdateList(m_playerBullets);

		UpdateList(m_enemyBullets);
	}

	void Draw()
	{
		DrawList(m_playerBullets);

		DrawList(m_enemyBullets);
	}

	//データ全削除（GameSceneが作り直されても昔のデータを保持し続けるのを阻止するため）
	void Clear()
	{
		for (auto& bullet : m_playerBullets){ delete bullet;}	//データの中身を消去
		for (auto& bullet : m_enemyBullets) { delete bullet; }	//データの中身を消去

		m_playerBullets.clear();		//リストの要素数を0にする（deleteせずにclear関数をすると、住所は存在しないのにデータは存在するという最悪なメモリリークに繋がる）
		m_enemyBullets.clear();
	}

	//=========== ゲッター ============
	vector<C_BulletBase*>& GetPlayerBulletList() { return m_playerBullets; }

	vector<C_BulletBase*>& GetEnemyBulletList() { return m_enemyBullets; }

	//リストから「C_NormalBullet」型のポインタを探す
	C_NormalBullet* GetNormalBullet()
	{
		for (auto* bullet : m_playerBullets)
		{
			auto* normal = dynamic_cast<C_NormalBullet*>(bullet);
			if (normal) return normal;
		}
		return nullptr;
	}

	//リストから「C_ChargeBullet」型のポインタを探す
	C_ChargeBullet* GetChargeBullet()
	{
		for (auto* bullet : m_playerBullets)
		{
			auto* charge = dynamic_cast<C_ChargeBullet*>(bullet);
			if (charge) return charge;
		}
		return nullptr;
	}

private:

	C_BulletManager() {}

	void UpdateList(vector<C_BulletBase*> &a_bullets)
	{
		//全エフェクトをループで更新
		for (auto it = a_bullets.begin(); it != a_bullets.end();)
		{
			//NULLチェック
			if (*it == nullptr)
			{
				it = a_bullets.erase(it);
				continue;
			}

			(*it)->Update();

			//非表示状態のエフェクトはメモリ解放する
			if (!(*it)->IsActive())
			{
				delete (*it);				//メモリ解放
				it = a_bullets.erase(it);	//erase関数は、引数の要素を削除した後、その要素よりも後に位置していたデータが前に詰めてくる（空間を自動的になくす）性質を持つ。
				//左辺の「it」変数には削除した次の要素の箱が格納されているため、「++it」のようにインクリメントをする必要がない。
			}
			else
			{
				//(*it)->Update();			//もしここにUpdate関数を呼び出した場合、エフェクトが消える際に、すぐに消えないということが発生するから
				++it;						//次の要素へ進む
			}

		}
	}

	void DrawList(vector<C_BulletBase*> &a_bullets)
	{
		for (auto bullet : a_bullets)
		{
			if (bullet == nullptr)continue;
			bullet->Draw();
		}
	}

	C_GameScene* m_pGameScene = nullptr;

	vector<C_BulletBase*> m_playerBullets;		//プレイヤーの弾を管理する
	vector<C_BulletBase*> m_enemyBullets;		//敵の弾を管理する

};

#define BULLETMANAGER C_BulletManager::GetInstance()