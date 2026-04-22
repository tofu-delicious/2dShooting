//GameSettingScene.h
#pragma once
#include "SceneBase.h"

class C_GameSettingScene:public C_SceneBase
{
public:
	C_GameSettingScene(){}
	~C_GameSettingScene(){}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ImGui()override {}

private:

};