//Player.cpp
#include "Scene/GameScene.h"
#include "Manager/BulletManager.h"
#include "Player.h"

void C_Player::Init(C_GameScene* a_GameScene)
{
	m_pGameScene = a_GameScene;
	
	m_pos = { 0,0 };
	m_move = { 0,0 };
	m_tex = TEXTUREMANAGER.GetTex("Player");
	m_rect = { 0,0,64,64 };
	m_radiusX = 32.0f;
	m_radiusY = 32.0f;
	m_scaleX = 1.0f;
	m_scaleY = 1.0f;
	m_rotate = 0.0f;
	m_alpha = 1.0f;
	m_fadeStep = -0.02f;
	m_isActive = true;

	m_isTrigger = false;
	m_isPressed = false;
	m_isRelease = false;

	m_isRecoiling = false;

	m_recoilTimer = RECOIL_DURATION;
}

void C_Player::Action()
{
	//チャージ攻撃の入力準備（チャージ攻撃中は入力準備をできないようにする）
	UpdateChargeInput();

	//通常弾
	if (CanShootNormal())
	{
		BULLETMANAGER.CreateNormalBullet(m_pos);	//弾を撃つ
		StartCoolTime(COOLTIME);					//クールタイムを設定（一気に複数の弾を表示させないため）
	}

	//チャージ弾
	if (CanShootCharge()) BULLETMANAGER.CreateChargeBullet(m_pos);
}

void C_Player::Update()
{
	//移動確定処理
	m_pos += m_move;

	//カウントダウン
	UpdateCoolTime();

	//画面外処理
	KeepInsideScreen();

	//行列処理
	UpdateMatrix();
}

void C_Player::LateAction()
{
	//プレイヤーの移動量
	UpdateMovement();

	//チャージ攻撃時のヒットバック
	ApplyRecoil();
}

void C_Player::Draw()
{
	if(m_isActive)
	{
		SHADER.m_spriteShader.SetMatrix(m_mat);
		SHADER.m_spriteShader.DrawTex(m_tex, m_rect, m_alpha);
	}
}

void C_Player::UpdateMatrix()
{
	m_transMat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_scaleMat = Math::Matrix::CreateScale(m_scaleX, m_scaleY, 1.0f);
	m_rotateMat = Math::Matrix::CreateRotationZ(CalcRadian(m_rotate));
	m_mat = m_rotateMat * m_scaleMat * m_transMat;
}

void C_Player::UpdateMovement()
{
	m_move = { 0,0 };

	if (m_isRecoiling) return;	//反動中は移動ができない

	//移動量を算出する
	if (m_isPressed)		//チャージ攻撃をためて
	{
		m_finalSpeed = SLOW_SPEED;
	}
	else
	{
		m_finalSpeed = NORMAL_SPEED;
	}

	//右移動
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_move.x = m_finalSpeed;
	}
	//左移動
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_move.x = -m_finalSpeed;
	}
	//上移動
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_move.y = m_finalSpeed;
	}
	//下移動
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_move.y = -m_finalSpeed;
	}
}

void C_Player::UpdateChargeInput()
{
	if (BULLETMANAGER.GetChargeBullet() != nullptr)
	{
		Math::Vector2 chargeMove = BULLETMANAGER.GetChargeBullet()->GetMove();
		if (chargeMove.y != 0.0f)return;
	}

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_isPressed)
		{
			m_isTrigger = true;		//1フレームのみの実行を許可する
			m_isPressed = true;		//「押しっぱなし」であることを記録
			m_isRelease = false;	//離されていないためfalseにする
		}
		else
		{
			m_isTrigger = false;	//2フレーム以降は許可しない
			m_isRelease = false;
		}
	}
	else
	{
		if (m_isPressed)			//もしLボタンが離された直前まで押しっぱなしだった場合
		{
			m_isRelease = true;
			m_isRecoiling = true;	//反動処理を実行させる
		}
		else                        //もしLボタンが離しっぱなしである場合
		{
			m_isRelease = false;
		}

		m_isTrigger = false;
		m_isPressed = false;
	}
}

void C_Player::ApplyRecoil()
{
	if (m_isRecoiling)
	{
		//時間のカウント
		if (m_recoilTimer > 0.0f) m_recoilTimer -= m_deltaTime;

		//時間ごとのアクション
		if (m_recoilTimer > m_recoilSwitchTime)		//1.0f < m_recoilTimer ≦ 2.0f
		{
			m_move.y = -RECOIL_POWER;
		}
		else if (m_recoilTimer > 0.0f)				//0.0f < m_recoilTimer ≦ 1.0f
		{
			m_move.y = RECOIL_POWER;
		}
		else
		{
			m_move = { 0.0f,0.0f };
			m_recoilTimer = RECOIL_DURATION;		//カウント変数初期化
			m_isRecoiling = false;					//反動処理を終了させる
		}
	}
}

void C_Player::KeepInsideScreen()
{
	float rightLimit = SCREENRIGHT - (m_radiusX + SCREEN_PADDING);
	float leftLimit = SCREENLEFT + (m_radiusX + SCREEN_PADDING);
	float topLimit = SCREENTOP - (m_radiusY + SCREEN_PADDING);
	float downLimit = SCREENDOWN + (m_radiusY + SCREEN_PADDING);

	if (m_pos.x > rightLimit) m_pos.x = rightLimit;
	if (m_pos.x < leftLimit) m_pos.x = leftLimit;
	if (m_pos.y > topLimit) m_pos.y = topLimit;
	if (m_pos.y < downLimit) m_pos.y = downLimit;
}

bool C_Player::CanShootNormal()
{
	//チャージ攻撃をしていない & 通常弾のクールタイムが0になったらtrue、そうでなければfalseを返す。
	return m_isActive && BULLETMANAGER.GetChargeBullet() == nullptr && IsReady();
}

bool C_Player::CanShootCharge()
{
	//チャージ攻撃をしていない & プレイヤーが左クリックを実行した瞬間にtrue、そうでなければfalseを返す。
	return m_isActive && BULLETMANAGER.GetChargeBullet() == nullptr && m_isTrigger;
}

void C_Player::StartCoolTime(float a_seconds)
{
	m_coolTimeCount = a_seconds * FPS;
}

void C_Player::UpdateCoolTime()
{
	if (m_coolTimeCount > 0.0f) m_coolTimeCount -= 1.0f;
}

bool C_Player::IsReady()
{
	return m_coolTimeCount <= 0.0f;
}

void C_Player::ImGui()
{
	ImGui::Text("player : posX:%.1f posY:%.1f", m_pos.x, m_pos.y);
	ImGui::Text("player : moveX:%.1f moveY:%.1f", m_move.x, m_move.y);
	ImGui::Text("m_recoilTimer : %.1f", m_recoilTimer);
	if (m_isRecoiling)ImGui::Text("m_isRecoiling::True");
	else ImGui::Text("m_isRecoiling::False");
}


