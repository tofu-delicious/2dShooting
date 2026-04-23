//StaticElectricity.h
#pragma once
#include "EffectBase.h"

//前方宣言
class C_GameScene;
class C_ChargeBullet;

using namespace std;

class C_StaticElectricity:public C_EffectBase
{
public:
	C_StaticElectricity(){}
	~C_StaticElectricity(){}

	void Init(C_GameScene* a_pGameScene) override;
	void Update()override;
	void Draw()override;

	//行列計算
	void UpdateMatrix();

	//表示処理
	void Activate(Math::Vector2 a_pos,float a_radiusX,float a_radiusY);

	//非表示処理
	void Deactivate();

	//拡大率の変更
	void ElecScaledChange(float a_scale);

	//描画位置の特定
	void CalcDrawPos(Math::Vector2 a_centerPos, float a_radiusX, float a_radiusY);

	//描画範囲の変更
	void CalcDrawRange();

	//変数「AnimationCnt」をランダム指定する
	void CalcAnimationCnt();

	//描画の方向（向き）の変更
	void CalcDrawAngle();

	//描画の透明度の変更
	void CalcDrawAlpha();

	//エフェクトの動きを定義する（円を描くように移動）
	void MoveElec();

	//========= セッター ==========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }

	//========= ゲッター ==========
	bool IsActive()override { return m_isActive; }
	//ラベルを取得
	EffectType GetType()override { return EffectType::StaticElec; }

	//========= デバッグ ==========
	void eImGui(){}

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;				//GameSceneクラスのインスタンスを格納する
	C_ChargeBullet* m_pChargeBullet = nullptr;			//ChargeBulletクラスのインスタンスを格納する

	//======= 定数・設定値 ========
	static constexpr float ANIM_SPEED = 0.2f;			//静電気アニメーションのスピード
	static constexpr int ROTATION_DEG = 45;				//CalcDrawPos関数内で使用
	static constexpr float ELEC_ROTATION_SPEED = 10.0f;	//静電気アニメーションの回転速度
	static constexpr float ELEC_ABSORPTION_SPEED = 1.5f;//静電気アニメーションの中央へ吸い込まれる速度
	static constexpr float ELEC_RADIUS_MARGIN = 10.0f;	//基準とする「radius」変数からの余白
	static constexpr float ELEC_SCALE_OFFSET = 0.5f;	//基準とする「scale」変数を調整する
	static constexpr float MAX_ELEC_ROTATE = 7.0f;		//静電気の回転速度の最大値
	static constexpr float MIN_ELEC_ROTATE = 3.0f;		//静電気の回転速度の最小値
	
	//======== 状態フラグ =========
	//ChargeBullet関連
	bool m_isBulletActive;						//ChargeBulletが有効かどうか
	bool m_isCharging;							//ChargeBulletがチャージ中かつ、移動していなければtrueを返す

	//========= 動的変数 ==========
	//ChargeBullet関連
	Math::Vector2 m_bulletPos;					//ChargeBulletの座標情報
	Math::Vector2 m_bulletMove;					//ChargeBulletの移動量
	float m_bulletScale;						//ChargeBulletの拡大率
};