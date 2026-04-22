//SettingScene.cpp
#include "SettingScene.h"

void C_SettingScene::Init()
{
}

void C_SettingScene::Update()
{
}

void C_SettingScene::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "İ’è‰æ–Ê", Math::Vector4(1, 1, 0, 1));
}
