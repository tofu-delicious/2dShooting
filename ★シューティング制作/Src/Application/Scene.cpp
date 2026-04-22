#include "main.h"
#include "Scene.h"
#include "Manager/SceneManager.h"
#include "string.h"

void Scene::Draw2D()
{
	SCENEMANAGER.Draw();
}

void Scene::Update()
{
	SCENEMANAGER.Update();

	if (GetAsyncKeyState('Z') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_TitleScene());
	}
	else if (GetAsyncKeyState('X') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_SettingScene());
	}
	else if (GetAsyncKeyState('C') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_GameScene());
	}
	else if (GetAsyncKeyState('V') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_MenuScene());
	}
	else if (GetAsyncKeyState('B') & 0x8000)
	{
		SCENEMANAGER.ChangeState(new C_ResultScene());
	}

}

void Scene::Init()
{
	SCENEMANAGER.ChangeState(new C_TitleScene());
}

void Scene::Release()
{
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		SCENEMANAGER.ImGui();
	}
	ImGui::End();
}
