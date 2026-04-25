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

		for (auto& elec : m_elec)
		{
			elec.Init(m_pGameScene);
			elec.SetTex(TEXTUREMANAGER.GetTex("StaticElec"));
		}

		for (auto& shock : m_shock)
		{
			shock.Init(m_pGameScene);
			shock.SetTex(TEXTUREMANAGER.GetTex("ShockWave"));
		}

		for (auto& abs : m_abs)
		{
			abs.Init(m_pGameScene);
			abs.SetTex(TEXTUREMANAGER.GetTex("ChargeAbsorption"));
		}

		for (auto& exp : m_exp)
		{
			exp.Init(m_pGameScene);
			exp.SetTex(TEXTUREMANAGER.GetTex("Explosion"));
		}
	}

	//静電気を発生させる
	void EmitStaticElec(Math::Vector2 a_pos, float a_radiusX, float a_radiusY)
	{
		for (int e = 0;e < MAX_ELEC;e++)
		{
			if (!m_elec[e].IsActive())
			{
				m_elec[e].Activate(a_pos, a_radiusX, a_radiusY);
				return;
			}
		}
	}

	//衝撃波を発生させる
	void EmitShockWave(Math::Vector2 a_pos,float a_scaleX,float a_scaleY)
	{
		for (int s = 0;s < MAX_SHOCK;s++)
		{
			if (!m_shock[s].IsActive())
			{
				m_shock[s].Activate(a_pos, a_scaleX, a_scaleY);
				return;
			}
		}
	}

	//吸い込みを発生させる
	void EmitAbsorption(Math::Vector2 a_pos,float a_radiusX,float a_radiusY)
	{
		for (int a = 0;a < MAX_ABSORPTION;a++)
		{
			if (!m_abs[a].IsActive())
			{
				m_abs[a].Activate(a_pos, a_radiusX, a_radiusY);
				return;
			}
		}
	}

	//爆発を発生させる（主に敵撃破時）
	void EmitExplosion(Math::Vector2 a_pos)
	{
		for (int x = 0;x < MAX_EXP;x++)
		{
			if (!m_exp[x].IsActive())
			{
				m_exp[x].Activate(a_pos);
				return;
			}
		}
	}

	//静電気を非表示にする
	void DeleteStaticElec()
	{
		for (int e = 0;e < MAX_ELEC;e++)if (m_elec[e].IsActive()) m_elec[e].Deactivate();
	}

	//衝撃波を非表示にする
	void DeleteShockWave()
	{
		for (int s = 0;s < MAX_SHOCK;s++) if (m_shock[s].IsActive()) m_shock[s].Deactivate();
	}

	//吸い込みを非表示にする
	void DeleteChargeAbsorption()
	{
		for (int a = 0;a < MAX_ABSORPTION;a++) if (m_abs[a].IsActive()) m_abs[a].Deactivate();
	}

	//爆発を非表示にする
	void DeleteExplosion()
	{
		for (int x = 0;x < MAX_EXP;x++) if (m_exp[x].IsActive()) m_exp[x].Deactivate();
	}

	void Update(const Math::Vector2 &a_centerPos)
	{
		for (auto& elec : m_elec) if (elec.IsActive()) elec.Update(a_centerPos);
		for (auto& shock : m_shock) if (shock.IsActive()) shock.Update(a_centerPos);
		for (auto& abs : m_abs) if (abs.IsActive()) abs.Update(a_centerPos);
		for (auto& exp : m_exp) if (exp.IsActive()) exp.Update(a_centerPos);
	}

	void Draw()
	{
		D3D.SetBlendState(BlendMode::Add);	//加算合成モード

		for (auto& elec : m_elec)if(elec.IsActive()) elec.Draw();

		D3D.SetBlendState(BlendMode::Alpha);

		for (auto& shock : m_shock)if (shock.IsActive()) shock.Draw();
		for (auto& abs : m_abs)if (abs.IsActive()) abs.Draw();
		for (auto& exp : m_exp)if (exp.IsActive()) exp.Draw();
	}

	void eImGui(){}

private:

	C_EffectManager() {}

	C_GameScene* m_pGameScene = nullptr;

	//=============== vector配列 ===============
	vector<unique_ptr<C_EffectBase>>m_effects;	//全エフェクトを管理するクラス
	
	//================= 最大数 =================
	static constexpr int MAX_ELEC = 15;			//静電気の最大数
	static constexpr int MAX_SHOCK = 1;			//衝撃波の最大数
	static constexpr int MAX_ABSORPTION = 30;	//吸い込みエフェクトの最大数
	static constexpr int MAX_EXP = 50;			//爆発エフェクトの最大数

	//================== 配列 ==================
	//起動時にコンストラクタが走る
	C_StaticElectricity m_elec[MAX_ELEC];
	C_ShockWave m_shock[MAX_SHOCK];
	C_ChargeAbsorption m_abs[MAX_ABSORPTION];
	C_Explosion m_exp[MAX_EXP];
};

#define  EFFECTMANAGER C_EffectManager::GetInstance()