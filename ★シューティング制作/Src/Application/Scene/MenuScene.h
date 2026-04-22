//MenuScene.h
#pragma once
#include "SceneBase.h"

class C_MenuScene:public C_SceneBase
{
public:
	C_MenuScene(){}
	~C_MenuScene(){}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ImGui()override {}

private:

};
