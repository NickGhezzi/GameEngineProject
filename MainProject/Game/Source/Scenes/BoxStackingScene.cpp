#include "GamePCH.h"
#include "BoxStackingScene.h"
#include "Game.h"
#include "GameObjects/Player.h"
#include "GameObjects/Camera.h"
#include "ResourceManager.h"
#include "Base/ObjectPool.h"

BoxStackingScene::BoxStackingScene(Game* game):
    BaseScene(game),
    m_ObjectPool()
{
    m_pCamera = nullptr;
    m_pResources = nullptr;
}

BoxStackingScene::~BoxStackingScene()
{
    for (auto obj : m_pGameObjects)
    {
        delete obj;
    }
    m_pGameObjects.clear();

    delete m_pCamera;
    //delete m_pPhysicsWorld;
}

void BoxStackingScene::Init()
{
    m_pResources = m_pGame->GetResourceManager();
    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));

    for (int i = 0; i < 100; i++)
    {
        GameObject* pObj = new GameObject(this, m_pResources->GetMesh("PlayerMesh"), m_pResources->GetMaterial("Megaman"), vec3(1, 1, 1), vec3(0, 0, 0), vec3(0, 0, 0));
        pObj->CreateBody(false);
        pObj->GetBody()->SetActive(false);
        pObj->AddBox(vec3(1, 1, 1), 1, false, 0.2, 0);
        m_ObjectPool.AddObjectToPool(pObj);
        pObj->SetPoolWhereWeCameFrom(&m_ObjectPool);
    }

    for (int i = 0; i < 3; i++)
    {
        GameObject* pObj = m_ObjectPool.GetObjectFromPool();
        AddObjectToScene(pObj);
        pObj->GetBody()->SetActive(true);
    }
}

void BoxStackingScene::Update(float deltaTime)
{
    m_pPhysicsWorld->Update(deltaTime);
    for (auto obj : m_pGameObjects)
    {
        obj->Update(deltaTime);
    }
    m_pCamera->Update(deltaTime);
}

void BoxStackingScene::Draw()
{
    for (auto obj : m_pGameObjects)
    {
        obj->Draw(m_pCamera);
    }
}

void BoxStackingScene::LoadFromFile(const char* filename)
{

}


