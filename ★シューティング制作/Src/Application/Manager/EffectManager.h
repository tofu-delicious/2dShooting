//EffectManager.h
#pragma once
#include "../Manager/TextureManager.h"
#include "../Effect/StaticElectricity.h"
#include "../Effect/ChargeAbsorption.h"
#include "../Effect/ShockWave.h"
#include "../Effect/Explosion.h"

class C_GameScene;

class C_EffectManager
{
public:
	
	~C_EffectManager() { Clear(); }

	static C_EffectManager& GetInstance()
	{
		static C_EffectManager Instance;
		return Instance;
	}

	void Init(C_GameScene* a_pGameScene)
	{
		Clear();

		//各エフェクトの最大領域を最初に確保
		for (int e = 0;e < MAX_ELEC;e++)
		{
			C_StaticElectricity* elec = new C_StaticElectricity();	//インスタンスを生成
			elec->Init(m_pGameScene);								//預かっているGameSceneを返す
			elec->SetTex(TEXTUREMANAGER.GetTex("StaticElec"));		//画像セット
			m_elecs.push_back(elec);								//リストに追加
		}

		for (int s = 0;s < MAX_SHOCK;s++)
		{
			C_ShockWave* shock = new C_ShockWave();					//インスタンスを生成
			shock->Init(m_pGameScene);								//預かっているGameSceneを渡す
			shock->SetTex(TEXTUREMANAGER.GetTex("ShockWave"));		//画像セット
			m_shocks.push_back(shock);								//リストに追加
		}

		for (int a = 0;a < MAX_ABSORPTION;a++)
		{
			C_ChargeAbsorption* charge = new C_ChargeAbsorption();
			charge->Init(m_pGameScene);
			charge->SetTex(TEXTUREMANAGER.GetTex("ChargeAbsorption"));
			m_absorptions.push_back(charge);
		}

		for (int x = 0;x < MAX_EXPLOSION;x++)
		{
			C_Explosion* explosion = new C_Explosion();;
			explosion->Init(m_pGameScene);
			explosion->SetTex(TEXTUREMANAGER.GetTex("Explosion"));
			m_explosions.push_back(explosion);
		}

		m_pGameScene = a_pGameScene;
	}

	//静電気を発生させる
	void CreateStaticElec(Math::Vector2 a_pos,float a_radiusX,float a_radiusY)
	{
		for (auto& elec : m_elecs)
		{
			//if (elec == nullptr)continue;

			if (!elec->IsActive())
			{
				elec->Activate(a_pos, a_radiusX, a_radiusY);
				return;
			}
		}
	}

	//衝撃波を発生させる
	void CreateShockWave(Math::Vector2 a_pos,float a_scaleX,float a_scaleY)
	{
		for (auto& shock : m_shocks)
		{
			if (shock == nullptr)continue;

			if (!shock->IsActive())
			{
				shock->Activate(a_pos, a_scaleX, a_scaleY);				//初期値を指定して表示状態へ移行
				return;
			}
		}
	}

	//吸い込みを発生させる
	void CreateAbsorption(Math::Vector2 a_pos,float a_radiusX,float a_radiusY)
	{
		
		for (auto& absorption : m_absorptions)
		{
			if (absorption == nullptr)continue;

			if (!absorption->IsActive())
			{
				absorption->Activate(a_pos, a_radiusX, a_radiusY);
				return;
			}
		}
	}

	//爆発を発生させる（主に敵撃破時）
	void CreateExplosion(Math::Vector2 a_pos)
	{
		for (auto& explosion : m_explosions)
		{
			if (explosion == nullptr)continue;

			if (!explosion->IsActive())
			{
				explosion->Activate(a_pos);
				return;
			}
		}
	}

	void Update()
	{
		for (auto& elec : m_elecs) if (elec && elec->IsActive()) elec->Update();
		for (auto& shock : m_shocks) if (shock && shock->IsActive()) shock->Update();
		for (auto& absorption : m_absorptions) if (absorption && absorption->IsActive()) absorption->Update();
		for (auto& explosion : m_explosions) if (explosion && explosion->IsActive()) explosion->Update();
	}

	void Draw()
	{
		D3D.SetBlendState(BlendMode::Add);	//加算合成モード

		for (auto& elec : m_elecs) if (elec && elec->IsActive()) elec->Draw();
		for (auto& shock : m_shocks) if (shock && shock->IsActive()) shock->Draw();
		for (auto& absorption : m_absorptions) if (absorption && absorption->IsActive()) absorption->Draw();
		for (auto& explosion : m_explosions) if (explosion && explosion->IsActive()) explosion->Draw();

		D3D.SetBlendState(BlendMode::Alpha);
	}

	void eImGui(){}

	void Clear()
	{
		for (auto& elec : m_elecs)
		{
			delete elec;
			elec = nullptr;
		}

		for (auto& shock : m_shocks)
		{
			delete shock;
			shock = nullptr;
		}

		for (auto& absorption : m_absorptions)
		{
			delete absorption;
			absorption = nullptr;
		}

		for (auto& explosion : m_explosions)
		{
			delete explosion;
			explosion = nullptr;
		}
	}

private:

	C_EffectManager() {}

	C_GameScene* m_pGameScene = nullptr;

	//=============== vector配列 ===============
	vector<C_StaticElectricity*> m_elecs;		//静電気エフェクトのリスト
	vector<C_ShockWave*> m_shocks;				//衝撃波エフェクトのリスト
	vector<C_ChargeAbsorption*>m_absorptions;	//吸い込みエフェクトのリスト
	vector<C_Explosion*>m_explosions;			//爆発エフェクトのリスト
	
	//================= 最大数 =================
	static constexpr int MAX_ELEC = 50;			//静電気の最大数
	static constexpr int MAX_SHOCK = 50;		//衝撃波の最大数
	static constexpr int MAX_ABSORPTION = 50;	//吸い込みエフェクトの最大数
	static constexpr int MAX_EXPLOSION = 50;	//爆発エフェクトの最大数
};

#define  EFFECTMANAGER C_EffectManager::GetInstance()