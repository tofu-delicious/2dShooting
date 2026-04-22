//TextureManager
#pragma once
#include <string>
#include <fstream>

class C_GameScene;

using namespace std;

class C_TextureManager
{
public:
	~C_TextureManager(){}

	static C_TextureManager& GetInstance() {
		static C_TextureManager Instance;
		return Instance;
	}

	//引数のテキストファイルをスペース区切りで1行ずつ読み込む
	void ReadFile(const string&a_filename)
	{
		ifstream ifs(a_filename);
		string name, path;

		if (!ifs)return;

		while (getline(ifs, name, ' ') && getline(ifs, path))
		{
			LoadTex(name, path);
		}
	}

	//画像ロード
	void LoadTex(const string& key, const string& filePath)
	{
		if (m_texMap.count(key) > 0)return;
		m_texMap[key].Load(filePath);
	}

	//画像データ取得
	KdTexture* GetTex(const string& key)
	{
		if (m_texMap.count(key) > 0) return &m_texMap[key];
		return nullptr;
	}

private:
	C_TextureManager() {}

	C_GameScene* m_pGameScene = nullptr;

	unordered_map<string, KdTexture> m_texMap;
};

#define TEXTUREMANAGER C_TextureManager::GetInstance()