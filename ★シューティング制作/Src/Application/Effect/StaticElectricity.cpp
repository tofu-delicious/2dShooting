//effect.cpp
#include "../Scene/GameScene.h"
#include "StaticElectricity.h"

void C_StaticElectricity::Init(C_GameScene* a_pGameScene)
{
	srand(timeGetTime());

	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.0f };
	m_radiusX = 32.0f;
	m_radiusY = 32.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_alpha = 1.0f;
	m_rect = { 0,0,0,0 };
	m_AnimationCnt = 0.0f;
	m_maxAnimationCnt = Rnd(5.0f, 8.0f);
	m_orbitRadius = 0.0f;
	m_isActive = false;

	m_pGameScene = a_pGameScene;
}

void C_StaticElectricity::Update()
{
	//ChargeBulletの情報を取得
	m_pChargeBullet = BULLETMANAGER.GetChargeBullet();

	if(m_pChargeBullet != nullptr)
	{
		m_bulletPos = m_pChargeBullet->GetPos();				//座標を取得
		m_bulletMove = m_pChargeBullet->GetMove();				//移動量を取得
		m_isBulletActive = m_pChargeBullet->IsActive();			//変数「m_isActive」の真偽値を取得
		m_bulletScale = m_pChargeBullet->GetScale();
	}

	bool isCharging = (m_isBulletActive && m_bulletMove.y == 0.0f);	//チャージ攻撃が表示状態かつ、発射していなければtrueを返す

	//静電気の非表示処理（ChargeBulletがチャージ中でない場合は非表示にする）
	if (!isCharging) Deactivate();
	
	//拡大率の変更
	ElecScaledChange(m_bulletScale);

	//描画範囲の変更
	CalcDrawRange();

	//エフェクトの動き
	MoveElec();
	
	//行列計算
	UpdateMatrix();
}

void C_StaticElectricity::Draw()
{
	if (!m_isActive) return;

	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
}

void C_StaticElectricity::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX,m_scaleY, 1.0f);
	m_rotateMat = Math::Matrix::CreateRotationZ(CalcRadian(m_rotate));
	m_mat = m_rotateMat * m_scaleMat * m_transMat;	
}

void C_StaticElectricity::Activate(Math::Vector2 a_pos, float a_radiusX, float a_radiusY)
{
	m_isActive = true;

	//AnimationCntの初期値を乱数指定
	CalcAnimationCnt();

	//描画方向の変更
	CalcDrawAngle();

	//透明度の変更
	CalcDrawAlpha();

	//描画位置の決定
	CalcDrawPos(a_pos, a_radiusX, a_radiusY);

	//移動行列
	UpdateMatrix();
}

void C_StaticElectricity::Deactivate()
{
	m_isActive = false;

	m_move = { 0.0f,0.0f };
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_AnimationCnt = 0.0f;
}

void C_StaticElectricity::ElecScaledChange(float a_scale)
{
	m_scaleX = a_scale - 0.5f;
	m_scaleY = a_scale - 0.5f;
}

void C_StaticElectricity::CalcDrawPos(Math::Vector2 a_centerPos, float a_radiusX, float a_radiusY)
{
	float highDeg = 360.0f;	//最大角度
	float lowDeg = 0.0f;	//最低角度

	//0～360度のランダムな角度を決める
	float randomDeg = Rnd(lowDeg, highDeg);
	float radian = CalcRadian(randomDeg);	//ラジアンに変換

	//変数「a_radiusX」以下の半径値をランダムに取得する
	m_orbitRadius = Rnd(a_radiusX,a_radiusX + ELEC_RADIUS_MARGIN);

	//座標確定処理
	m_pos.x = a_centerPos.x + cosf(radian) * m_orbitRadius;
	m_pos.y = a_centerPos.y + sinf(radian) * m_orbitRadius;
}

void C_StaticElectricity::CalcDrawRange()
{
	m_AnimationCnt += ANIM_SPEED;
	
	if(m_AnimationCnt > m_maxAnimationCnt)
	{
		Deactivate();	//非表示状態へ移行
	}

	//描画範囲の算出
	m_rect = { (int)m_AnimationCnt * 64,0,64,64 };
}

void C_StaticElectricity::CalcAnimationCnt()
{
	float highCnt = 10.0f;
	float lowCnt = 0.0f;

	m_AnimationCnt = Rnd(lowCnt, highCnt);
}

void C_StaticElectricity::CalcDrawAngle()
{
	float highDeg = 360.0f;
	float lowDeg = 0.0f;

	m_rotate = Rnd(lowDeg, highDeg);
}

void C_StaticElectricity::CalcDrawAlpha()
{
	float highAlpha = 1.0f;
	float lowAlpha = 0.2f;
	m_alpha = Rnd(lowAlpha,highAlpha);
}

void C_StaticElectricity::MoveElec()
{
	//更新処理
	m_rotate += Rnd(MIN_ELEC_ROTATE, MAX_ELEC_ROTATE);	//回転速度
	float radian = CalcRadian(m_rotate);				//ラジアン値が大きくなるほど回転速度は上がるみたい

	m_orbitRadius -= ELEC_ABSORPTION_SPEED;				//半径を減らす（徐々に中央に近づいていく感じになる！）
	if (m_orbitRadius < 0.0f)
	{
		m_orbitRadius = 0.0f;
	}

	//移動量を算出する
	m_pos.x = m_bulletPos.x + cosf(radian) * m_orbitRadius;
	m_pos.y = m_bulletPos.y + sinf(radian) * m_orbitRadius;
}
