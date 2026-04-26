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
	void Action(const Math::Vector2 &a_playerPos)override;
	void Update()override;
	void Draw()override;
	void cImGui()override {}

	//行列
	void UpdateMatrix();

	//表示状態にする処理
	void Activate() override;

	//敵の行動パターンを切り替える
	void ChangeAction(const Math::Vector2& a_playerPos = { 0,0 })override;

	//水平移動
	void MoveTrans() { m_move = { -3.0f,0.0f }; }

	//停止
	void MoveStop() { m_move = { 0.0f,0.0f }; }

	//敵の攻撃（LuckyEnemyは攻撃をしない）
	void AttackEnemy() override{}

	//敵の効果
	void BenefitPlayer() override;

	//停止時間設定
	void SetStopTime(int a_seconds){ m_stopTime = a_seconds * FPS; }

	//停止時間経過処理
	void UpdateStopTime(){ if (m_stopTime > 0.0f) m_stopTime -= WAIT_STEP; }

	//改めて移動してもよいかを判定する
	bool IsMovable(){ return m_stopTime <= 0.0f; }

	//衝突処理
	void OnHit()override;

	//========== ゲッター =========

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;

	//======= 定数・設定値 ========
	static constexpr float MAX_STOP_POSX = 200.0f;		//停止範囲の最大X座標
	static constexpr float MIN_STOP_POSX = -200.0f;		//停止範囲の最小X座標
	static constexpr float MAX_STOP_TIME = 3.0f;		//最大停止時間
	static constexpr float MIN_STOP_TIME = 1.0f;		//最小停止時間
	static constexpr float WAIT_STEP = 1.0f;			//停止時間カウント
	static constexpr float FPS = 60.0f;					//秒をフレーム単位に変換する

	//======== 状態フラグ =========
	bool m_isArrived;			//停止位置に着いたらtrueを返す

	//========= 動的変数 ==========
	float m_stopPosX = 0.0f;	//停止位置のX座標
	float m_stopTime;			//総停止時間
};