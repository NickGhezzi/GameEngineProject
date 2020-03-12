#include "GamePCH.h"
#include "Game.h"
#include "BaseScene.h"
#include "GameObjects/Camera.h"

BaseScene::BaseScene(Game* game)
{
    m_pGame = game;
    m_pPhysicsWorld = new fw::PhysicsWorld2D(game->GetFramework());
    m_pCamera = new Camera(this, vec3(0, 0, 0), vec2(1 / 5.0f, 1 / 5.0f));
}

BaseScene::~BaseScene()
{
    for (auto obj : m_pGameObjects)
    {
        delete obj;
    }
    m_pGameObjects.clear();
    delete m_pCamera;
    delete m_pPhysicsWorld;
}

void BaseScene::Update(float deltaTime)
{
    m_pCamera->Update(deltaTime);

    for (auto obj : m_pGameObjects)
    {
        obj->Update(deltaTime);
    }
}

void BaseScene::Draw()
{
    for (auto obj : m_pGameObjects)
    {
        obj->Draw(m_pCamera);
    }
}

void BaseScene::LoadFromFile(const char* filename)
{

}

void BaseScene::AddObjectToScene(GameObject* pObj)
{
    //object isnt already in list
    assert(std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObj) == m_pGameObjects.end());
    m_pGameObjects.push_back(pObj);
}

void BaseScene::RemoveObjectFromScene(GameObject* pObj)
{
    //object is already in list
    assert(std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObj) != m_pGameObjects.end());
    
    auto it = std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObj);
    m_pGameObjects.erase(it);

    assert(std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObj) == m_pGameObjects.end());
}

void BaseScene::OnEvent(fw::Event* pEvent)
{
    if (pEvent->GetType() == "CollisionEvent")
    {
        fw::CollisionEvent* pCollisionEvent = (fw::CollisionEvent*)pEvent;
        if (pCollisionEvent)
        {
            GameObject* A = (GameObject*)pCollisionEvent->GetBodyA();
            GameObject* B = (GameObject*)pCollisionEvent->GetBodyB();

        }
    }
}

Game* BaseScene::GetGame()
{
    return m_pGame;
}

fw::PhysicsWorld* BaseScene::GetPhysicsWorld()
{
    return m_pPhysicsWorld;
}
