//ResultScene.h
#pragma once
#include "SceneBase.h"

class C_ResultScene:public C_SceneBase
{
public:
	C_ResultScene(){}
	~C_ResultScene(){}

	void Init()override;
	void Update()override;
	void Draw()override;
	void ImGui()override {}

private:

};
