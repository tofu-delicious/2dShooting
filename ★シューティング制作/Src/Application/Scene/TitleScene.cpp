//TitleScene.cpp
#include"TitleScene.h"

void C_TitleScene::Init()
{
}

void C_TitleScene::Update()
{
}

void C_TitleScene::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "ƒ^ƒCƒgƒ‹‰æ–Ê", Math::Vector4(1, 1, 0, 1));
}
