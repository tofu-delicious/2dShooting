//ShockWave.cpp
#include "../Scene/GameScene.h"
#include "ShockWave.h"

void C_ShockWave::Init(C_GameScene* a_pGameScene)
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.0f };
	m_radiusX = 32.0f;
	m_radiusY = 32.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_alpha = 0.4f;
	m_rect = { 0,0,96,96};
	m_isActive = false;

	m_pGameScene = a_pGameScene;
}

void C_ShockWave::Update(const Math::Vector2& a_centerPos)
{
	if(m_isActive)
	{
		//拡大処理
		ExpandShockWave();

		//フェード処理
		Fade();

		//行列計算
		UpdateMatrix();
	}
}

void C_ShockWave::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_ShockWave::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX,m_scaleY, 1.0f);
	m_mat = m_rotateMat * m_scaleMat * m_transMat;
}

void C_ShockWave::Activate(Math::Vector2 a_pos, float a_scaleX, float a_scaleY)
{
	m_pos = a_pos;						//座標確定
	m_scaleX = a_scaleX;				//初期拡大率確定
	m_scaleY = a_scaleY;				//初期拡大率確定
	m_isActive = true;					//表示状態へ移行

	//移動行列
	UpdateMatrix();
}

void C_ShockWave::Deactivate()
{
	m_isActive = false;
}

void C_ShockWave::ExpandShockWave()
{
	m_scaleX += SCALE_SPEED;
	m_scaleY += SCALE_SPEED;
}

void C_ShockWave::Fade()
{
	m_alpha += ALPHA_SPEED;
	if (m_alpha < 0.0f) ResetToDefault();
}

void C_ShockWave::ResetToDefault()
{
	m_pos = { 0.0f,0.0f };
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_alpha = 0.4f;
	m_isActive = false;
}
