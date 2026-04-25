//Player.h
#pragma once

//前方宣言
class C_GameScene;

class C_Player
{
public:
	C_Player() {}
	~C_Player() {}

	void Init(C_GameScene* a_GameScene);	//初期化処理
	void Action();							//行動処理
	void Update();							//確定処理
	void LateAction();						//ChargeBulletクラスの変数値をリアルタイムで受け取りながら実行する処理
	void Draw();							//描画処理

	//行列処理
	void UpdateMatrix();

	//プレイヤーの移動量
	void UpdateMovement();

	//チャージ攻撃のための入力状態を更新する
	void UpdateChargeInput();

	//チャージ攻撃をした瞬間の反動
	void ApplyRecoil();

	//画面外に出ているかどうかを判定する（true：画面外に出ている　false：画面内）
	void KeepInsideScreen();

	//衝突判定後の処理
	const void OnHit() { m_isActive = false; }

	//NormalBulletを撃てるかどうか
	bool CanShootNormal();

	//ChargeBulletを撃てるかどうか
	bool CanShootCharge();

	//通常弾の生成タイミングを均等にする
	//クールタイムの設定
	void StartCoolTime(float a_seconds);

	//クールタイム更新処理
	void UpdateCoolTime();

	//弾を撃つタイミングを判定する処理
	bool IsReady();

	//ラジアン値を算出する
	float CalcRadian(float a_deg) { return DirectX::XMConvertToRadians(a_deg); }

	//========= ゲッター ==========
	//プレイヤーの座標情報を取得
	Math::Vector2 GetPos()const { return m_pos; }
	//プレイヤーの移動量を取得
	Math::Vector2 GetMove()const { return m_move; }
	//プレイヤーのX,Y軸の半径のうち、大きい値を取得
	float GetRadius()const { return m_radiusX > m_radiusY ? m_radiusX : m_radiusY; }
	//プレイヤーのX軸の半径を取得
	float GetRadiusX()const { return m_radiusX; }
	//プレイヤーのY軸の半径を取得
	float GetRadiusY()const { return m_radiusY; }
	//変数「m_isTrigger」の真偽値を取得
	bool IsTrigger() const { return m_isTrigger; }
	//変数「m_isPressed」の真偽値を取得
	bool IsPressed() const { return m_isPressed; }
	//変数「m_isRelease」の真偽値を取得
	bool IsRelease() const { return m_isRelease; }
	//変数「m_isActive」の真偽値を取得
	bool IsActive()const { return m_isActive; }

	//========= セッター ==========

	//========= デバッグ ==========
	void ImGui();

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;

	//======= 定数・設定値 ========
	static constexpr float NORMAL_SPEED = 5.0f;					//通常の移動量
	static constexpr float SLOW_SPEED = 3.0f;					//チャージ中の移動量
	static constexpr float RECOIL_POWER = 4.0f;					//反動中の移動量
	static constexpr float RECOIL_DURATION = 0.2f;				//反動の総時間
	static constexpr float FPS = 60.0f;							//秒をフレーム単位に変換する際に乗算する値
	static constexpr float COOLTIME = 0.3f;						//カウントタイムの最大値
	const float m_recoilSwitchTime = RECOIL_DURATION * 0.5f;	//反動の動作の切り替わり時間

	//======== 状態フラグ =========
	bool m_isTrigger;	//押した瞬間だけON
	bool m_isPressed;	//押しっぱなし状態に移行
	bool m_isRelease;	//離した瞬間だけON
	bool m_isRecoiling;	//true：反動中　false：反動していない（通常）

	//========= 動的変数 ==========
	float m_recoilTimer = 0.0f;		//プレイヤーが弾を撃った際の反動（下に行ってから上に戻る）時間を計測する
	float m_finalSpeed = 0.0f;		//弾をチャージしているか否かで移動速度を調整する
	float m_deltaTime = 0.016f;		//反動による上下移動の時間を減らす
	float m_coolTimeCount = 0.0f;;	//弾の発射間隔のカウントダウン用

	Math::Vector2 m_pos;		//座標
	Math::Vector2 m_move;		//移動量
	Math::Matrix m_transMat;	//移動行列
	Math::Matrix m_scaleMat;	//拡縮行列
	Math::Matrix m_rotateMat;	//回転行列
	Math::Matrix m_mat;			//合成行列
	Math::Rectangle m_rect;		//画像範囲指定
	KdTexture* m_tex;			//画像用
	float m_radiusX;			//X軸方向の半径
	float m_radiusY;			//Y軸方向の半径
	float m_scaleX;				//X軸方向の拡縮
	float m_scaleY;				//Y軸方向の拡縮
	float m_rotate;				//回転角度
	float m_alpha;				//不透明度
	float m_fadeStep;			//フェード用
	bool m_isActive;			//true 表示　false 非表示

	
};

