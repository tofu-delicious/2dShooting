//TitleScene.h
#pragma once
#include "SceneBase.h"

class C_TitleScene:public C_SceneBase
{
public:
	C_TitleScene(){}
	~C_TitleScene(){}

	void Init() override;
	void Update() override;
	void Draw() override;
	void ImGui()override{}

private:

};