//EnemyBase.h
#pragma once

//前方宣言
class C_GameScene;

class C_EnemyBase
{
public:
	C_EnemyBase(){}
	~C_EnemyBase(){}
	
	virtual void Init(C_GameScene *a_GameScene) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	//表示状態にする
	virtual void Activate() = 0;

	//衝突判定後の処理
	virtual void OnHit() = 0;

	//敵の移動処理
	virtual void MoveEnemy() = 0;

	//敵の攻撃処理
	virtual void AttackEnemy() = 0;

	//敵の効果処理（関数名の意味は「プレイヤーの利益を与える」）
	virtual void BenefitPlayer() = 0;

	//クールタイムの設定
	virtual void StartCoolTime(float a_seconds);

	//クールタイム更新処理
	virtual void UpdateCoolTime();

	//弾を撃つタイミングを判定する処理
	virtual bool IsReady();

	//========= ゲッター ==========
	//座標情報を取得する
	virtual Math::Vector2 GetPos()const{ return m_pos; }
	//X軸、Y軸のどちらか大きい値を取得する
	virtual float GetRadius()const { return (m_radiusX > m_radiusY) ? m_radiusX : m_radiusY; }
	//X軸方向の半径値を取得する
	virtual float GetRadiusX()const { return m_radiusX; }
	//Y軸方向の半径値を取得する
	virtual float GetRadiusY()const { return m_radiusY; }
	//表示状態かどうかを取得
	virtual bool IsActive()const { return m_isActive; }

	//========= セッター ==========
	const virtual void SetTex(KdTexture* a_tex) { m_tex = a_tex; }

	//========= デバッグ ==========
	virtual void cImGui() = 0;

	//引数の角度からラジアン値を算出する
	float CalcRadian(float a_deg);

	//指定した範囲の乱数を算出する
	float Rnd(float a_min, float a_max);

private:

protected:

	static constexpr float FPS = 60.0f;							//秒をフレーム単位に変換する際に乗算する値
	static constexpr float COOLTIME = 0.3f;						//カウントタイムの最大値

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