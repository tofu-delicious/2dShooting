//EffectBase.cpp
#include "../Scene/GameScene.h"
#include "EffectBase.h"

float C_EffectBase::CalcRadian(float a_deg)
{
	return DirectX::XMConvertToRadians(a_deg);
}

float C_EffectBase::Rnd(float a_min, float a_max)
{
	float range = a_max - a_min;
	float ratio = (float)rand() / RAND_MAX;

	//乱数を求める
	return a_min + (ratio * range);
}