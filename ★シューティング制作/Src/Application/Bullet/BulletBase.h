//BulletBase.h
#pragma once

//前方宣言
class C_GameScene;

class C_BulletBase
{
public:
	C_BulletBase(){}
	virtual ~C_BulletBase(){}

	virtual void Init(C_GameScene* a_pGameScene) = 0;
	virtual void Update(const Math::Vector2& a_playerPos = {0,0}) = 0;
	virtual void Draw() = 0;

	//衝突判定後の処理
	virtual void OnHit() { m_isActive = false; }

	//引数の角度からラジアン値を算出する
	float CalcRadian(float a_deg);
	
	//========= ゲッター ==========
	virtual Math::Vector2 GetPos()const { return m_pos; }
	virtual Math::Vector2 GetMove()const { return m_move; }
	//radiusX、radiusYを比較し、値が大きいほうを戻り値とする
	virtual float GetRadius()const { return (m_radiusX > m_radiusY) ? m_radiusX : m_radiusY; }
	virtual float GetRadiusX()const { return m_radiusX; }
	virtual float GetRadiusY()const { return m_radiusY; }

	//scaleX、scaleYを比較し、値が大きいほうを戻り値とする
	virtual float GetScale()const { return (m_scaleX > m_scaleY) ? m_scaleX : m_scaleY; }
	virtual float GetScaleX()const { return m_scaleX; }
	virtual float GetScaleY()const { return m_scaleY; }
	virtual bool IsActive()const = 0;

	//========= セッター ==========

	//========= デバッグ ==========

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
	float m_scaleX;				//X軸方向の拡縮
	float m_scaleY;				//Y軸方向の拡縮
	float m_rotate;				//回転角度
	float m_alpha;				//不透明度
	float m_fadeStep;			//フェード用
	bool m_isActive;			//true 有効　false 無効

};