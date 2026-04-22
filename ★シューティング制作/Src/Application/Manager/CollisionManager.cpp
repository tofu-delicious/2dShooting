//CollisionManager.cpp
#include "CollisionManager.h"
#include "../Enemy/EnemyBase.h"
#include "../Bullet/BulletBase.h"



void C_CollisionManager::AllCollision(C_Player& a_player, vector<C_EnemyBase*>& a_enemies, vector<C_BulletBase*>& a_playerBullets,vector<C_BulletBase*> &a_enemyBullets)
{
	//プレイヤーと敵の弾の判定
	PlayerToEnemyBullet(a_player, a_enemyBullets);

	//プレイヤーと敵の判定
	PlayerToEnemy(a_player, a_enemies);

	//プレイヤーの弾と敵の判定
	PlayerBulletToEnemy(a_playerBullets, a_enemies);
}

bool C_CollisionManager::CheckCircleCollision(const Math::Vector2 a_posA, const float a_radiusA,const Math::Vector2 a_posB,const float a_radiusB)
{
	//ピタゴラスの定理の（a²とb²の部分を算出）
	float width = a_posA.x - a_posB.x;
	float height = a_posA.y - a_posB.y;

	//バグの修正箇所：const引数（読み取り専用の別名）を通して呼び出せるのは、const修飾されたメンバ関数だけである
	return a_radiusA + a_radiusB >= sqrtf(width * width + height * height);
}

void C_CollisionManager::PlayerToEnemyBullet(C_Player& a_player, vector<C_BulletBase*>& a_enemyBullets)
{
	for (auto& bullet : a_enemyBullets)
	{
		//どちらか一方が非表示状態なら判定をしない
		if (!a_player.IsActive() || !bullet->IsActive())continue;

		if (CheckCircleCollision(bullet->GetPos(), bullet->GetRadius(), a_player.GetPos(), a_player.GetRadius()))
		{
			bullet->OnHit();
			a_player.OnHit();
			break;
		}
	}
}

void C_CollisionManager::PlayerToEnemy(C_Player& a_player, vector<C_EnemyBase*>& a_enemies)
{
	for (auto& enemy : a_enemies)
	{
		//どちらか一方が非表示状態なら判定をしない
		if (!a_player.IsActive() || !enemy->IsActive())continue;

		if (CheckCircleCollision(enemy->GetPos(), enemy->GetRadius(), a_player.GetPos(), a_player.GetRadius()))
		{
			enemy->OnHit();
			a_player.OnHit();
			break;
		}
	}
}

void C_CollisionManager::PlayerBulletToEnemy(vector<C_BulletBase*>& a_playerBullets, vector<C_EnemyBase*>& a_enemies)
{
	for (auto& enemy : a_enemies)
	{
		for (auto& bullet : a_playerBullets)
		{
			//どちらか一方が非表示状態なら判定をしない
			if (!enemy->IsActive() || !bullet->IsActive())continue;

			if (CheckCircleCollision(enemy->GetPos(), enemy->GetRadius(), bullet->GetPos(), bullet->GetRadius()))
			{
				enemy->OnHit();
				bullet->OnHit();
				break;
			}
		}
	}
}