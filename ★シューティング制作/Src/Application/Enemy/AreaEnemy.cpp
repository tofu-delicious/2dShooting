#include "AreaEnemy.h"

//===============================================
// 初期化処理
//===============================================
void C_AreaEnemy::Init(C_GameScene* a_pGameScene)
{
	InitEnemy();
	m_pGameScene = a_pGameScene;
}

void C_AreaEnemy::InitEnemy()
{
	enemy.pos = { 0,0 };						//座標
	enemy.move = { 0,0 };						//移動量
	enemy.rect = { 0,0,64,64 };					//画像範囲指定
	enemy.radiusX = 32.0f;						//X軸方向の半径
	enemy.radiusY = 32.0f;						//Y軸方向の半径
	enemy.scaleX = 1.0f;						//X軸方向の拡縮
	enemy.scaleY = 1.0f;						//Y軸方向の拡縮
	enemy.rotate = 0.0f;						//回転角度
	enemy.alpha = 1.0f;							//不透明度
	enemy.fadeStep = -0.01f;					//フェード用
	enemy.isActive = true;						//true 表示　false 非表示
}

void C_AreaEnemy::InitArea()
{
	area.pos = { enemy.pos.x,enemy.pos.y };		//座標
	area.move = { 0,0 };						//移動量
	area.rect = { 0,0,64,64 };					//画像範囲指定
	area.radiusX = 8.0f;						//X軸方向の半径
	area.radiusY = 8.0f;						//Y軸方向の半径
	area.scaleX = INITIAL_SCALE;				//X軸方向の拡縮
	area.scaleY = INITIAL_SCALE;				//Y軸方向の拡縮
	area.rotate = 0.0f;							//回転角度
	area.alpha = 0.4f;							//不透明度
	area.isActive = true;						//true 表示　false 非表示
}

void C_AreaEnemy::Action(const Math::Vector2& a_playerPos)
{
	////敵の生存処理
	//if (enemy.isActive)
	//{
	//	//行動パターンの切替処理
	//	ChangeAction(a_playerPos);
	//}
	////敵の死亡処理（エリアを強制的に縮小 & 
	//else
	//{
	//	//モードをDeployに変更
	//	m_ActionMode = ActionMode::Shrink;

	//	//縮小モード
	//	m_isExpanding = false;

	//	//動きを止める
	//	enemy.move = { 0,0 };
	//}
	
	//行動パターンの切替処理
	ChangeAction(a_playerPos);
	//攻撃処理
	AttackEnemy();
	//撃破時の効果処理
	BenefitPlayer();
}

void C_AreaEnemy::Update()
{
	//座標確定処理
	CommitMove();
	//敵の行列
	UpdateMatEnemy();
	//エリアの行列
	UpdateMatArea();
}

void C_AreaEnemy::Draw()
{
	if(enemy.isActive)
	{
		SHADER.m_spriteShader.SetMatrix(enemy.mat);
		SHADER.m_spriteShader.DrawTex(enemy.tex, enemy.rect, enemy.alpha);
	}

	if (area.isActive)
	{
		SHADER.m_spriteShader.SetMatrix(area.mat);
		SHADER.m_spriteShader.DrawTex(area.tex, area.rect, area.alpha);
	}
}

void C_AreaEnemy::Activate()
{
	//初期化処理
	enemy.pos = { 200,200 };
	enemy.move = { 0,0 };

	//表示処理
	enemy.isActive = true;
}

//=============================================================
// 敵系
//=============================================================
void C_AreaEnemy::ChangeAction(const Math::Vector2& a_playerPos)
{
	//目標座標への移動量を決める
	if (m_ActionMode == ActionMode::Calculate)
	{
		//目標座標を決める
		DetermineTargetPos(a_playerPos);

		//移動量を求める
		CalculateVelocity();

		//移動モードへ変更
		m_ActionMode = ActionMode::Move;
	}
	//移動する
	else if (m_ActionMode == ActionMode::Move)
	{
		if (IsArrived())
		{
			//エリアの初期化
			InitArea();

			m_ActionMode = ActionMode::Deploy;
		}
		else
		{
			enemy.move.x = m_vectorX;
			enemy.move.y = m_vectorY;
		}
	}
	else if (m_ActionMode == ActionMode::Deploy)
	{
		//動きを止める
		enemy.move = { 0.0f,0.0f };

		//エリアを表示・拡大
		m_isExpanding = true;		//増加モードに変更
	}
	else if (m_ActionMode == ActionMode::Shrink)
	{
		m_isExpanding = false;
	}
}

void C_AreaEnemy::AttackEnemy()
{
	//AreaEnemyの攻撃手段は「体力を減らすエリア展開」
	if (m_isExpanding)
	{
		//徐々にエリアを拡大
		ExpandArea();
	}
	else
	{
		//徐々にエリアを縮小
		ShrinkArea();
	}
}

void C_AreaEnemy::BenefitPlayer()
{
}

void C_AreaEnemy::DetermineTargetPos(const Math::Vector2& a_targetPos)
{
	m_targetPos = a_targetPos;
}

void C_AreaEnemy::CalculateVelocity()
{
	float dx = m_targetPos.x - enemy.pos.x;
	float dy = m_targetPos.y - enemy.pos.y;

	//プレイヤーがいる方向のラジアンを求める
	float angle = atan2(dy, dx);

	//速度を掛けて移動量を計算
	m_vectorX = cosf(angle) * MOVE_SPEED;
	m_vectorY = sinf(angle) * MOVE_SPEED;
}

bool C_AreaEnemy::IsArrived()
{
	//return enemy.pos == m_targetPos;
	return (enemy.pos.x >= m_targetPos.x - 10 && enemy.pos.x <= m_targetPos.x) &&
		(enemy.pos.y >= m_targetPos.y - 10 && enemy.pos.y <= m_targetPos.y);
}

void C_AreaEnemy::OnHit()
{
	enemy.isActive = false;
	//エリア縮小モードへ移行
	m_ActionMode = ActionMode::Shrink;
}

void C_AreaEnemy::UpdateMatEnemy()
{
	enemy.transMat = Math::Matrix::CreateTranslation(enemy.pos.x, enemy.pos.y, 0.0f);
	enemy.scaleMat = Math::Matrix::CreateScale(enemy.scaleX, enemy.scaleY, 1.0f);
	enemy.mat = enemy.scaleMat * enemy.transMat;
}

//==============================================================
// エリア系
//==============================================================
void C_AreaEnemy::ExpandArea()
{
	area.scaleX += SCALE_SPEED;
	area.scaleY += SCALE_SPEED;

	if (area.scaleX > MAX_SCALE || area.scaleY > MAX_SCALE)
	{
		area.scaleX = MAX_SCALE;
		area.scaleY = MAX_SCALE;
	}
}

void C_AreaEnemy::ShrinkArea()
{
	//エリアのサイズを縮小
	area.scaleX -= SCALE_SPEED;
	area.scaleY -= SCALE_SPEED;

	//Init関数でINITIAL_SCALEの値として初期化しているため、縮小アニメーションが実行されない
	if (area.scaleX < 0.0f || area.scaleY < 0.0f)
	{
		area.isActive = false;
	}
}

void C_AreaEnemy::UpdateMatArea()
{
	area.transMat = Math::Matrix::CreateTranslation(area.pos.x, area.pos.y, 0.0f);
	area.scaleMat = Math::Matrix::CreateScale(area.scaleX, area.scaleY, 1.0f);
	area.mat = area.scaleMat * area.transMat;
}
