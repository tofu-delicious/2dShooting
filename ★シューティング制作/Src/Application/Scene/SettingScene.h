//SettingScene.h
#pragma once
#include "SceneBase.h"

class C_SettingScene:public C_SceneBase
{
public:
	C_SettingScene(){}
	~C_SettingScene(){}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ImGui()override {}

private:

};