//ChargeBullet.h
#pragma once
#include "BulletBase.h"

//前方宣言
class C_GameScene;

class C_ChargeBullet:public C_BulletBase
{
public:
	C_ChargeBullet(){}
	~C_ChargeBullet(){}

	void Init(C_GameScene* a_pGameScene)override;
	void Update()override;
	void Draw()override;

	//弾を表示させる
	void Activate(Math::Vector2 a_pos);

	//行列計算
	void UpdateMatrix();

	//チャージ時間（m_chargeTime）をカウントする
	void UpdateChargeTime();

	//画面外処理
	bool IsOutOfBounds();

	//初期状態に戻す
	void ResetToDefault();

	//常に回転を行う
	void RotateLoop(const float& INCREASE_ANGLE);

	//========= ゲッター =========
	//拡大後の半径「m_scaledRadius」を取得する
	float GetScaledRadius()const { return m_scaledRadius; }
	//チャージ時間「m_chargeTime」を取得する
	float GetChargeTime()const { return m_chargeTime; }
	//変数「m_isActive」の真偽値を取得する
	bool IsActive() const override{ return m_isActive; }

	//========= セッター =========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }
	//変数「m_isActive」に引数の真偽値を格納する
	void SetActive(bool a_isActive) { m_isActive = a_isActive; }

	//========= デバッグ =========
	void bImGui();

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;	//GameSceneクラスのインスタンスを格納する

	//======= 定数・設定値 ========
	static constexpr int OFFSET_Y = 110;				//プレイヤーとチャージ攻撃の生成場所との間隔
	static constexpr float MOVE_SPEED_Y = 8.0f;			//チャージ攻撃の発射速度
	static constexpr float MAX_CHARGE_SCALE = 2.5f;		//ChargeBullet.m_scaleの上限値
	static constexpr float CHARGE_SPEED = 0.01f;		//ChargeBullet.m_scaleの拡大値
	static constexpr float MAX_ANGLE = 360.0f;			//ChargeBulletの回転の最大角度
	static constexpr float HIGH_INCREASE_ANGLE = 10.0f;	//ChargeBulletの回転の増分角度
	static constexpr float LOW_INCREASE_ANGLE = 1.5f;	//ChargeBulletの回転の増分角度
	static constexpr float CHARGE_INCREMENT = 1.0f;		//chargeTimeの増分

	//======== 状態フラグ =========

	//========= 動的変数 ==========
	float m_chargeTime;						//チャージしてからカウントする時間（Lボタンを押してからカウントする）
	float m_scaledRadius;					//Scaleを乗算した後の半径の値
};
