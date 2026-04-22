//CharaBase.cpp
#include "EnemyBase.h"

float C_EnemyBase::CalcRadian(float a_deg)
{
    return DirectX::XMConvertToRadians(a_deg);
}

float C_EnemyBase::Rnd(float a_min, float a_max)
{
    float range = a_max - a_min;            //乱数の範囲の幅を算出
    float ratio = (float)rand() / RAND_MAX; //floatとintの演算は、暗黙のルールでfloatに桁数を合わせられる

    return a_min + (range * ratio);         //最小値に（乱数の幅 * その幅のうちの割合）を掛けることで、乱数値が得られる！
}

void C_EnemyBase::StartCoolTime(float a_seconds)
{
    m_coolTimeCount = a_seconds * FPS;
}

void C_EnemyBase::UpdateCoolTime()
{
    if (m_coolTimeCount > 0.0f) m_coolTimeCount -= 1.0f;
}

bool C_EnemyBase::IsReady()
{
    return m_coolTimeCount <= 0.0f;
}
