//Explosion.h
#pragma once
#include "EffectBase.h"

//前方宣言
class C_GameScene;

using namespace std;

class C_Explosion:public C_EffectBase
{
public:
	C_Explosion(){}
	~C_Explosion(){}

	void Init(C_GameScene* a_pGameScene) override;
	void Update(const Math::Vector2& a_centerPos = { 0,0 })override;
	void Draw()override;

public:

	//行列プログラムをまとめる関数
	void UpdateMatrix();

	//ShockWaveの表示処理
	void Activate(Math::Vector2 a_pos);

	//非表示処理
	void Deactive();

	//描画範囲の変更
	void CalcDrawRange();

	//フェード処理
	void Fade();

	//初期状態に戻す
	void ResetToDefault();

	//========= セッター ==========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }

	//========= ゲッター ==========
	bool IsActive()override { return m_isActive; }
	//ラベルを取得
	EffectType GetType()override { return EffectType::Exp; }

	//========= デバッグ ==========
	void eImGui() {}

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;		//GameSceneクラスのインスタンスを取得

	//======= 定数・設定値 ========

	//======== 状態フラグ =========

	//========= 動的変数 ==========

};