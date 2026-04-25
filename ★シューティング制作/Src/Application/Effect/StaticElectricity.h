//StaticElectricity.h
#pragma once
#include "EffectBase.h"

//前方宣言
class C_GameScene;

using namespace std;

class C_StaticElectricity:public C_EffectBase
{
public:
	C_StaticElectricity() { m_isActive = false; }
	~C_StaticElectricity()override{}

	void Init(C_GameScene* a_pGameScene) override;
	void Update(const Math::Vector2& a_centerPos = { 0,0 })override;
	void Draw()override;

	//行列計算
	void UpdateMatrix();

	//表示処理
	void Activate(Math::Vector2 a_pos,float a_radiusX,float a_radiusY);

	//非表示処理
	void Deactivate();

	//拡大率の変更
	void ElecScaledChange(const float& a_scale);

	//描画位置の特定
	void CalcDrawPos(Math::Vector2 a_centerPos, float a_radiusX, float a_radiusY);

	//描画範囲の変更
	void CalcDrawRange();

	//エフェクトの動きを定義する（円を描くように移動）
	void MoveElec(const Math::Vector2 &a_centerPos);

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

	//======= 定数・設定値 ========
	static constexpr float ANIM_SPEED = 0.2f;			//静電気アニメーションのスピード
	static constexpr int ROTATION_DEG = 45;				//CalcDrawPos関数内で使用
	static constexpr float ELEC_ROTATION_SPEED = 10.0f;	//静電気アニメーションの回転速度
	static constexpr float ELEC_ABSORPTION_SPEED = 1.5f;//静電気アニメーションの中央へ吸い込まれる速度
	static constexpr float ELEC_RADIUS_MARGIN = 10.0f;	//基準とする「radius」変数からの余白
	static constexpr float MAX_SCALE = 2.5f;			//scaleの上限値
	static constexpr float SCALE_SPEED = 0.01f;			//scaleの拡大値
	static constexpr float MAX_ELEC_ROTATE = 7.0f;		//静電気の回転速度の最大値
	static constexpr float MIN_ELEC_ROTATE = 3.0f;		//静電気の回転速度の最小値
	static constexpr float MAX_ANIMATION = 10.0f;		//アニメーションの最大値
	static constexpr float MIN_ANIMATION = 0.0f;		//アニメーションの最大値
	static constexpr float MAX_DEG = 360.0f;			//描画角度の最大値
	static constexpr float MIN_DEG = 0.0f;				//描画角度の最小値
	static constexpr float MAX_ALPHA = 1.0f;			//描画の最大不透明度
	static constexpr float MIN_ALPHA = 0.2f;			//描画の最小不透明度
	
	//======== 状態フラグ =========

	//========= 動的変数 ==========
};