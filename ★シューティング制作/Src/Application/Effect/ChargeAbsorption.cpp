//ChargeAbsorption.cpp
#include "../Scene/GameScene.h"
#include "ChargeAbsorption.h"

void C_ChargeAbsorption::Init(C_GameScene *a_pGameScene)
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,10.0f };
	m_radiusX = 8.0f;
	m_radiusY = 8.0f;
	m_scaleX = 0.0f;
	m_scaleY = 0.0f;
	m_rotate = 0.0f;
	m_alpha = 1.0f;
	m_fadeStep = -0.02f;
	m_rect = { 0,0,16,16 };
	m_isActive = true;

	m_pGameScene = a_pGameScene;
}

void C_ChargeAbsorption::Update(const Math::Vector2 &a_centerPos)
{
	////ChargeBulletの情報を取得
	//m_pChargeBullet = BULLETMANAGER.GetChargeBullet();

	//if (m_pChargeBullet != nullptr)
	//{
	//	m_bulletPos = m_pChargeBullet->GetPos();				//座標を取得
	//	m_bulletMove = m_pChargeBullet->GetMove();				//移動量を取得
	//	m_isBulletActive = m_pChargeBullet->IsActive();			//変数「m_isActive」の真偽値を取得
	//}

	//bool isCharging = (m_isBulletActive && m_bulletMove.y == 0.0f);	//チャージ攻撃が表示状態かつ、発射していなければtrueを返す

	////光の粒子の非表示処理（ChargeBulletがチャージ中でない場合は非表示にする）
	//if (!isCharging) Deactivate();

	MoveAbsorption(a_centerPos);

	UpdateMatrix();
}

void C_ChargeAbsorption::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_ChargeAbsorption::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_rotateMat = Math::Matrix::CreateRotationZ(CalcRadian(m_rotate));
	m_mat = m_rotateMat * m_scaleMat * m_transMat;
}

void C_ChargeAbsorption::Activate(Math::Vector2 a_pos, float a_radiusX, float a_radiusY)
{
	m_scaleX = INITIAL_SCALE;
	m_scaleY = INITIAL_SCALE;
	CalcDrawPos(a_pos, a_radiusX, a_radiusY);				//初期座標取得

	m_rotate = Rnd(MIN_ROTATE, MAX_ROTATE);					//角度を取得
	m_alpha = Rnd(MIN_ALPHA, MAX_ALPHA);					//透明度取得
	m_fadeStep = Rnd(MIN_FADE_STEP, MAX_FADE_STEP);			//透明度調整値を取得
	m_isActive = true;
}

void C_ChargeAbsorption::Deactivate()
{
	m_isActive = false;

	m_pos = { 0.0f,0.0f };
	m_alpha = 0.0f;
	m_fadeStep = -0.02f;
}

void C_ChargeAbsorption::CalcDrawPos(Math::Vector2 a_pos, float a_radiusX, float a_radiusY)
{
	float lowDeg = 0.0f;
	float highDeg = 360.0f;

	//ランダムな角度を求める
	float randomDeg = Rnd(lowDeg, highDeg);
	float radian = CalcRadian(randomDeg);

	//ランダムな半径を求める
	m_orbitRadius = Rnd(a_radiusX - SPAWN_RADIUS_OFFSET, a_radiusX);

	//座標確定処理
	m_pos.x = a_pos.x + cosf(radian) * m_orbitRadius;
	m_pos.y = a_pos.y + sinf(radian) * m_orbitRadius;
}

void C_ChargeAbsorption::MoveAbsorption(const Math::Vector2 &a_centerPos)
{
	//更新処理
	m_rotate += ROTATION_SPEED;					//回転速度
	float radian = CalcRadian(m_rotate);		//ラジアン値が大きくなるほど回転速度は上がるみたい

	m_orbitRadius -= ABSORPTION_SPEED;			//半径を減らす（徐々に中央に近づいていく感じになる！）
	if (m_orbitRadius < 0.0f)
	{
		m_orbitRadius = 0.0f;
	}

	//移動量を算出する
	m_pos.x = a_centerPos.x + cosf(radian) * m_orbitRadius;
	m_pos.y = a_centerPos.y + sinf(radian) * m_orbitRadius;
}

void C_ChargeAbsorption::Fade()
{
	m_alpha += m_fadeStep;

	if (m_alpha <= 0.0f)
	{
		m_alpha = 0.0f;
		Deactivate();
	}
}

float C_ChargeAbsorption::Rnd(float a_min, float a_max)
{
	float range = a_max - a_min;
	float ratio = (float)rand() / RAND_MAX;

	//乱数を求める
	return a_min + (ratio * range);
}