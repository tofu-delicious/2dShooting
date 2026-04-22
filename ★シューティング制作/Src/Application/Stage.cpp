//Stage.cpp
#include "Stage.h"

void C_Stage::Init(C_GameScene* a_pGameScene, Stage a_stageNum)
{
	m_stageNum = a_stageNum;	//ステージ情報を取得

	switch (m_stageNum) {
	case Stage::Saturn:
		break;
	case Stage::Earth:
		break;
	case Stage::Sun:
		break;
	case Stage::Pluto:
		break;
	default:
		break;
	}

	CreateSpace();				//宇宙

	CreateNebula();				//星雲

	CreateStars();				//星

	m_pGameScene = a_pGameScene;
}

void C_Stage::Update()
{
	//宇宙
	UpdateMatrix(m_space);

	//星雲
	for (auto& nebula : m_Nebula)
	{

		//行列
		UpdateMatrix(nebula);
	}

	//星
	for (auto& star : m_Stars)
	{
		//フェード処理
		FadeStars(star);

		//行列
		UpdateMatrix(star);		
	}
}

void C_Stage::Draw()
{
	//宇宙
	SHADER.m_spriteShader.SetMatrix(m_space.mat);
	SHADER.m_spriteShader.DrawTex(m_space.tex, m_space.rect, m_space.alpha);

	//星雲
	for (auto& nebula : m_Nebula)
	{
		if (nebula.isActive)
		{
			SHADER.m_spriteShader.SetMatrix(nebula.mat);
			SHADER.m_spriteShader.DrawTex(nebula.tex, nebula.rect, nebula.alpha);
		}
	}

	//星
	for (auto& star : m_Stars)
	{
		if(star.isActive)
		{
			SHADER.m_spriteShader.SetMatrix(star.mat);
			SHADER.m_spriteShader.DrawTex(star.tex, star.rect, star.alpha);
		}
	}
}

void C_Stage::CreateSpace()
{
	m_space.pos = { 0.0f,0.0f };
	m_space.move = { 0.0f,0.0f };
	m_space.rect = { 0,0,1280,720 };
	m_space.tex = TEXTUREMANAGER.GetTex("Space");
	m_space.scaleX = 1.0f;
	m_space.scaleY = 1.0f;
	m_space.radiusX = 640.0f;
	m_space.radiusY = 360.0f;
	m_space.rotate = 0.0f;
	m_space.alpha = 1.0f;
	m_space.fadeStep = 0.0f;
	m_space.isActive = true;
}

void C_Stage::CreateNebula()
{
	for(int n = 0;n < NEBULA_NUM;n++)
	{
		float randScaleX = Rnd(MIN_SCALE, MAX_SCALE);
		float randScaleY = Rnd(MIN_SCALE, MAX_SCALE);

		SpaceObject newNebula;
		newNebula.pos = { Rnd(-600.0f,600.0f),Rnd(-300.0f,300.0f) };
		newNebula.move = { 0.0f,0.0f };
		newNebula.rect = { 0,0,128,92 };
		newNebula.tex = TEXTUREMANAGER.GetTex("Nebula");
		newNebula.scaleX = randScaleX;
		newNebula.scaleY = randScaleY;
		newNebula.radiusX = 64.0f * newNebula.scaleX;
		newNebula.radiusY = 46.0f * newNebula.scaleY;
		newNebula.rotate = Rnd(MIN_ROTATE, MAX_ROTATE);
		newNebula.alpha = 1.0f;
		newNebula.fadeStep = 0.0f;
		newNebula.isActive = false;

		m_Nebula.push_back(newNebula);
	}
}

void C_Stage::CreateStars()
{
	for (int s = 0; s < STAR_NUM; s++)
	{
		float randScale = Rnd(0.1f, 0.5f);

		SpaceObject newStar;
		newStar.pos = { Rnd(-640.0f,640.0f),Rnd(-360.0f,360.0f) };
		newStar.move = { 0.0f,0.0f };
		newStar.rect = { 0,0,32,32 };
		newStar.tex = TEXTUREMANAGER.GetTex("Star");
		newStar.scaleX = 0.1f;
		newStar.scaleY = 0.1f;
		newStar.radiusX = 16.0f * newStar.scaleX;
		newStar.radiusY = 16.0f * newStar.scaleY;
		newStar.alpha = 1.0f;
		newStar.fadeStep = Rnd(MIN_FADESTEP, MAX_FADESTEP);
		newStar.isActive = true;

		m_Stars.push_back(newStar);
	}
}

void C_Stage::FadeStars(SpaceObject& a_star)
{
	a_star.alpha += a_star.fadeStep;

	if (a_star.alpha > MAX_ALPHA)
	{
		a_star.alpha = MAX_ALPHA;
		a_star.fadeStep *= -1.0f;
	}
	
	if (a_star.alpha < MIN_ALPHA)
	{
		a_star.alpha = MIN_ALPHA;
		a_star.fadeStep *= -1.0f;
	}
}

void C_Stage::UpdateMatrix(SpaceObject &spaceObject)
{
	spaceObject.transMat = Math::Matrix::CreateTranslation(spaceObject.pos.x, spaceObject.pos.y, 0.0f);
	spaceObject.scaleMat = Math::Matrix::CreateScale(spaceObject.scaleX, spaceObject.scaleY, 1.0f);
	spaceObject.rotateMat = Math::Matrix::CreateRotationZ(CalcRadian(spaceObject.rotate));
	spaceObject.mat = spaceObject.rotateMat * spaceObject.scaleMat * spaceObject.transMat;
}

float C_Stage::Rnd(float a_min, float a_max)
{
	float range = a_max - a_min;
	float ratio = (float)rand() / RAND_MAX;

	//乱数を求める
	return a_min + (ratio * range);
}

float C_Stage::CalcRadian(float a_deg)
{
	return DirectX::XMConvertToRadians(a_deg);
}

