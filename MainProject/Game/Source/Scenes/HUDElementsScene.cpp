#include "GamePCH.h"
#include "HUDElementsScene.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Camera.h"

HUDElementsScene::HUDElementsScene(Game* game)
    :BaseScene(game)
{
    m_Score1 = 0;
    m_Score2 = 0;
}

HUDElementsScene::~HUDElementsScene()
{
    delete m_pHUDCamera;
    for (int i = 0; i < 10; i++)
    {
        delete m_pScore[i];
        delete m_pScore2[i];
    }
}

void HUDElementsScene::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pHUDCamera = new Camera(this, vec3(0, 0, 0), vec2(1, 1));
    m_pHUDCamera->GetViewMatrix().SetIdentity();
    m_pHUDCamera->GetProjectionMatrix().CreateOrtho(0, 100, 0, 100, -1, 1);
    for (int i = 0; i < 10; i++)
    {
        m_pScore[i] = new GameObject(this, m_pResources->GetMesh("Score" + std::to_string(i)), m_pResources->GetMaterial("Score"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(-3, 4, 0));
        m_pScore2[i] = new GameObject(this, m_pResources->GetMesh("Score" + std::to_string(i)), m_pResources->GetMaterial("Score"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(-4, 4, 0));
    }
}

void HUDElementsScene::Update(float deltaTime)
{
    //BaseScene::Update(deltaTime);
    m_pHUDCamera->Update(deltaTime);

}

void HUDElementsScene::Draw()
{
    m_pScore[m_Score1]->Draw(m_pHUDCamera);
    m_pScore2[m_Score2]->Draw(m_pHUDCamera);
}

void HUDElementsScene::UpdateScore(int score)
{
    if (score > 9)
    {
        int lastDig = score % 10;
        int secondDig = score / 10;
        m_Score1 = lastDig;
        m_Score2 = secondDig;
    }
    else
    {
        m_Score1 = score;

    }
}

void HUDElementsScene::AddHUDElement(GameObject* element)
{

}
