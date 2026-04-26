//Boss.cpp
#include "Boss.h"

void C_Boss::Init(C_GameScene* a_pGameScene)
{
	m_pos = { 0,200 };						//座標
	m_move = { 0,0 };						//移動量

	m_rect = { 0,0,64,64 };					//画像範囲指定
	m_radiusX = 32.0f;						//X軸方向の半径
	m_radiusY = 32.0f;						//Y軸方向の半径
	m_scaleX = 1.0f;						//X軸方向の拡縮
	m_scaleY = 1.0f;						//Y軸方向の拡縮
	m_rotate = 0.0f;						//回転角度
	m_alpha = 1.0f;							//不透明度
	//m_fadeStep;							//フェード用
	m_isActive = false;						//true 表示　false 非表示

	m_pGameScene = a_pGameScene;
}

void C_Boss::Action(const Math::Vector2& a_playerPos)
{
	ChangeAction();

	AttackEnemy();

	BenefitPlayer();
}

void C_Boss::Update()
{
	CommitMove();

	UpdateMatrix();
}

void C_Boss::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_Boss::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_mat = m_scaleMat * m_transMat;
}

void C_Boss::Activate()
{
	m_pos = { 600,200 };
	m_move = { 0,0 };
	m_isActive = true;
}

void C_Boss::ChangeAction(const Math::Vector2& a_playerPos)
{
}

void C_Boss::AttackEnemy()
{
}

void C_Boss::BenefitPlayer()
{
}

void C_Boss::OnHit()
{
}
