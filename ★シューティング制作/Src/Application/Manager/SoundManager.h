//SoundManager.h
#pragma once

enum class SoundType
{
	SE,
	BGM
};

class C_GameScene;

using namespace std;

class C_SoundManager
{
public:
	~C_SoundManager(){}

	static C_SoundManager& GetInstance()
	{
		static C_SoundManager Instance;
		return Instance;
	}

	void Init(C_GameScene *a_pGameScene)
	{
		//=============== SE ================
		Load("Shot", "Sound/ShotChargeBullet.wav", SoundType::SE);
		Load("Charge", "Sound/Charging.wav", SoundType::SE);

		//============== BGM ================

		m_pGameScene = a_pGameScene;
	}

	//引数の音をロードする
	void Load(const string& a_soundName, const string& a_filePath, const SoundType& a_soundType, bool a_isInstance = false)
	{
		//➀領域確保
		auto newSound = make_shared<KdSoundEffect>();

		//➁音データを読み込む
		newSound->Load(a_filePath);

		//➂実体か（インスタンス化）
		auto newInst = newSound->CreateInstance(a_isInstance);

		//➃音量設定（0から1の段階で）
		if (a_soundType == SoundType::SE) newInst->SetVolume(m_seVolume);
		else newInst->SetVolume(m_bgmVolume);

		//➄ロード情報を記録
		m_typeMap.insert({ a_soundName, a_soundType });
		m_soundMap.insert({a_soundName,newSound});
		m_instMap.insert({ a_soundName,newInst });
	}
	
	//引数に指定した音を鳴らす
	void Play(const string& a_soundName,bool a_loop = false)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			m_instMap[a_soundName]->Play(a_loop);
		}
	}

	//引数に指定した音を停止させる
	void Stop(const string& a_soundName)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			m_instMap[a_soundName]->Stop();
		}
	}

	//引数に指定した音を一時停止させる
	void Pause(const string& a_soundName)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			m_instMap[a_soundName]->Pause();
		}
	}

	//引数に指定した音を一時停止したところから再生させる
	void Resume(const string& a_soundName)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			m_instMap[a_soundName]->Resume();
		}
	}

	//引数に指定した音の音量を引数の数値に反映させる
	void Volume(const string& a_soundName, float a_volume)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			m_instMap[a_soundName]->SetVolume(a_volume);
		}
	}

	//SE,BGMといった分類ごとの音を一気に調整する
	void GroupVolume(const SoundType& a_soundType, float a_volume)
	{
		if (a_soundType == SoundType::SE)
		{
			m_seVolume = a_volume;
		}
		else
		{
			m_bgmVolume = a_volume;
		}
	}

	//現在、引数の音が再生されているかどうかを確認
	bool IsPlay(const string& a_soundName)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			if (m_instMap[a_soundName]->IsPlay())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	//現在、引数の音が一時停止されているかどうかを確認
	bool IsPause(const string& a_soundName)
	{
		if (m_instMap.count(a_soundName) > 0)
		{
			if (m_instMap[a_soundName]->IsPause())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	

private:

	unordered_map<string, SoundType>m_typeMap;						//引数の音がSEなのかBGMなのか分類するため
	unordered_map<string,shared_ptr<KdSoundEffect>> m_soundMap;		//音データ（波形）を「名前」というラベルを付けて保存する
	unordered_map<string, shared_ptr<KdSoundInstance>> m_instMap;	//実際に音を鳴らすスピーカーを「名前」で管理する

	C_SoundManager(){}

	C_GameScene* m_pGameScene = nullptr;

	float m_seVolume = 0.5f;
	float m_bgmVolume = 0.2f;

};

#define SOUNDMANAGER C_SoundManager::GetInstance() 