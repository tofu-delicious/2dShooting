//NormalEnemy.cpp
#include "../Scene/GameScene.h"
#include"../Manager/EffectManager.h"
#include "../Manager/BulletManager.h"
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

void C_NormalEnemy::Action(const Math::Vector2 &a_playerPos)
{
	m_move = { 0,0 };

	//敵の行動
	ChangeAction(a_playerPos);
	//弾の発射間隔
	UpdateCoolTime();
	//敵の攻撃
	AttackEnemy();
	//敵撃破時の効果
	BenefitPlayer();
}

void C_NormalEnemy::Update()
{
	//座標確定処理
	CommitMove();
	//行列処理
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

void C_NormalEnemy::cImGui()
{
	ImGui::Text("enemy : posX:%.1f posY:%.1f", m_pos.x, m_pos.y);
}

void C_NormalEnemy::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_mat = m_scaleMat * m_transMat;
}

void C_NormalEnemy::Activate()
{
	//m_pos = { Rnd(-600,600),Rnd(100,200) };
	m_pos = { -600,200 };
	m_move = { 0.0f,0.0f };

	m_isActive = true;		//表示状態へ移行
}

void C_NormalEnemy::ChangeAction(const Math::Vector2 &a_playerPos)
{
	//自身とプレイヤーとの距離を測る
	float distance = CalcDistance(a_playerPos, m_pos);

	//距離が100より大きく300以下だった場合は「停止」
	if (distance <= 300) { MoveStop(); }
	//距離が300より大きい場合は「平行移動
	else{ MoveTrans(); }
}

void C_NormalEnemy::MoveTrans()
{
	m_rotate += 1.0f;
	if (m_rotate >= 360.0f) m_rotate -= 360.0f;
	float radian = CalcRadian(m_rotate);
	m_move.x = sinf(radian);
}

void C_NormalEnemy::MoveStop()
{
	m_move = { 0,0 };
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
	EFFECTMANAGER.EmitExplosion(m_pos);
}
