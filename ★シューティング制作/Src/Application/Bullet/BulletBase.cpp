//BulletBase.cpp
#include "../Manager/EffectManager.h"
#include "BulletBase.h"

float C_BulletBase::CalcRadian(float a_deg)
{
	return DirectX::XMConvertToRadians(a_deg);
}
