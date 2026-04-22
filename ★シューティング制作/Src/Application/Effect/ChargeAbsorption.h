//ChargeAbsorption.h
#pragma once
#include "EffectBase.h"

class C_GameScene;
class C_ChargeBullet;

class C_ChargeAbsorption:public C_EffectBase
{
public:
	C_ChargeAbsorption(){}
	~C_ChargeAbsorption(){}

	void Init(C_GameScene* a_pGameScene)override;
	void Update()override;
	void Draw()override;

	//行列計算
	void UpdateMatrix();

	//表示させる
	void Activate(Math::Vector2 a_pos,float a_radiusX,float a_radiusY);

	//非表示にする
	void Deactivate();

	//描画位置を算出する
	void CalcDrawPos(Math::Vector2 a_pos, float a_radiusX, float a_radiusY);

	//エフェクトの動き
	void MoveAbsorption();

	//フェード処理
	void Fade();

	//指定した範囲の乱数を取得する
	float Rnd(float a_min, float a_max);

	//========= ゲッター ==========
	bool IsActive()override {return m_isActive;}

	//========= セッター ==========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }

	//========= デバッグ ==========
	void eImGui() {}

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;			//GameSceneクラスのインスタンスを取得
	C_ChargeBullet* m_pChargeBullet = nullptr;		//ChargeBulletクラスのインスタンスを取得

	//======= 定数・設定値 ========
	static constexpr float ROTATION_SPEED = 10.0f;		//エフェクトの回転速度
	static constexpr float ABSORPTION_SPEED = 1.5f;		//半径を減らす数値

	static constexpr float INITIAL_SCALE = 0.15f;		//生成時のScale値
	static constexpr float SPAWN_RADIUS_OFFSET = 10.0f;	//生成位置の調整

	static constexpr float MAX_ROTATE = 360.0f;			//傾きの最大値
	static constexpr float MIN_ROTATE = 0.0f;			//傾きの最小値

	static constexpr float MAX_FADE_STEP = -0.01f;		//透明度調整値の最大値
	static constexpr float MIN_FADE_STEP = -0.03f;		//透明度調整値の最小値

	static constexpr float MAX_ALPHA = 1.0f;			//透明度の最大値
	static constexpr float MIN_ALPHA = 0.5f;			//透明度の最小値

	//======== 状態フラグ =========

	//========= 動的変数 ==========
	float m_orbitRadius;							//円範囲上の初期座標と原点との距離
	
	Math::Vector2 m_bulletPos;						//ChargeBulletの座標
	Math::Vector2 m_bulletMove;						//ChargeBulletの移動量
	bool m_isBulletActive;							//ChargeBulletが有効かどうか

};