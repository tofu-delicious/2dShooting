//Stage.h
#pragma once
#include "Manager/TextureManager.h"

//列挙型変数
enum class Stage
{
	Saturn,	//土星
	Earth,	//地球
	Sun,	//太陽
	Pluto,	//冥王星（エキストラステージ）
};

//背景オブジェクト用の構造体
struct SpaceObject
{
	Math::Vector2 pos;		//座標
	Math::Vector2 move;		//移動量
	Math::Matrix transMat;	//移動行列
	Math::Matrix scaleMat;	//拡縮行列
	Math::Matrix rotateMat;	//回転行列
	Math::Matrix mat;		//合成行列
	Math::Rectangle rect;	//画像範囲指定
	KdTexture* tex;			//画像用
	float radiusX;			//X軸方向の半径
	float radiusY;			//Y軸方向の半径
	float scaleX;			//X軸方向の拡縮
	float scaleY;			//Y軸方向の拡縮
	float rotate;			//傾き
	float alpha;			//不透明度
	float fadeStep;			//フェード用
	bool isActive;			//true 有効　false 無効
};

//前方宣言
class C_GameScene;

using namespace std;

class C_Stage
{
public:
	C_Stage(){}
	~C_Stage(){}

	void Init(C_GameScene *a_pGameScene,Stage a_stageNum);
	void Update();
	void Draw();

	//背景画像（宇宙）の定義
	void CreateSpace();

	//背景画像（星雲）の定義
	void CreateNebula();

	//背景画像（星）の定義
	void CreateStars();

	//背景画像（星）のフェード処理
	void FadeStars(SpaceObject& a_star);

	//行列情報
	void UpdateMatrix(SpaceObject& spaceObject);

	//引数の範囲のランダム値を生成する関数
	float Rnd(float a_min, float a_max);

	//引数の角度をラジアン値に変換する関数
	float CalcRadian(float a_deg);

private:

	//========= 外部参照 ==========
	C_GameScene* m_pGameScene = nullptr;		//GameSceneクラスのインスタンスを取得

	//======= 定数・設定値 ========
	static constexpr int STAR_NUM = 100;			//星の最大数
	static constexpr int NEBULA_NUM = 2;			//星雲の最大値
	static constexpr float MAX_ALPHA = 1.0f;		//最大透明度
	static constexpr float MIN_ALPHA = 0.0f;		//最小透明度
	static constexpr float MAX_FADESTEP = -0.01f;	//最大透明調整値
	static constexpr float MIN_FADESTEP = -0.02f;	//最小透明調整値
	static constexpr float MAX_SCALE = 5.0f;		//最大拡大率
	static constexpr float MIN_SCALE = 2.0f;		//最小拡大率
	static constexpr float MAX_ROTATE = 180.0f;		//最大角度
	static constexpr float MIN_ROTATE = 20.0f;		//最小角度

	//======== 状態フラグ =========

	//========= 動的変数 ==========
	SpaceObject m_space;							//背景（宇宙）
	vector<SpaceObject> m_Nebula;					//背景（星雲）
	vector<SpaceObject> m_Stars;					//星を管理するリスト
	

	//ステージ関連
	Stage m_stageNum;								//現在のステージ番号（Saturn ～ Pluto）

};