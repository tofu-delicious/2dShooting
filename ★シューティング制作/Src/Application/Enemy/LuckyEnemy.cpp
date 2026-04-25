#include "LuckyEnemy.h"

void C_LuckyEnemy::Init(C_GameScene* a_pGameScene)
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
	m_isActive = true;						//true 表示　false 非表示

	m_pGameScene = a_pGameScene;
}

void C_LuckyEnemy::Action(const Math::Vector2 &a_playerPos)
{
	ChangeAction();

	AttackEnemy();

	BenefitPlayer();
}

void C_LuckyEnemy::Update()
{
	CommitMove();

	UpdateMatrix();
}

void C_LuckyEnemy::Draw()
{
	if (m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_LuckyEnemy::UpdateMatrix()
{
}

void C_LuckyEnemy::Activate()
{
}

void C_LuckyEnemy::ChangeAction(const Math::Vector2& a_playerPos)
{
}

void C_LuckyEnemy::AttackEnemy()
{
}

void C_LuckyEnemy::BenefitPlayer()
{
}

void C_LuckyEnemy::OnHit()
{
}
