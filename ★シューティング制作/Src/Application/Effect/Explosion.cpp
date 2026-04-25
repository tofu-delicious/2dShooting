//Explosion.cpp
#include "Explosion.h"

void C_Explosion::Init(C_GameScene* a_pGameScene)
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.0f };
	m_radiusX = 32.0f;
	m_radiusY = 32.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_alpha = 1.0f;
	m_fadeStep = -0.01f;
	m_rect = { 0,0,0,0 };
	m_AnimationCnt = 0.0f;
	m_orbitRadius = 0.0f;
	m_isActive = false;

	m_pGameScene = a_pGameScene;
}

void C_Explosion::Update(const Math::Vector2& a_centerPos)
{
	//描画範囲変更
	CalcDrawRange();

	//行列
	UpdateMatrix();
}

void C_Explosion::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_Explosion::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_mat = m_scaleMat * m_transMat;
}

void C_Explosion::Activate(Math::Vector2 a_pos)
{
	m_pos = { a_pos.x,a_pos.y };
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_alpha = 1.0f;
	m_rect = { 0,0,64,64 };

	m_isActive = true;
}

void C_Explosion::Deactive()
{
	m_isActive = false;
}

void C_Explosion::CalcDrawRange()
{
	m_AnimationCnt += 0.01f;
	m_rect = { (int)m_AnimationCnt * 64,0,64,64 };
}

void C_Explosion::Fade()
{
}

void C_Explosion::ResetToDefault()
{
}
