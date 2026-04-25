//AreaEnemy.h
#pragma once
#include "EnemyBase.h"
#include "../Manager/TextureManager.h"

//前方宣言
class C_GameScene;

class C_AreaEnemy :public C_EnemyBase
{
public:
	C_AreaEnemy() {}
	~C_AreaEnemy() {}

	void Init(C_GameScene* a_GameScene)override;
	void Action(const Math::Vector2& a_playerPos)override;
	void Update()override;
	void Draw()override;
	void cImGui()override {}

	//行列
	void UpdateMatrix();

	//表示状態にする処理
	void Activate() override;

	//敵の行動パターンを切り替える
	void ChangeAction(const Math::Vector2& a_playerPos = { 0,0 })override;

	//逃げる
	void MoveEscape()override;

	//急停止する
	void MoveStop()override;

	//平行移動
	void MoveParallel()override;

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