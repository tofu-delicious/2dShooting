//EnemyBullet.cpp
#include "../Scene/GameScene.h"
#include "EnemyBullet.h"

void C_EnemyBullet::Init(C_GameScene* a_pGameScene)
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.0f };
	m_radiusX = 16.0f;
	m_radiusY = 16.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_alpha = 1.0f;
	m_rect = { 0,0,32,32 };
	m_isActive = false;

	m_pGameScene = a_pGameScene;
}

void C_EnemyBullet::Update()
{
	m_pos += m_move;

	RotateLoop(INCREASE_ANGLE);

	if (IsOutOfBounds())ResetToDefault();

	UpdateMatrix();
}

void C_EnemyBullet::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_EnemyBullet::Activate(Math::Vector2 a_pos)
{
	m_pos = { a_pos.x,a_pos.y - OFFSET_Y };
	m_move = { 0.0f,-MOVE_SPEED_Y };
	m_rotate = 0.0f;

	m_isActive = true;
}

void C_EnemyBullet::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_rotateMat = Math::Matrix::CreateRotationZ(CalcRadian(m_rotate));
	m_mat = m_rotateMat * m_scaleMat * m_transMat;
}

bool C_EnemyBullet::IsOutOfBounds()
{
	return m_pos.y < SCREENDOWN - m_radiusY;
}

void C_EnemyBullet::ResetToDefault()
{
	m_move.y = 0.0f;
	m_radiusX = 16.0f;
	m_radiusY = 16.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_isActive = false;
}

void C_EnemyBullet::RotateLoop(const float& INCREASE_ANGLE)
{
	if (m_rotate < MAX_ANGLE)
	{
		m_rotate += INCREASE_ANGLE;
	}
	else
	{
		m_rotate -= MAX_ANGLE;
	}
}
