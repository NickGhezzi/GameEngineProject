#include "GamePCH.h"
#include "Game.h"
#include "BaseScene.h"

BaseScene::BaseScene(Game* game)
{
    m_pGame = game;
    m_pPhysicsWorld = new fw::PhysicsWorld2D(game->GetFramework());
}

BaseScene::~BaseScene()
{
    //for (auto obj : m_pGameObjects)
    //{
    //    delete obj;
    //}
    //m_pGameObjects.clear();
    delete m_pPhysicsWorld;
}

void BaseScene::Update(float deltaTime)
{

}

void BaseScene::Draw()
{

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

Game* BaseScene::GetGame()
{
    return m_pGame;
}

fw::PhysicsWorld* BaseScene::GetPhysicsWorld()
{
    return m_pPhysicsWorld;
}
