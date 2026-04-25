//EffectBase.h
#pragma once

//ラベル（エフェクトの分類）：EffectManagerクラスで使用する
enum class EffectType
{
	StaticElec,
	Shock,
	Absorption,
	Exp
};

//前方宣言
class C_GameScene;

class C_EffectBase
{
public:
	C_EffectBase(){}
	~C_EffectBase(){}

	virtual void Init(C_GameScene* a_pGameScene) = 0;
	virtual void Update(const Math::Vector2& a_centerPos = { 0,0 }) = 0;
	virtual void Draw() = 0;

	//引数の角度からラジアン値を算出する
	float CalcRadian(float a_deg);

	//乱数
	float Rnd(float a_min, float a_max);

	//=========== ゲッター =========
	//変数「m_isActive」の真偽値を取得する
	virtual bool IsActive() = 0;
	//各エフェクトのラベルを取得する
	virtual EffectType GetType() = 0;

private:

protected:

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
	float m_orbitRadius;		//円軌道上の半径
	float m_scaleX;				//X軸方向の拡縮
	float m_scaleY;				//Y軸方向の拡縮
	float m_rotate;				//回転角度
	float m_alpha;				//不透明度
	float m_fadeStep;			//フェード用
	float m_AnimationCnt;		//アニメーションの描画範囲
	float m_maxAnimationCnt;	//アニメーションの最大描画範囲
	bool m_isActive;			//true 表示　false 非表示
};