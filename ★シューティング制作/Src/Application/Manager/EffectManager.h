//EffectManager.h
#pragma once
#include "../Manager/TextureManager.h"
#include "../Effect/StaticElectricity.h"
#include "../Effect/ChargeAbsorption.h"
#include "../Effect/ShockWave.h"
#include "../Effect/Explosion.h"
#include<memory>

using namespace std;

class C_GameScene;

class C_EffectManager
{
public:
	
	~C_EffectManager() {}

	static C_EffectManager& GetInstance()
	{
		static C_EffectManager Instance;
		return Instance;
	}

	void Init(C_GameScene* a_pGameScene)
	{
		//GameScene型のポインタを取得
		m_pGameScene = a_pGameScene;
	}

	//静電気を発生させる
	void CreateStaticElec(Math::Vector2 a_pos, float a_radiusX, float a_radiusY)
	{
		if (CountEffectNum(EffectType::StaticElec) < MAX_ELEC)
		{
			auto elec = make_unique<C_StaticElectricity>();			//インスタンスを生成
			elec->Init(m_pGameScene);								//預かっているGameSceneを返す
			elec->SetTex(TEXTUREMANAGER.GetTex("StaticElec"));		//画像セット
			elec->Activate(a_pos, a_radiusX, a_radiusY);
			m_effects.push_back(move(elec));	//リストに追加
		}
	}

	//衝撃波を発生させる
	void CreateShockWave(Math::Vector2 a_pos,float a_scaleX,float a_scaleY)
	{
		if(CountEffectNum(EffectType::Shock) < MAX_SHOCK)
		{
			auto shock = make_unique<C_ShockWave>();				//インスタンスを生成
			shock->Init(m_pGameScene);								//預かっているGameSceneを渡す
			shock->SetTex(TEXTUREMANAGER.GetTex("ShockWave"));		//画像セット
			shock->Activate(a_pos, a_scaleX, a_scaleY);				//初期値を指定して表示状態へ移行
			m_effects.push_back(move(shock));								//リストに追加
		}
	}

	//吸い込みを発生させる
	void CreateAbsorption(Math::Vector2 a_pos,float a_radiusX,float a_radiusY)
	{
		if(CountEffectNum(EffectType::Absorption) < MAX_ABSORPTION)
		{
			auto absorption = make_unique<C_ChargeAbsorption>();
			absorption->Init(m_pGameScene);
			absorption->SetTex(TEXTUREMANAGER.GetTex("ChargeAbsorption"));
			absorption->Activate(a_pos, a_radiusX, a_radiusY);
			m_effects.push_back(move(absorption));
		}
	}

	//爆発を発生させる（主に敵撃破時）
	void CreateExplosion(Math::Vector2 a_pos)
	{
		if(CountEffectNum(EffectType::Exp)< MAX_EXPLOSION)
		{
			auto explosion = make_unique<C_Explosion>();
			explosion->Init(m_pGameScene);
			explosion->SetTex(TEXTUREMANAGER.GetTex("Explosion"));
			explosion->Activate(a_pos);
			m_effects.push_back(move(explosion));
		}
	}

	void Update(const Math::Vector2 &a_centerPos)
	{
		for (auto& effect : m_effects)
		{
			if (effect && effect->IsActive())
			{
				effect->Update(a_centerPos);
			}
		}
	}

	void Draw()
	{
		D3D.SetBlendState(BlendMode::Add);	//加算合成モード

		for (auto& effect : m_effects) if (effect) effect->Draw();

		D3D.SetBlendState(BlendMode::Alpha);
	}

	//引数のTypeがm_effects内にいくつ存在しているかを数える関数
	int CountEffectNum(const EffectType& a_effectType)
	{
		int activeCount = (int)count_if(m_effects.begin(), m_effects.end(), [a_effectType](const unique_ptr<C_EffectBase>& effect) {
			return effect && effect->IsActive() && effect->GetType() == a_effectType; // 中身があって、かつActiveなやつをカウント
			});

		return activeCount;
	}

	void eImGui(){}

private:

	C_EffectManager() {}

	C_GameScene* m_pGameScene = nullptr;

	//=============== vector配列 ===============
	vector<unique_ptr<C_EffectBase>>m_effects;	//全エフェクトを管理するクラス
	
	//================= 最大数 =================
	static constexpr int MAX_ELEC = 20;			//静電気の最大数
	static constexpr int MAX_SHOCK = 1;			//衝撃波の最大数
	static constexpr int MAX_ABSORPTION = 40;	//吸い込みエフェクトの最大数
	static constexpr int MAX_EXPLOSION = 50;	//爆発エフェクトの最大数
};

#define  EFFECTMANAGER C_EffectManager::GetInstance()

/*
〇ラムダ式
★ラムダ式とは？
　関数のようにその都度定義を行わなくても、その場で処理を記述すること。

★ラムダ式の書式
　[ ] ( ) { 処理 }
・[ ]キャプチャ：外側にある変数をラムダ式の中で使いたいときに使用する
・( )　 引数   ：普通の関数と同様、引数のこと。
・　　　処理   ：判定結果
*/