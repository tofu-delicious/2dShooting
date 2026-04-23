//ShockWave.h
#pragma once
#include "EffectBase.h"

//前方宣言
class C_GameScene;

using namespace std;

class C_ShockWave:public C_EffectBase
{
public:
	C_ShockWave(){}
	~C_ShockWave(){}

	void Init(C_GameScene *a_pGameScene)override;
	void Update()override;
	void Draw()override;
	
	//行列プログラムをまとめる関数
	void UpdateMatrix();

	//ShockWaveの表示処理
	void Activate(Math::Vector2 a_pos,float a_scaleX,float a_scaleY);

	//ShockWaveを拡大させる
	void ExpandShockWave();

	//フェード処理
	void Fade();

	//ShockWaveを初期状態に戻す
	void ResetToDefault();

	//========= セッター ==========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }

	//========= ゲッター ==========
	bool IsActive()override { return m_isActive; }
	//ラベルを取得
	EffectType GetType()override { return EffectType::Shock; }

	//========= デバッグ ==========
	void eImGui() {}

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;		//GameSceneクラスのインスタンスを取得

	//======= 定数・設定値 ========
	static constexpr float FPS = 60.0f;			//1秒間当たりのフレーム数
	static constexpr float SCALE_SPEED = 0.2f;	//「ShockWave.m_scale」を増やす数値
	static constexpr float ALPHA_SPEED = -0.08f;//「ShockWave.m_alpha」を減らす数値
	
	//======== 状態フラグ =========

	//========= 動的変数 ==========

};