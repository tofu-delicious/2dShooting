//AreaEnemy.h
#pragma once
#include "EnemyBase.h"
#include "../Manager/TextureManager.h"

//構造体（1つのクラスに複数の要素を実装するため、構造体を使用する）
struct AreaData
{
	Math::Vector2 pos;		//座標
	Math::Vector2 move;		//移動量
	Math::Matrix transMat;	//移動行列
	Math::Matrix scaleMat;	//拡縮行列
	Math::Matrix rotateMat;	//回転行列
	Math::Matrix mat;		//合成行列
	Math::Rectangle rect;	//画像範囲指定
	KdTexture* tex;			//画像用
	float radiusX;			//X軸方向の半径
	float radiusY;			//Y軸方向の半径
	float scaleX;			//X軸方向の拡縮
	float scaleY;			//Y軸方向の拡縮
	float rotate;			//回転角度
	float alpha;			//不透明度
	float fadeStep;			//フェード用
	bool isActive;			//true 表示　false 非表示
};

enum class ActionMode
{
	Wait,		//何もしない
	Calculate,	//プレイヤーの現在地を目標座標として決定
	Move,		//目標座標へ向かう
	Deploy,		//エリアを展開する
	Shrink		//エリアを縮小する
};

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
	void cImGui()override {};

	//座標確定処理
	void CommitMove()override { enemy.pos += enemy.move; }

	//表示状態にする処理
	void Activate() override;

	//敵の行動パターンを切り替える（AreaEnemyの行動パターンは1つしかない）
	void ChangeAction(const Math::Vector2& a_playerPos = { 0,0 })override;

	//敵の攻撃
	void AttackEnemy() override;

	//敵の効果
	void BenefitPlayer() override;

	//衝突処理
	void OnHit()override;

	//このクラスの削除条件を変更する（通常はIsActive()がfalseのときに削除される）
	bool IsDeletable() override { return !enemy.isActive&& !area.isActive; }
	
	//============ 敵 =============
	void InitEnemy();
	//行列処理
	void UpdateMatEnemy();
	//目的座標を決める
	void DetermineTargetPos(const Math::Vector2 &a_targetPos);
	//最短経路を決める
	void CalculateVelocity();
	//目的座標に着いたかどうかを判定
	bool IsArrived();

	//========== エリア ===========
	void InitArea();
	//行列処理
	void UpdateMatArea();
	//拡大処理
	void ExpandArea();
	//縮小処理
	void ShrinkArea();

	//========== ゲッター =========
	//座標情報を取得する（引数なしはenemy構造体変数の情報、引数ありは構造体変数の情報
	Math::Vector2 GetPos()const override { return enemy.pos; }
	float GetRadius()const override { return (enemy.radiusX > enemy.radiusY) ? enemy.radiusX : enemy.radiusY; }
	float GetRadiusX()const override { return enemy.radiusX; }
	float GetRadiusY()const override { return enemy.radiusY; }
	bool IsActive()const override { return enemy.isActive; }

	Math::Vector2 GetPos(AreaData& a_AreaData)const{ return a_AreaData.pos; }
	float GetRadius(AreaData& a_AreaData)const{ return (a_AreaData.radiusX > a_AreaData.radiusY) ? a_AreaData.radiusX : a_AreaData.radiusY; }
	float GetRadiusX(AreaData& a_AreaData)const{ return a_AreaData.radiusX; }
	float GetRadiusY(AreaData& a_AreaData)const{ return a_AreaData.radiusY; }
	bool IsActive(AreaData& a_AreaData)const{ return a_AreaData.isActive; }

	//========== セッター =========
	void SetTex(KdTexture* a_enemyTex, KdTexture* a_areaTex)
	{
		enemy.tex = a_enemyTex;
		area.tex = a_areaTex;
	}

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;

	//======= 定数・設定値 ========
	//敵
	static constexpr float MOVE_SPEED = 3.0f;		//敵の移動量
	//エリア
	static constexpr float INITIAL_SCALE = 0.25f;	//初期拡大率
	static constexpr float MAX_SCALE = 8.0f;		//最大拡大率
	static constexpr float SCALE_SPEED = 0.04f;		//拡大増加・減少量

	//======== 状態フラグ =========
	bool m_isExpanding;				//true：エリア拡大中　false：エリア縮小中

	//========= 動的変数 ==========
	AreaData enemy;					//AreaEnemy
	AreaData area;					//AreaEnemyが展開するエリア

	ActionMode m_ActionMode = ActionMode::Calculate;

	Math::Vector2 m_targetPos;		//敵が向かう目標座標
	float m_vectorX;				//目的座標へ向かうX軸方向の移動量
	float m_vectorY;				//目的座標へ向かうY軸方向の移動量


};