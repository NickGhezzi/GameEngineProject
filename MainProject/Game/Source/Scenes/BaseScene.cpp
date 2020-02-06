#include "GamePCH.h"
#include "BaseScene.h"

BaseScene::BaseScene(Game* game)
{
    m_pGame = game;
}

BaseScene::~BaseScene()
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
