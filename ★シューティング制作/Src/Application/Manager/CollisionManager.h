//CollisionManager.h
#pragma once
#include  "../player.h"		//プレイヤー
#include "EnemyManager.h"	//敵
#include "BulletManager.h"	//弾

class C_CollisionManager
{
public:
	
	~C_CollisionManager(){}

	static C_CollisionManager &GetInstance()
	{
		static C_CollisionManager Instance;
		return Instance;
	}

	//全オブジェクト衝突判定
	void AllCollision(C_Player& a_player, vector<C_EnemyBase*>& a_enemies, vector<C_BulletBase*>& a_playerBullets, vector<C_BulletBase*>& a_enemyBullets);

	//円同士の衝突判定（引数➀：敵等の比較する対象 引数➁：自機等の比較される対象
	bool CheckCircleCollision(const Math::Vector2 a_posA,const float a_radiusA,const Math::Vector2 a_posB,const float a_radiusB);

	//プレイヤーと敵の弾
	void PlayerToEnemyBullet(C_Player &a_player,vector<C_BulletBase*> &a_enemyBullets);

	//プレイヤーと敵
	void PlayerToEnemy(C_Player &a_player,vector<C_EnemyBase*>&a_enemies);

	//プレイヤーの弾と敵
	void PlayerBulletToEnemy(vector<C_BulletBase*> &a_playerBullets,vector<C_EnemyBase*> &a_enemies);

private:

	C_CollisionManager(){}

	static constexpr float RADIUS_TO_DIAMETER = 2.0f;

};

#define COLLISIONMANAGER C_CollisionManager::GetInstance()