
//EnemyBullet.h
#pragma once
#include "BulletBase.h"

using namespace std;

class C_EnemyBullet:public C_BulletBase
{
public:
	C_EnemyBullet(){}
	~C_EnemyBullet(){}

	void Init(C_GameScene* a_pGameScene)override;
	void Update(const Math::Vector2& a_playerPos = { 0,0 })override;
	void Draw()override;

	//弾を表示させる
	void Activate(Math::Vector2 a_pos);

	//行列計算
	void UpdateMatrix();

	//画面外処理
	bool IsOutOfBounds();

	//初期状態に戻す
	void ResetToDefault();

	//常に回転を行う
	void RotateLoop(const float& INCREASE_ANGLE);

	//========= ゲッター =========
	//変数「m_isActive」の真偽値を取得する
	bool IsActive() const override { return m_isActive; }

	//========= セッター =========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }
	//変数「m_isActive」に引数の真偽値を格納する
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }

	//========= デバッグ =========
	void bImGui(){}

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;	//GameSceneクラスのインスタンスを格納する

	//======= 定数・設定値 ========
	static constexpr int OFFSET_Y = 50;				//プレイヤーとチャージ攻撃の生成場所との間隔
	static constexpr float MOVE_SPEED_Y = 7.0f;			//チャージ攻撃の発射速度
	static constexpr float MAX_ANGLE = 360.0f;			//ChargeBulletの回転の最大角度
	static constexpr float INCREASE_ANGLE = 10.0f;		//ChargeBulletの回転の増分角度

	//======== 状態フラグ =========

	//========= 動的変数 ==========
	float m_chargeTime;						//チャージしてからカウントする時間（Lボタンを押してからカウントする）
	float m_scaledRadius;					//Scaleを乗算した後の半径の値
};