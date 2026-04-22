//NormalBullet.h
#pragma once
#include "BulletBase.h"

//前方宣言
class C_GameScene;

using namespace std;

class C_NormalBullet:public C_BulletBase
{
public:
	C_NormalBullet(){}
	~C_NormalBullet(){}

	void Init(C_GameScene* a_pGameScene) override;
	void Update()override;
	void Draw()override;

	//行列計算
	void UpdateMatrix();

	//弾が画面外に出ているかどうかを判定する（true：画面外に出ている　false：画面内）
	bool IsOutOfBounds();

	//弾を表示させる
	void Activate(Math::Vector2 a_pos);

	//引数の弾を非表示にする
	void Deactivate();

	//========= ゲッター ==========
	//変数「m_isActive」の値を取得
	bool IsActive()const override{ return m_isActive; }

	//========= セッター ==========
	void SetTex(KdTexture* a_tex) { m_tex = a_tex; }

	//========= デバッグ ==========
	void bImGui();

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;

	//======= 定数・設定値 ========
	static constexpr int OFFSET_Y = 20;

	//======== 状態フラグ =========

	//========= 動的変数 ==========

};