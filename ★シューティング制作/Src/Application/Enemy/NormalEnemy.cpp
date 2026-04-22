//NormalEnemy.cpp
#include "../Scene/GameScene.h"
#include "NormalEnemy.h"

void C_NormalEnemy::Init(C_GameScene* a_pGameScene)
{
	m_pos = { 0,200 };								//座標
	m_move = { 0,0 };								//移動量

	m_rect = { 0,0,64,64 };							//画像範囲指定
	m_radiusX = 32.0f;								//X軸方向の半径
	m_radiusY = 32.0f;								//Y軸方向の半径
	m_scaleX = 1.0f;								//X軸方向の拡縮
	m_scaleY = 1.0f;								//Y軸方向の拡縮
	m_rotate = 0.0f;								//回転角度
	m_alpha = 1.0f;									//不透明度
	//m_fadeStep;									//フェード用
	m_isActive = true;								//true 表示　false 非表示

	m_pGameScene = a_pGameScene;
}

void C_NormalEnemy::Update()
{
	UpdateCoolTime();

	MoveEnemy();

	AttackEnemy();

	BenefitPlayer();

	UpdateMatrix();
}

void C_NormalEnemy::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_NormalEnemy::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_mat = m_scaleMat * m_transMat;
}

void C_NormalEnemy::Activate()
{
	m_isActive = true;		//表示状態へ移行
	m_pos = { Rnd(100,1280),Rnd(100,200) };
	m_move = { 0.0f,0.0f };
}

void C_NormalEnemy::MoveEnemy()
{
	m_rotate += 3.0f;
	if (m_rotate >= 360.0f) m_rotate -= 360.0f;

	m_pos.x = sinf(CalcRadian(m_rotate)) * 100;
}

void C_NormalEnemy::AttackEnemy()
{
	if (CanShootBullet())
	{
		BULLETMANAGER.CreateEnemyBullet(m_pos);
		StartCoolTime(COOLTIME);
	}
}

void C_NormalEnemy::BenefitPlayer()
{
}

bool C_NormalEnemy::CanShootBullet()
{
	return IsReady() && m_isActive;
}

void C_NormalEnemy::OnHit()
{
	m_isActive = false;
	EFFECTMANAGER.CreateExplosion(m_pos);
}
