//NormalBullet.cpp
#include "../Scene/GameScene.h"
#include "NormalBullet.h"

void C_NormalBullet::Init(C_GameScene *a_pGameScene)
{
	m_pGameScene = a_pGameScene;
;
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,10.0f };
	m_radiusX = 16.0f;
	m_radiusY = 16.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_alpha = 1.0f;
	m_rect = { 0,0,32,32 };
	m_isActive = false;
}

void C_NormalBullet::Update()
{
	if (m_isActive)
	{
		//座標確定処理
		m_pos += m_move;

		//画面外処理
		if (IsOutOfBounds()) Deactivate();

		//行列計算
		UpdateMatrix();
	}
}

void C_NormalBullet::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex,m_rect,m_alpha);
	}
}

void C_NormalBullet::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_mat = m_scaleMat * m_transMat;
}

bool C_NormalBullet::IsOutOfBounds()
{
	bool isOutRight = m_pos.x > SCREENRIGHT + m_radiusX;
	bool isOutLeft = m_pos.x < SCREENLEFT - m_radiusX;
	bool isOutTop = m_pos.y > SCREENTOP + m_radiusY;
	bool isOutDown = m_pos.y < SCREENDOWN - m_radiusY;

	return isOutRight || isOutLeft || isOutTop || isOutDown;
}

void C_NormalBullet::Activate(Math::Vector2 a_pos)
{
	m_pos = { a_pos.x,a_pos.y + OFFSET_Y};	//座標初期化
	m_isActive = true;	//弾を表示
}

void C_NormalBullet::Deactivate()
{
	m_isActive = false;
}

void C_NormalBullet::bImGui()
{
	/*if (NormalBullet.m_display) ImGui::Text("m_display:true");
	else ImGui::Text("m_display:false");*/
}
