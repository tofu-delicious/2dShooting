//ResultScene.cpp
#include "ResultScene.h"

void C_ResultScene::Init()
{
}

void C_ResultScene::Update()
{
}

void C_ResultScene::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "ƒŠƒUƒ‹ƒg‰æ–Ê", Math::Vector4(1, 1, 0, 1));
}
