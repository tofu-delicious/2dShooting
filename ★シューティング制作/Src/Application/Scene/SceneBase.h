//SceneBase.h
#pragma once

class C_SceneBase
{
public:
	C_SceneBase(){}
	~C_SceneBase(){}

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void ImGui() = 0;

private:

};
