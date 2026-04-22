//LuckyEnemy.h
#pragma once
#include "EnemyBase.h"
#include "../Manager/TextureManager.h"

//前方宣言
class C_GameScene;

class C_LuckyEnemy :public C_EnemyBase
{
public:
	C_LuckyEnemy() {}
	~C_LuckyEnemy() {}

	void Init(C_GameScene* a_GameScene)override;
	void Update()override;
	void Draw()override;
	void cImGui()override {}

	//行列
	void UpdateMatrix();

	//表示状態にする処理
	void Activate() override;

	//敵の動き
	void MoveEnemy() override;

	//敵の攻撃
	void AttackEnemy() override;

	//敵の効果
	void BenefitPlayer() override;

	//衝突処理
	void OnHit()override;

	//========== ゲッター =========



private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;

	//======= 定数・設定値 ========

	//======== 状態フラグ =========

	//========= 動的変数 ==========


};