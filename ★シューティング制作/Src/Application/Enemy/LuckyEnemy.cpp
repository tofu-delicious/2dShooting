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
	m_isArrived = false;					//true 到着　false まだ到着していない
	m_isActive = true;						//true 表示　false 非表示

	m_pGameScene = a_pGameScene;
}

void C_LuckyEnemy::Action(const Math::Vector2 &a_playerPos)
{
	//行動パターンの切り替え処理
	ChangeAction();
	//攻撃処理
	AttackEnemy();
	//敵撃破時の効果処理
	BenefitPlayer();
}

void C_LuckyEnemy::Update()
{
	//停止時間カウント処理（停止座標に着いたらカウント開始）
	if(m_isArrived)UpdateStopTime();
	//座標確定処理
	CommitMove();
	//行列処理
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
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0.0f);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_mat = m_scaleMat * m_transMat;
}

void C_LuckyEnemy::Activate()
{
	//m_pos = { -300,200 };

	m_pos = { 650,200 };
	m_move = { -5.0f,0.0f };
	m_isArrived = false;
	m_isActive = true;

	m_stopPosX = Rnd(MIN_STOP_POSX, MAX_STOP_POSX);	//停止位置を決める
	SetStopTime(Rnd(MIN_STOP_TIME, MAX_STOP_TIME));	//停止時間を決める
}

void C_LuckyEnemy::ChangeAction(const Math::Vector2& a_playerPos)
{
	//もし設定した停止位置と等しくなったら「m_isArrived」をtrue
	if (m_pos.x <= m_stopPosX)m_isArrived = true;

	//もし停止時間が終わったら「m_isArrived」をfalse
	if (IsMovable()) m_isArrived = false;

	//停止座標に到着していない or 停止時間が終了したら水平移動
	if (IsMovable() || !m_isArrived) MoveTrans();
	//もしそうでなければ
	else MoveStop();
}

void C_LuckyEnemy::BenefitPlayer()
{
}

void C_LuckyEnemy::OnHit()
{
}
