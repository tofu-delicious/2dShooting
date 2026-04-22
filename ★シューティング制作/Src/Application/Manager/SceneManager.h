//SceneManager.h
#pragma once
#include "Scene/TitleScene.h"
#include "Scene/SettingScene.h"
#include "Scene/GameSettingScene.h"
#include "Scene/GameScene.h"
#include "Scene/MenuScene.h"
#include "Scene/ResultScene.h"

class C_SceneManager
{
public:
	
	~C_SceneManager(){}

	static C_SceneManager& GetInstance()
	{
		static C_SceneManager Instance;
		return Instance;
	}

	void ChangeState(C_SceneBase* newState)
	{
		delete currentState;	//ˆê‰ñ’†gíœ
		currentState = newState;

		currentState->Init();
	}

	void Update()
	{
		currentState->Update();
	}

	void Draw()
	{
		currentState->Draw();
	}

	void ImGui()
	{
		currentState->ImGui();
	}

private:

	C_SceneManager() {}
	
	C_SceneBase* currentState = nullptr;

};

#define  SCENEMANAGER C_SceneManager::GetInstance()

/*
ƒƒƒ‚„
E


*/