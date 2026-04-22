//ChargeBullet.cpp
#include "../Scene/GameScene.h"
#include "ChargeBullet.h"

void C_ChargeBullet::Init(C_GameScene *a_pGameScene)
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.0f };
	m_radiusX = 32.0f;
	m_radiusY = 32.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_alpha = 1.0f;
	m_rect = { 0,0,64,64 };
	m_isActive = false;

	m_pGameScene = a_pGameScene;

	m_chargeTime = 0.0f;
	m_scaledRadius = 0.0f;
}

void C_ChargeBullet::Update()
{
	//プレイヤーインスタンス情報取得
	C_Player* player = m_pGameScene->GetPlayer();

	//チャージ攻撃が移動していない場合
	if (m_move.y == 0.0f)
	{
		//静電気エフェクトの描画処理
		EFFECTMANAGER.CreateStaticElec(m_pos, m_scaledRadius, m_scaledRadius);

		//光の粒子エフェクトの描画処理
		EFFECTMANAGER.CreateAbsorption(m_pos, m_scaledRadius, m_scaledRadius);

		//チャージする処理
		if (player->IsPressed())
		{
			if(!SOUNDMANAGER.IsPlay("Charge"))SOUNDMANAGER.Play("Charge");

			UpdateChargeTime();
		}

		//チャージ中の角度増分は10.0f
		RotateLoop(HIGH_INCREASE_ANGLE);

		//チャージ攻撃の発射処理
		if (player->IsRelease())
		{
			//チャージ攻撃の発射音
			SOUNDMANAGER.Play("Shot",false);

			//衝撃波エフェクトの描画処理
			EFFECTMANAGER.CreateShockWave(m_pos, m_scaleX, m_scaleY);

			m_move.y = MOVE_SPEED_Y;
		}
	}
	//チャージ攻撃が移動している場合
	else
	{
		//チャージ攻撃をためる音を停止
		SOUNDMANAGER.Stop("Charge");

		//座標確定処理
		m_pos += m_move;

		//移動中の回転増分は1.5f
		RotateLoop(LOW_INCREASE_ANGLE);

		//画面外処理
		if (IsOutOfBounds())
		{
			ResetToDefault();
		}
	}

	//行列計算
	UpdateMatrix();
}

void C_ChargeBullet::Draw()
{
	if(m_isActive && m_tex != nullptr)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect,m_alpha);
	}
}

void C_ChargeBullet::Activate(Math::Vector2 a_pos)
{
	m_pos = { a_pos.x,a_pos.y + OFFSET_Y };
	m_isActive = true;
}

void C_ChargeBullet::bImGui()
{
	ImGui::Text("chargeTime:%.1f", m_chargeTime);
}

void C_ChargeBullet::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x,m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_rotateMat = Math::Matrix::CreateRotationZ(CalcRadian(m_rotate));
	m_mat = m_rotateMat * m_scaleMat * m_transMat;
}

void C_ChargeBullet::UpdateChargeTime()
{
	Math::Vector2 playerPos = m_pGameScene->GetPlayer()->GetPos();

	//プレイヤー座標に補正
	m_pos = { playerPos.x,playerPos.y + OFFSET_Y };

	//最大サイズになればカウント停止
	if (m_scaleX < MAX_CHARGE_SCALE || m_scaleY < MAX_CHARGE_SCALE)
	{
		//チャージ時間を加算
		m_chargeTime += CHARGE_INCREMENT;

		//拡大率制御
		m_scaleX += CHARGE_SPEED;
		m_scaleY += CHARGE_SPEED;
	}

	m_scaledRadius = m_radiusX * m_scaleX;	//Y軸方向のデータが考慮されていないが、X・Yともに共通した値なため、このようなプログラムにしている
}

bool C_ChargeBullet::IsOutOfBounds()
{
	return m_pos.y > SCREENTOP + m_scaledRadius;
}

void C_ChargeBullet::ResetToDefault()
{
	m_move.y = 0.0f;
	m_radiusX = 32.0f;
	m_radiusY = 32.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_isActive = false;
	m_chargeTime = 0.0f;
	m_scaledRadius = 0.0f;
}

void C_ChargeBullet::RotateLoop(const float& INCREASE_ANGLE)
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